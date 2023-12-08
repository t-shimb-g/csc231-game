#include "tile.h"

Tile::Tile()
    :type{Type::None}, sprite{}, visible{false}, walkable{false}, door{nullptr}, entity{nullptr} {}
    
bool Tile::is_wall() const {
    return type == Type::Wall;
}
    
bool Tile::has_door() const {
    return type == Type::Door;
}

bool Tile::has_entity() const {
    return entity != nullptr;
}

bool Tile::is_visible() const {
    return visible;
}

bool Tile::has_item() const {
    return item != nullptr;
}