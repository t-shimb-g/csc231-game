#include "openchest.h"
#include "entity.h"
#include "engine.h"
#include "droploot.h"

OpenChest::OpenChest(Entity& chest)
    :chest{chest} {}

Result OpenChest::perform(Engine& engine, std::shared_ptr<Entity>) {
    chest.set_sprite("chest_full2");
    chest.set_sprite("chest_full3");
    engine.events.create_event<DropLoot>(chest.get_position(), chest.get_item());
    engine.remove_entity(chest);
    return success();
}
