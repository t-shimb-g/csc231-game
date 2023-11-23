#include "monsters.h"
#include "entity.h"
#include "engine.h"
#include "rest.h"
#include "randomness.h"
#include "wander.h"
#include "move.h"

namespace Monsters {
    void make_orc_masked(std::shared_ptr<Entity> monster) {
        monster->set_sprite("orc_masked");
        monster->behavior = behavior;
        monster->set_max_health(12);
    }

    void make_zombie(std::shared_ptr<Entity> monster) {
        monster->set_sprite("zombie");
        monster->behavior = behavior;
        monster->set_max_health(20);
    }

    void make_goblin(std::shared_ptr<Entity> monster) {
        monster->set_sprite("goblin");
        monster->behavior = behavior;
        monster->set_max_health(4);
    }

    std::unique_ptr<Action> behavior(Engine& engine, Entity& entity) {
        // if visible to hero, calculate path, and move towards hero
        if (engine.hero && entity.is_visible()) {
            std::vector<Vec> path = engine.dungeon.calculate_path(entity.get_position(), engine.hero->get_position());

            if (path.size() > 1) {
                Vec direction = path.at(1) - path.at(0);
                return std::make_unique<Move>(direction);
            }
        }
        // hero can't see monster
        if (probability(66)) {
            return std::make_unique<Wander>();
        }
        else {
            return std::make_unique<Rest>();
        }
    }
}