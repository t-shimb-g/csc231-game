#pragma once
#include <memory>
#include "sprite.h"

class Entity;

class Item {
public:
    virtual void interact(std::shared_ptr<Entity> entity) = 0;
    virtual Sprite get_sprite() const = 0;
};