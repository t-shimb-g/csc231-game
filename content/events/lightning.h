#pragma once

#include "event.h"
#include "vec.h"
#include "animatedsprite.h"

class Lightning : public Event {
public:
    Lightning(Vec position);

    void execute(Engine& engine) override;
    void when_done(Engine& engine) override;

private:
    Vec position;
    const int damage = 5;
    AnimatedSprite sprite;
};