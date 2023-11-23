#pragma once

#include "weapon.h"

class Spear : public Weapon {
public:
    Spear(int damage);

    void use(Engine& engine, Entity& attacker, Entity& defender) override;
};