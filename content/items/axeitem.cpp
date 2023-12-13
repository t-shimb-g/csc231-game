#include "axeitem.h"
#include "entity.h"
#include "weapon.h"

AxeItem::AxeItem(std::shared_ptr<Weapon> weapon)
    :weapon{weapon} {
}

void AxeItem::interact(std::shared_ptr<Entity> entity) {
    std::shared_ptr<Item> item = std::make_shared<AxeItem>(weapon);
    entity->add_to_inventory(item);
    entity->set_weapon(weapon);
}

Sprite AxeItem::get_sprite() const {
    weapon->sprite.angle = 45;
    return weapon->sprite;
    // TODO: SHIFT SPRITE DOWN A FEW PIXELS
}