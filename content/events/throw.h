#pragma once

#include "event.h"
#include "sprite.h"
#include "vec.h"

class Throw : public Event {
public:
    Throw(Sprite& sprite, Vec direction, int delta);

    void execute(Engine& engine) override;
    void when_done(Engine& engine) override;

private:
    Sprite& sprite;
    Sprite copy;
    Vec direction;
    int delta;
};