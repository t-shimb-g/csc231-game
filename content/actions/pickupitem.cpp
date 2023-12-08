#include "pickupitem.h"
#include "item.h"

PickupItem::PickupItem(Tile& tile)
    :tile{tile} {}

Result PickupItem::perform(Engine& engine, std::shared_ptr<Entity> entity) {
    tile.item->interact(entity);
    tile.item = nullptr;
    return success();
}
