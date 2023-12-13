#include "sworditem.h"
#include "entity.h"
#include "weapon.h"

SwordItem::SwordItem(std::shared_ptr<Weapon> weapon)
    :weapon{weapon} {}

void SwordItem::interact(std::shared_ptr<Entity> entity) {
    std::shared_ptr<Item> item = std::make_shared<SwordItem>(weapon);
    entity->add_to_inventory(item);
    entity->set_weapon(weapon);
}

Sprite SwordItem::get_sprite() const {
    weapon->sprite.angle = 45;
    return weapon->sprite;
}


