#include "bite.h"
#include "engine.h"
#include "hit.h"

Bite::Bite(int damage)
    :Weapon{"none", damage} {}

void Bite::use(Engine& engine, Entity&, Entity& defender) {
    engine.events.create_event<Hit>(defender, damage);
}
