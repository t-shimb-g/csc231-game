#include "heart.h"
#include "entity.h"

Heart::Heart(Sprite sprite)
    :Item{sprite} {}

void Heart::interact(std::shared_ptr<Entity> entity) {
    entity->take_damage(-3);
}