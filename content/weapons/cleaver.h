#pragma once

#include "weapon.h"

class Cleaver : public Weapon {
public:
    Cleaver(int damage);

    void use(Engine& engine, Entity& attacker, Entity& defender) override;
};