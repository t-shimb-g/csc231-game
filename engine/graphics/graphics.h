#pragma once

#include "sprite.h"
#include "animatedsprite.h"

#include <string>
#include <vector>
#include <unordered_map>

// forward declarations
struct Vec;
struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
    
class Graphics {
public:
    // window bar title and pixel width and height
    Graphics(const std::string& title, int width, int height);
    ~Graphics();

    void load_spritesheet(const std::string& filename);
    Sprite get_sprite(const std::string& name) const;
    AnimatedSprite get_animated_sprite(const std::string& name, int ticks_per_frame=1,
                                       bool random_start=false, bool shuffle_order=false) const;
        
    void clear();  // clear the screen
    void draw_rect(const Vec& pixel, const Vec& size, int r, int g, int b, int alpha);
    void draw_sprite(const Vec& pixel, const Sprite& sprite, int scale=1);
    void redraw(); // redraw all sprites on screen

    const int width;
    const int height;
        
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<SDL_Texture*> textures;
    std::unordered_map<std::string, int> texture_ids;
    std::unordered_map<std::string, std::vector<Sprite>> sprites;

    int get_texture_id(const std::string& image_filename);
};

