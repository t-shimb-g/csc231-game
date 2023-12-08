#include "item.h"

Item::Item(Sprite sprite)
    :sprite{sprite} {}

Sprite Item::get_sprite() {
    return sprite;
}