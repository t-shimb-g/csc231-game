#pragma once

#include "weapon.h"

class Bite : public Weapon {
public:
    Bite(int damage);
    void use(Engine& engine, Entity& attacker, Entity& defender) override;
};
