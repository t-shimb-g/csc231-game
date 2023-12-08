#pragma once

#include "action.h"
#include "tile.h"

class PickupItem : public Action { // Pick up item off tile
public:
    PickupItem(Tile& tile);

    Result perform(Engine& engine, std::shared_ptr<Entity> entity) override;

private:
    Tile& tile;
};