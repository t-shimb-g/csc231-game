#pragma once

#include "sprite.h"
#include <memory>

// forward declaration
class Entity;
class Door;

class Tile {
public:
    Tile();
    bool is_wall() const;
    bool has_door() const;
    bool has_entity() const;
    bool is_visible() const;
    
    enum class Type { None, Floor, Wall, Door };
    
    Type type;
    Sprite sprite;
    bool visible;
    bool walkable;

    std::shared_ptr<Door> door;
    Entity* entity;
};
