#pragma once

#include "weapon.h"

class Club : public Weapon {
public:
    Club(int damage);

    void use(Engine& engine, Entity& attacker, Entity& defender) override;
};