#include "heart.h"
#include "entity.h"

Heart::Heart(Sprite sprite)
    :sprite{sprite} {}

void Heart::interact(std::shared_ptr<Entity> entity) {
    entity->take_damage(-3);
}

Sprite Heart::get_sprite() const {
    return sprite;
}