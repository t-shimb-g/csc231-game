#include "knife.h"
#include "hit.h"
#include "engine.h"
#include "thrust.h"
#include "swing.h"
#include "randomness.h"

Knife::Knife(int damage)
    :Weapon{"knife", damage} {}

void Knife::use(Engine& engine, Entity& attacker, Entity& defender) {
    engine.events.create_event<Hit>(defender, damage);
    Vec direction = defender.get_position() - attacker.get_position();
    if (probability(50)) {
        std::shared_ptr<Event> swing = engine.events.create_event<Swing>(sprite, direction);
        swing->add_next(Hit{defender, damage});
    }
    else {
        std::shared_ptr<Event> thrust = engine.events.create_event<Thrust>(sprite, direction);
        thrust->add_next(Hit{defender, damage});
    }
}