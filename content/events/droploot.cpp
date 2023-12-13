#include "droploot.h"
#include "engine.h"
#include "entity.h"

DropLoot::DropLoot(Vec position, std::shared_ptr<Item> item)
     :position{position}, item{item} {}

void DropLoot::execute(Engine& engine) {
    Tile& tile = engine.dungeon.get_tile(position);
    tile.item = item;
}

void DropLoot::when_done(Engine& engine) {}