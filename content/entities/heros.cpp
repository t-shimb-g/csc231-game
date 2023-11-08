#include "heros.h"
#include "entity.h"
#include "engine.h"
#include "rest.h"

namespace Heros {

    void make_wizard(std::shared_ptr<Entity> entity) {
        entity->set_sprite("wizard");
        entity->behavior = behavior;
    }

    std::unique_ptr<Action> behavior(Engine& engine, Entity&) {
        std::string key = engine.input.get_last_keypress();
        if (key == "R") {
            return std::make_unique<Rest>();
        }

        return nullptr;
    }
}
