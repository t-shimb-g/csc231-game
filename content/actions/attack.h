#pragma once

#include "action.h"
#include "vec.h"

class Entity;

class Attack : public Action {
public:
    Result perform(Engine& engine, std::shared_ptr<Entity> entity) override;

    Attack(Entity& attacker, Entity& defender);
private:
    Entity& attacker;
    Entity& defender;
};