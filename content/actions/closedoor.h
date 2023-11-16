#pragma once

#include "action.h"

class CloseDoor : public Action {
    Result perform(Engine& engine, std::shared_ptr<Entity> entity) override;


};