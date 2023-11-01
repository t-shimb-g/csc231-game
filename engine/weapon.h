#pragma once

#include <functional>
#include <memory>
#include <string>

#include "entity.h"
#include "sprite.h"

class Weapon {
public:
    Weapon();
    // name corresponds to a sprite in weapons.txt
    Weapon(const std::string& name, int damage);
    virtual ~Weapon() {}

    // override with what happens when the weapon is used in game
    virtual void use(Engine& engine, Entity& attacker, Entity& defender);

    // these are public to allow for manipulation by heros and monsters
    std::string name;
    int damage{0};
    Sprite sprite;
};
