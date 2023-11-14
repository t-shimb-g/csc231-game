#include "opendoor.h"
#include "updatefov.h"

Result OpenDoor::perform(Engine& engine, std::shared_ptr<Entity>) {
        door.open();
        engine.events.create_event<UpdateFOV>();
        return success();
}

OpenDoor::OpenDoor(Door& door)
    :door{door}{}