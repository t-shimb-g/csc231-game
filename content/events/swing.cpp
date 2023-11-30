#include "swing.h"
#include <cmath>

constexpr int duration = 5;

Swing::Swing(Sprite& sprite, Vec direction)
    :Event{duration}, sprite{sprite}, copy{sprite} {

    if (direction == Vec{1, 0}) { // right
        starting_angle = 0;
        delta = 135.0 / duration - 1;

    }
    else if (direction == Vec{-1, 0}) { // left
        starting_angle = 0;
        delta = -135.0 / (duration - 1);

    }
    else if (direction == Vec{0, 1}) { // up
        sprite.shift.y -= 12;
        double sign = std::copysign(1.0, sprite.angle);
        starting_angle = -75 * sign; // rotate back before swing
        delta = 90.0 / (duration - 1) * sign;
    }
    else { // down
       sprite.shift.y -= 4;
       double sign = std::copysign(1.0, sprite.angle);
       sprite.shift.x = -4;
       starting_angle = 135 * sign; // rotate forward before swing
       delta = 90.0 / (duration - 1) * sign;
    }
}

void Swing::execute(Engine&) {
    sprite.angle = starting_angle + delta * frame_count;
}

void Swing::when_done(Engine&) {
    sprite = copy;
}