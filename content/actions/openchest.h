#pragma once

#include "action.h"

class OpenChest : public Action {
public:
    OpenChest(Entity& chest);

    Result perform(Engine& engine, std::shared_ptr<Entity> entity) override;

private:
    Entity& chest;
};