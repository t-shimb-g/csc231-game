#pragma once

#include "item.h"

class Heart : public Item {
public:
    Heart(Sprite sprite);

    void interact(std::shared_ptr<Entity> entity) override;

private:
    Sprite sprite;
};