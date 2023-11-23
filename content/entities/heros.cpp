#include "heros.h"
#include "entity.h"
#include "engine.h"
#include "rest.h"
#include "move.h"
#include "closedoor.h"
#include "cleaver.h"


namespace Heros {

    void make_wizard(std::shared_ptr<Entity> entity) {
        entity->set_sprite("wizard");
        entity->behavior = behavior;
        entity->set_max_health(20);
        entity->set_weapon(std::make_shared<Cleaver>(4));
    }

    std::unique_ptr<Action> behavior(Engine& engine, Entity&) {
        std::string key = engine.input.get_last_keypress();
        if (key == "R") {
            return std::make_unique<Rest>();
        }
        else if (key == "Right" || key == "D") {
            return std::make_unique<Move>(Vec{1, 0});
        }
        else if (key == "Left" || key == "A") {
            return std::make_unique<Move>(Vec{-1, 0});
        }
        else if (key == "Up" || key == "W") {
            return std::make_unique<Move>(Vec{0, 1});
        }
        else if (key == "Down" || key == "S") {
            return std::make_unique<Move>(Vec{0, -1});
        }
        else if (key == "C") {
            return std::make_unique<CloseDoor>();
        }

        return nullptr;
    }
}