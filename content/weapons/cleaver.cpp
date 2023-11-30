#include "cleaver.h"
#include "hit.h"
#include "engine.h"
#include "swing.h"

Cleaver::Cleaver(int damage)
    :Weapon{"cleaver", damage} {}

void Cleaver::use(Engine& engine, Entity& attacker, Entity& defender) {
    Vec direction = defender.get_position() - attacker.get_position();
    std::shared_ptr<Event> swing = engine.events.create_event<Swing>(sprite, direction);
    swing->add_next(Hit{defender, damage});
}