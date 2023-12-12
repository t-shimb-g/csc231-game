#include "mimicbite.h"
#include "entity.h"
#include "engine.h"
#include "vec.h"
#include "attack.h"
#include "rest.h"

Result MimicBite::perform(Engine& engine, std::shared_ptr<Entity> entity) {
    std::vector<Vec> neighbors = engine.dungeon.neighbors(entity->get_position());
    for (Vec tilepos : neighbors) {
        Tile& tile = engine.dungeon.get_tile(tilepos);
        if (tile.has_entity() && tile.entity->get_team() == Team::Hero) {
            entity->set_sprite("mimic");
            return alternative(Attack{*tile.entity});
        }
    }
    return alternative(Rest());
}