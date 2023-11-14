#include "move.h"
#include "entity.h"
#include "opendoor.h"

Result Move::perform(Engine& engine, std::shared_ptr<Entity> entity) {
    Vec new_pos = entity->get_position() + direction;

    Tile& tile = engine.dungeon.get_tile(new_pos);
    if (tile.is_wall()) {
        return failure();
    }
    else if (tile.has_door() && !tile.door->is_open()) {
        return alternative(OpenDoor{new_pos});
    }
    else {
        entity->move_to(new_pos);
        entity->change_direction(direction);
        return success();
    }
}

Move::Move(Vec direction)
    :direction{direction} {}