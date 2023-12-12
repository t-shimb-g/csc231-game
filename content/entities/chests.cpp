#include "chests.h"
#include "entity.h"
#include "engine.h"
#include "rest.h"
#include "bite.h"
#include "mimicbite.h"

namespace Chests {
    void make_full_chest(std::shared_ptr<Entity> chest) {
        chest->set_sprite("chest_full1");
        chest->behavior = behavior;
        chest->set_max_health(10);
        chest->set_weapon(std::make_shared<Bite>(0));
    }

    void make_mimic_chest(std::shared_ptr<Entity> chest) {
        chest->set_sprite("mimic_still");
        chest->behavior = mimic_behavior;
        chest->set_max_health(20);
        chest->set_weapon(std::make_shared<Bite>(5));
    }

    std::unique_ptr<Action> behavior(Engine&, Entity&) {
        return std::make_unique<Rest>();
    }

    std::unique_ptr<Action> mimic_behavior(Engine&, Entity&) {
        return std::make_unique<MimicBite>();
    }
}