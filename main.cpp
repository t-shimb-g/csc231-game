#include "engine.h"
#include "heros.h"
#include "monsters.h"
#include "chests.h"
#include <iostream>
#include "entity.h"

int main() {
    try {
        Settings settings{"settings.txt"};
        Engine engine{settings};

        std::shared_ptr<Entity> hero = engine.create_hero();
        Heros::make_wizard(hero);

        for (int i = 0; i < 5; ++i) {
            std::shared_ptr<Entity> monster = engine.create_monster();
            Monsters::make_orc_masked(monster);
            Monsters::make_orc(monster);
        }
        for (int i = 0; i < 5; ++i) {
            std::shared_ptr<Entity> monster = engine.create_monster();
            Monsters::make_zombie(monster);
        }
        for (int i = 0; i < 5; ++i) {
            std::shared_ptr<Entity> monster = engine.create_monster();
            Monsters::make_goblin(monster);
        }

        std::shared_ptr<Entity> chest = engine.create_monster();
        chest->set_team(Team::Chest);
        Chests::make_full_chest(chest);

        engine.run();
    }
    catch (std::exception& e) {
        std::cout << e.what() << '\n';
    }
}