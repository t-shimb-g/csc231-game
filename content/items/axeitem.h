#pragma once

#include "item.h"

class Weapon;

class AxeItem : public Item {
public:
    AxeItem(std::shared_ptr<Weapon> weapon);

    void interact(std::shared_ptr<Entity> entity) override;
    Sprite get_sprite() const override;

private:
    std::shared_ptr<Weapon> weapon;
};