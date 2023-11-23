#pragma once

#include "weapon.h"

class Knife : public Weapon {
public:
    Knife(int damage);

    void use(Engine& engine, Entity& attacker, Entity& defender) override;
};