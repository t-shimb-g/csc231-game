#pragma once

#include "sprite.h"

class Tile;

class Door {
public:
    Door(Tile& tile, bool is_horizontal, const Sprite& horizontal, const Sprite& vertical);
    bool is_open() const;
    void open();
    void close();
    const Sprite& get_sprite() const;

    const Tile& get_tile() const;
        
private:
    Tile& tile;
    bool open_status;
    bool is_horizontal;
    Sprite horizontal, vertical;
};

