#include "closedoor.h"
#include "entity.h"
#include "engine.h"
#include "updatefov.h"

Result CloseDoor::perform(Engine& engine, std::shared_ptr<Entity> entity) {
    Vec player_pos = entity->get_position();
    std::vector<Vec> neighbors = engine.dungeon.neighbors(player_pos);

    bool closed_any_doors = false;
    for (Vec position : neighbors) {
        Tile& tile = engine.dungeon.get_tile(position);
        if (tile.has_door() && tile.door->is_open()) {
            tile.door->close();
            closed_any_doors = true;
        }
    }

    if (closed_any_doors) {
        engine.events.create_event<UpdateFOV>();
        return success();
    }
    else {
        return failure();
    }
}