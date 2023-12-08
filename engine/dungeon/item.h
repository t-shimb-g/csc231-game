#pragma once
#include <memory>
#include "sprite.h"

class Entity;

class Item {
public:
    Item(Sprite sprite);

    virtual void interact(std::shared_ptr<Entity> entity) = 0;
    Sprite get_sprite();

private:
    Sprite sprite;
};