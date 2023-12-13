#pragma once

#include "event.h"
#include "item.h"

class DropLoot : public Event {
public:
    DropLoot(Vec position, std::shared_ptr<Item> item);

    void execute(Engine& engine) override;
    void when_done(Engine& engine) override;

private:
    Vec position;
    std::shared_ptr<Item> item;
};