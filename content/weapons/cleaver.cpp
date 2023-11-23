#include "cleaver.h"
#include "hit.h"
#include "engine.h"

Cleaver::Cleaver(int damage)
    :Weapon{"cleaver", damage} {}

void Cleaver::use(Engine& engine, Entity&, Entity& defender) {
    engine.events.create_event<Hit>(defender, damage);
}

int Cleaver::get_damage() {
    return damage;
}