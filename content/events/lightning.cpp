#include "lightning.h"
#include "hit.h"
#include "engine.h"
#include "audioevent.h"

Lightning::Lightning(Vec position)
    :position{position} {}

void Lightning::execute(Engine& engine) {
    if (frame_count == 0) {
        sprite = engine.graphics.get_animated_sprite("lightning"); // ticks per frame defaults to 1
        number_of_frames = sprite.number_of_frames();
        //engine.events.create_event<AudioEvent>("thunder");
    }

    engine.camera.add_overlay(position, sprite.get_sprite());
    sprite.update();
}

void Lightning::when_done(Engine& engine) {
    Tile& tile = engine.dungeon.get_tile(position);

    if (tile.has_entity()) {
        Entity& entity = *tile.entity;
        engine.events.create_event<Hit>(entity, 6);
    }
}
