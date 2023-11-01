#include "engine.h"
#include "heros.h"
#include "monsters.h"
#include <iostream>

int main() {
    try {
        Settings settings{"settings.txt"};
        Engine engine{settings};

        std::shared_ptr<Entity> hero = engine.create_hero();
        
        engine.run();
    }
    catch (std::exception& e) {
        std::cout << e.what() << '\n';
    }
}
