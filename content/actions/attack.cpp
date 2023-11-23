#include "attack.h"
#include "engine.h"
#include "hit.h"
#include "entity.h"
#include "weapon.h"

Attack::Attack(Entity& attacker, Entity& defender)
    :attacker{attacker}, defender{defender} {}

Result Attack::perform(Engine& engine, std::shared_ptr<Entity> entity) {
    auto weapon = attacker.get_weapon();
    engine.events.create_event<Hit>(defender, weapon->damage);
    return success();
}