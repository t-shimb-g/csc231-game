#pragma once

#include "action.h"

class Vec;

class Rest : public Action {
public:
    Result perform(Engine& engine, std::shared_ptr<Entity> entity) override;
};
