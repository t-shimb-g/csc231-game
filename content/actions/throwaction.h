#pragma once

#include "action.h"
#include "engine.h"

class ThrowAction : public Action {
public:
    Result perform(Engine& engine, std::shared_ptr<Entity> entity) override;
};