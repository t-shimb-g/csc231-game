#include "attack.h"
#include "engine.h"
#include "hit.h"
#include "entity.h"
#include "weapon.h"

Attack::Attack(Entity& defender)
    :defender{defender} {}

Result Attack::perform(Engine& engine, std::shared_ptr<Entity> attacker) {
    auto weapon = attacker->get_weapon();
    weapon->use(engine, *attacker, defender);
    return success();
}