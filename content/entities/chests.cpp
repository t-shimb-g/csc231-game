#include "chests.h"
#include "entity.h"
#include "engine.h"
#include "rest.h"
#include "bite.h"

namespace Chests {
    void make_full_chest(std::shared_ptr<Entity> chest) {
        chest->set_sprite("chest_empty"); // Add asset txt with chest sprites
        chest->behavior = behavior;
        chest->set_max_health(10);
        chest->set_weapon(std::make_shared<Bite>(0));
    }

    void make_empty_chest(std::shared_ptr<Entity> chest) {
        chest->set_sprite("");
        chest->behavior = behavior;
        chest->set_max_health(10);
        chest->set_weapon(std::make_shared<Bite>(0));
    }

    void make_mimic_chest(std::shared_ptr<Entity> chest) {
        chest->set_sprite("");
        chest->behavior = behavior;
        chest->set_max_health(20);
        chest->set_weapon(std::make_shared<Bite>(5));
    }

    std::unique_ptr<Action> behavior(Engine& engine, Entity& entity) {
        return std::make_unique<Rest>();
    }

}