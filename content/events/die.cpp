#include "die.h"
#include "engine.h"
#include "entity.h"
#include "audioevent.h"

Die::Die(Entity& entity)
    :entity{entity} {}

void Die::execute(Engine& engine) {
    Vec position = entity.get_position();
    engine.dungeon.remove_entity(position);
    engine.events.create_event<AudioEvent>("death");
}
