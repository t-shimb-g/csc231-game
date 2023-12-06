#pragma once

#include "action.h"

class CastLightning : public Action {
public:
    Result perform(Engine& engine, std::shared_ptr<Entity> entity) override;
};