#include "engine.h"
#include "heros.h"
#include "monsters.h"
#include "chests.h"
#include <iostream>
#include "entity.h"
#include "axeitem.h"
#include "axe.h"
#include "sword.h"
#include "sworditem.h"

int main() {
    try {
        Settings settings{"settings.txt"};
        Engine engine{settings};

        std::shared_ptr<Entity> hero = engine.create_hero();
        Heros::make_wizard(hero);
        auto hero_weapon = std::make_shared<Sword>(5);
        hero_weapon->sprite = engine.graphics.get_sprite("sword");
        auto hero_item = std::make_shared<SwordItem>(hero_weapon);
        hero->add_to_inventory(hero_item);

//        for (int i = 0; i < 5; ++i) {
//            std::shared_ptr<Entity> monster = engine.create_monster();
//            Monsters::make_orc_masked(monster);
//            Monsters::make_orc(monster);
//        }
//        for (int i = 0; i < 5; ++i) {
//            std::shared_ptr<Entity> monster = engine.create_monster();
//            Monsters::make_zombie(monster);
//        }
        for (int i = 0; i < 2; ++i) {
            std::shared_ptr<Entity> monster = engine.create_monster();
            Monsters::make_goblin(monster);
        }
        for (int i = 0; i < 5; ++i) {
            std::shared_ptr<Entity> chest = engine.create_monster();
            chest->set_team(Team::Chest);
            auto axe = std::make_shared<Axe>(5);
            axe->sprite = engine.graphics.get_sprite("axe");
            auto item = std::make_shared<AxeItem>(axe);
            chest->add_to_inventory(item);
            Chests::make_full_chest(chest);
        }

        std::shared_ptr<Entity> mimic = engine.create_monster();
        Chests::make_mimic_chest(mimic);

        engine.run();
    }
    catch (std::exception& e) {
        std::cout << e.what() << '\n';
    }
}