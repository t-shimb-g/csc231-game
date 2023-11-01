#include "graphics.h"
#include "vec.h"
#include "randomness.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdexcept>
#include <fstream>
#include <iostream>

Graphics::Graphics(const std::string& title, int width, int height)
    :width{width}, height{height} {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::string msg{"Unable to initialize SDL Video: "};
        msg += SDL_GetError();
        SDL_Quit();
        throw std::runtime_error(msg);
    }

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              width, height, 0);
    if (!window) {
        throw std::runtime_error(SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        throw std::runtime_error(SDL_GetError());
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    int img_flags = IMG_INIT_PNG;
    if (!(IMG_Init(img_flags) & img_flags)) {
        throw std::runtime_error(IMG_GetError());
    }
}

Graphics::~Graphics() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    IMG_Quit();
    SDL_Quit();
}


void Graphics::load_spritesheet(const std::string& filename) {
    std::ifstream input{filename};
    if (!input) {
        throw std::runtime_error("Could not open filename: " + filename);
    }
    std::string image_filename;
    input >> image_filename;
    auto i = filename.find('/');
    std::string parent_path{filename.substr(0, i+1)};
    image_filename = parent_path + image_filename;

    int texture_id = get_texture_id(image_filename);
    
    // load sprites
    std::string name;
    int x, y, width, height;
    while (input >> name >> x >> y >> width >> height) {
        Vec shift{-width / 2, -height}; // anchor at bottom center of sprite
        Vec center{width / 2, height / 2};
            
        int number_of_frames;
        if (!(input >> number_of_frames)) { // attempt to read optional value
            number_of_frames = 1;
            input.clear(); // clear error if there was no optional value
        }
        for (int i = 0; i < number_of_frames; ++i) {
            Vec location{x+i*width, y};
            Vec size{width, height};
            Sprite sprite{texture_id, location, size, shift, center};
            sprites[name].push_back(sprite);
        }
    }

    if (sprites.size() == 0) {
        throw std::runtime_error("Could not read any sprites from filename: " + filename);
    }
}

Sprite Graphics::get_sprite(const std::string& name) const {
    auto i = sprites.find(name);
    if (i == sprites.end()) {
        throw std::runtime_error("Cannot find sprite: " + name);
    }
    return i->second.front();
}

AnimatedSprite Graphics::get_animated_sprite(const std::string& name, int ticks_per_frame,
                                             bool random_start, bool shuffle_order) const {
    auto i = sprites.find(name);
    if (i == sprites.end()) {
        throw std::runtime_error("Cannot find sprite: " + name);
    }

    std::vector<Sprite> sprites = i->second;
    if (shuffle_order) {
        shuffle(std::begin(sprites), std::end(sprites));
    }
        
    if (sprites.size() > 1 && random_start) {
        // choose random starting frame
        int starting_frame = randint(0, sprites.size() - 1);
        return AnimatedSprite{sprites, ticks_per_frame, starting_frame};
    }
    else {
        return AnimatedSprite{sprites, ticks_per_frame};
    }
}

void Graphics::clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Graphics::redraw() {
    SDL_RenderPresent(renderer);
}

void Graphics::draw_rect(const Vec& pixel, const Vec& size, int r, int g, int b, int alpha) {
    SDL_Rect rect{pixel.x, pixel.y, size.x, size.y};
    SDL_SetRenderDrawColor(renderer, r, g, b, alpha);
    SDL_RenderFillRect(renderer, &rect);
}

void Graphics::draw_sprite(const Vec& pixel, const Sprite& sprite, int scale) {
    if (sprite.texture_id < 0) { // sprite with empty texture
        return;
    }
    int x = pixel.x + sprite.shift.x * scale;
    int y = pixel.y + sprite.shift.y * scale;
    int w = sprite.size.x * scale;
    int h = sprite.size.y * scale;
    SDL_Rect screen_pixels{x, y, w, h};
    SDL_Point center{sprite.center.x*scale, sprite.center.y*scale};
    SDL_Rect image_pixels{sprite.location.x, sprite.location.y, sprite.size.x, sprite.size.y};
    SDL_Texture* texture = textures.at(sprite.texture_id);
    SDL_RendererFlip flip = sprite.flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_RenderCopyEx(renderer, texture, &image_pixels, &screen_pixels,
                     sprite.angle, &center, flip);
}

int Graphics::get_texture_id(const std::string& image_filename) {
    auto search = texture_ids.find(image_filename);
    if (search != texture_ids.end()) { // image file already loaded
        int texture_id = search->second;
        return texture_id;
    }
    else { // new image file
        SDL_Texture* texture = IMG_LoadTexture(renderer, image_filename.c_str());
        std::cout << "New: " << image_filename << ": " << texture << "\n";
        if (!texture) {
            throw std::runtime_error(IMG_GetError());
        }
        
        // register new texture
        int texture_id = textures.size();
        texture_ids[image_filename] = texture_id;
        // retain ownership of texture pointer
        textures.push_back(texture);
        return texture_id;
    }
}
