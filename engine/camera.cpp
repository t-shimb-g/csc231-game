#include "camera.h"

#include "dungeon.h"
#include "entities.h"
#include "entity.h"
#include "graphics.h"

Camera::Camera(Graphics& graphics, int tilesize, int zoom)
    :graphics{graphics}, tilesize{tilesize}, zoom{zoom}, location{0, 0},
     screen_center{graphics.width/2, graphics.height/2} {
    calculate_visibility_limits();
}

void Camera::render(const Vec& position, const Sprite& sprite) const {
    Vec pixel = world_to_screen(position);
    graphics.draw_sprite(pixel, sprite, zoom);
}
    
void Camera::render(const Dungeon& dungeon) const {
    // screen -> world
    // calculate min, max values for x, y, then only draw those
    int xmin = std::max(0, min.x);
    int ymin = std::max(0, min.y);
    int xmax = std::min(max.x, dungeon.tiles.width-1);
    int ymax = std::min(max.y, dungeon.tiles.height-1);

    // remember any doors that are in view, then draw them later on top of base tiles
    std::vector<std::pair<Vec, Sprite>> door_sprites;
    std::vector<std::pair<Vec, Sprite>> item_sprites;
    
    // draw tile base sprite
    for (int y = ymin; y <= ymax; ++y) {
        for (int x = xmin; x <= xmax; ++x) {
            Vec position{x, y};
            if (within_view(position)) {
                const Tile& tile = dungeon.tiles(position);
                render(position, tile.sprite);
                if (tile.has_door()) {
                    door_sprites.push_back({position, tile.door->get_sprite()});
                }
                if (tile.has_item()) {
                    item_sprites.push_back({position, tile.item->get_sprite()});
                }
            }
        }
    }

    // draw decorations
    for (const auto& [position, doodad] : dungeon.decorations) {
        if (within_view(position)) {
            render(position, doodad.get_sprite());
        }
    }

    // draw doors
    for (const auto& [position, sprite] : door_sprites) {
        render(position, sprite);
    }

    // draw items
    for (const auto& [position, sprite] : item_sprites) {
        render(position, sprite);
    }
}

void Camera::render(const Entities& entities) const {
    for (std::shared_ptr<Entity> entity : entities) {
        if (within_view(entity->get_position()) && entity->is_alive() && entity->is_visible()) {
            for (Sprite sprite : entity->get_sprites()) {
                render(entity->get_position(), sprite);
            }
        }
    }
}


void Camera::render_fog(const Dungeon& dungeon) const {
    int xmin = std::max(0, min.x);
    int ymin = std::max(0, min.y);
    int xmax = std::min(max.x, dungeon.tiles.width-1);
    int ymax = std::min(max.y, dungeon.tiles.height-1);
        
    for (int y = ymin; y <= ymax; ++y) {
        for (int x = xmin; x <= xmax; ++x) {
            Vec position{x, y};
            double brightness = dungeon.fog.brightness(position);
            int alpha = std::clamp(static_cast<int>(brightness*255), 0, 255);
            render_rect(position, 0, 0, 0, alpha);
        }
    }
}

void Camera::render_rect(const Vec& position, int red, int green, int blue, int alpha) const {
    int scale = tilesize * zoom;
    Vec pixel = world_to_screen(position);
    // sprites are anchored at the bottom center, whereas
    // rectangle are anchored at the upper-left: shift pixel x and
    // y values
    pixel.x -= scale / 2;
    pixel.y -= scale;
    Vec size{scale, scale};
    graphics.draw_rect(pixel, size, red, green, blue, alpha);
}

void Camera::render_healthbar(int current_health, int max_health) {
    double percentage = current_health / static_cast<double>(max_health);
    int length = static_cast<int>(percentage*300);
    graphics.draw_rect({10, 10}, {320, 40}, 255, 255, 255, 255);
    graphics.draw_rect({15, 15}, {310, 30}, 0, 0, 0, 255);
    graphics.draw_rect({20, 20}, {length, 20}, 50, 255, 50, 255);
}

void Camera::add_overlay(const Vec& position, const Sprite& sprite) {
    overlays.push_back({position, sprite});
}

void Camera::render_overlays() {
    for (auto [position, sprite] : overlays) {
        render(position, sprite);
    }
}

void Camera::update() {
    overlays.clear();
}


Vec Camera::world_to_screen(const Vec& position) const {
    // World Coords (cartesian, up is positive y) -> Pixel Coords (image, down is positive y):
    // 1. Shift dungeon position by making the camera's location be the origin
    // 2. Multiple this position by zoom and tilesize to convert to pixels
    // 3. Shift the pixel location to the center of the screen
    Vec pixel = zoom * tilesize * (position - location) + screen_center;

    // 4. flip y-axis
    pixel.y = graphics.height - pixel.y;

    // 5. shift up by half a tile to center it
    pixel.y += zoom * tilesize / 2;
    return pixel;
}

void Camera::move_to(const Vec& position) {
    location = position;
    calculate_visibility_limits();
}
    
void Camera::zoom_in() {
    if (zoom < 8) {
        ++zoom;
        calculate_visibility_limits();
    }
}
    
void Camera::zoom_out() {
    if (zoom > 1) {
        --zoom;
        calculate_visibility_limits();
    }
}

void Camera::calculate_visibility_limits() {
    Vec num_tiles = Vec{graphics.width, graphics.height} / (2 * zoom * tilesize) + Vec{1, 1};
    max = location + num_tiles;
    min = location - num_tiles;
}
    
bool Camera::within_view(const Vec& position) const {
    return min.x <= position.x && position.x <= max.x
        && min.y <= position.y && position.y <= max.y;
}

