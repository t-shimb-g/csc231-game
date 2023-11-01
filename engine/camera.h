#pragma once

#include "vec.h"
#include "sprite.h"
#include <vector>
#include <unordered_map>
#include <functional>

// forward declaration
class Graphics;
class Dungeon;
class Entities;
class Engine;


class Camera {
public:
    Camera(Graphics& graphics, int tilesize, int zoom=1);

    // drawing functions
    void render(const Vec& position, const Sprite& sprite) const;
    void render(const Dungeon& dungeon) const;
    void render(const Entities& entities) const;
    void render_fog(const Dungeon& dungeon) const;
    void render_rect(const Vec& position, int red, int green, int blue, int alpha) const;
    void render_healthbar(int current_health, int max_health);
    void add_overlay(const Vec& position, const Sprite& sprite);
    void render_overlays();

    void update();

    // translate entity positions to pixel positions
    Vec world_to_screen(const Vec& position) const;

    // position camera over this position
    void move_to(const Vec& position);
    void zoom_in();
    void zoom_out();

    
private:
    Graphics& graphics;
    int tilesize;
    int zoom;
    Vec location, screen_center;

    Vec min, max; // world coordinates of min/max tiles that are visible
    void calculate_visibility_limits();
    bool within_view(const Vec& position) const;

    //std::vector<std::function<void()>> overlays;
    std::vector<std::pair<Vec, Sprite>> overlays;
};

