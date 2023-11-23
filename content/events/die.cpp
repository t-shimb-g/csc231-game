#include "die.h"
#include "engine.h"
#include "entity.h"

Die::Die(Entity& entity)
    :entity{entity} {}

void Die::execute(Engine& engine) {
    Vec position = entity.get_position();
    engine.dungeon.remove_entity(position);
}
