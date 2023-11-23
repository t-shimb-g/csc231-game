#include "spear.h"
#include "hit.h"
#include "engine.h"

Spear::Spear(int damage)
    :Weapon{"spear", damage} {}

void Spear::use(Engine& engine, Entity& attacker, Entity& defender) {
    engine.events.create_event<Hit>(defender, damage);
}
