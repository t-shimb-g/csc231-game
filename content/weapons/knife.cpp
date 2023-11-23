#include "knife.h"
#include "hit.h"
#include "engine.h"

Knife::Knife(int damage)
    :Weapon{"knife", damage} {}

void Knife::use(Engine& engine, Entity& attacker, Entity& defender) {
    engine.events.create_event<Hit>(defender, damage);
}
