#include "throwaction.h"
#include "throw.h"
#include "event.h"
#include "entity.h"
#include "weapon.h"
#include "hit.h"

Result ThrowAction::perform(Engine& engine, std::shared_ptr<Entity> entity) {
    Entity& attacker = *entity;
    auto weapon = attacker.get_weapon();
    Vec starting_tile = entity->get_position();
    Vec direction = entity->get_direction();

    Vec tile_parser = starting_tile + direction;
    while (true) {
        Tile& tile = engine.dungeon.get_tile(tile_parser);
        if (tile.has_entity() || tile.is_wall() || tile.has_door()) {
            if (tile.has_door()) {
                if (tile.door->is_open() && !tile.has_entity()) {
                    tile_parser += direction;
                    continue;
                }
            }
            Vec ending_tile = tile_parser;
            int delta = distance(ending_tile, starting_tile) * 16 / 10;

            std::shared_ptr<Event> throw_event = engine.events.create_event<Throw>(weapon->sprite, direction, delta);
            if (tile.has_entity()) {
                throw_event->add_next(Hit{*tile.entity, (entity->get_weapon())->damage + 3});
            }
            return success();
        }
        tile_parser += direction;
    }
}
