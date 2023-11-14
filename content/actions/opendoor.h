#include "action.h"
#include "entity.h"
#include "engine.h"

class OpenDoor : public Action {
public:
    Result perform(Engine& engine, std::shared_ptr<Entity> entity) override;

    OpenDoor(Door& door);

private:
    Door& door;
};