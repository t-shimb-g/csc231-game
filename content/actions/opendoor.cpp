#include "opendoor.h"
#include "updatefov.h"

Result OpenDoor::perform(Engine& engine, std::shared_ptr<Entity> entity) {
    bool opened_any_doors = false;
    Tile& tile = engine.dungeon.get_tile(door_pos);

    if (tile.has_door() && !tile.door->is_open()) {
        tile.door->open();
        opened_any_doors = true;
    }

    if (opened_any_doors) {
        engine.events.create_event<UpdateFOV>();
        return success();
    }
    else {
        return failure();
    }
}

OpenDoor::OpenDoor(Vec door_pos)
    :door_pos{door_pos} {}