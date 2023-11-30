#pragma once

#include "weapon.h"

class Axe : public Weapon {
public:
    Axe(int damage);

    void use(Engine& engine, Entity& attacker, Entity& defender) override;
};