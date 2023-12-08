#include "die.h"
#include "engine.h"
#include "entity.h"
#include "audioevent.h"
#include "randomness.h"
#include "heart.h"

Die::Die(Entity& entity)
    :entity{entity} {}

void Die::execute(Engine& engine) {
    Vec position = entity.get_position();
    engine.dungeon.remove_entity(position);
    if (probability(100)) {
        Sprite sprite = engine.graphics.get_sprite("heart_full");
        engine.dungeon.get_tile(position).item = std::make_shared<Heart>(sprite);
    }
    engine.events.create_event<AudioEvent>("death");
}
