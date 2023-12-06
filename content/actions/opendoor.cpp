#include "opendoor.h"
#include "updatefov.h"
#include "audioevent.h"

Result OpenDoor::perform(Engine& engine, std::shared_ptr<Entity>) {
        door.open();
        engine.events.create_event<UpdateFOV>();
        const Tile& tile = door.get_tile();
        if (tile.is_visible()) {
            engine.events.create_event<AudioEvent>("door-open");
        }
        return success();
}

OpenDoor::OpenDoor(Door& door)
    :door{door}{}