#include "move.h"
#include "entity.h"
#include "opendoor.h"
#include "rest.h"
#include "attack.h"
#include "pickupitem.h"
#include "openchest.h"

Move::Move(Vec direction)
    :direction{direction} {}

Result Move::perform(Engine& engine, std::shared_ptr<Entity> entity) {
    Vec new_pos = entity->get_position() + direction;
    entity->change_direction(direction);

    Tile& tile = engine.dungeon.get_tile(new_pos);
    if (tile.is_wall()) {
        return failure();
    }
    else if (tile.has_entity()) {
        if (tile.entity->get_team() != entity->get_team()) {
            if (tile.entity->get_team() == Team::Chest) {
                return alternative(OpenChest{*tile.entity});
            }
            return alternative(Attack{*tile.entity});
        }
        else {
            return alternative(Rest{});
        }
    }
    else if (tile.has_door() && !tile.door->is_open()) {
        return alternative(OpenDoor{*tile.door});
    }
    else {
        entity->move_to(new_pos);
        if (tile.has_item() && entity->get_team() == Team::Hero) {
            return alternative(PickupItem{tile});
        }
        return success();
    }
}