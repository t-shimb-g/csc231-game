#include "cast_lightning.h"
#include "randomness.h"
#include "entity.h"
#include "engine.h"
#include "lightning.h"
#include <iostream>

Vec find_good_position(Engine& engine, Vec position) {
    auto [px, py] = position;
    while (true) {
        int x = randint(px - 5, px + 5);
        int y = randint(py - 5, py + 5);
        if (engine.dungeon.tiles.within_bounds({x, y})) {
            px = x;
            py = y;
            return {px, py};
        }
    }
}

Result CastLightning::perform(Engine& engine, std::shared_ptr<Entity> entity) {
    for (int i = 0; i < 5; ++i) {
        Vec good_pos = find_good_position(engine, entity->get_position());
        std::cout << "Here";
        engine.events.create_event<Lightning>(good_pos);
    }
    return success();
}
