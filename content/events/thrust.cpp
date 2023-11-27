#include "thrust.h"

constexpr int duration = 3;
constexpr int delta = 3; // change in pixels per frame

Thrust::Thrust(Sprite& sprite, Vec direction)
    :Event{duration}, sprite{sprite}, copy{sprite}, direction{direction} {

    sprite.shift.y -= sprite.size.y / 4;
    sprite.center = sprite.size / 2;

    if (direction == Vec{1, 0}) { // right
        sprite.angle = 90;
        sprite.shift.y += sprite.size.y / 2;
    }
    else if (direction == Vec{-1, 0}) { // left
        sprite.angle = 270;
        sprite.shift.y += sprite.size.y / 2;

    }
    else if (direction == Vec{0, 1}) { // up
        sprite.angle = 0;
        this->direction = direction * -1;
    }
    else { // down
        sprite.angle = 180;
        this->direction = direction * -1;
        sprite.shift.y += sprite.size.y / 2;
    }
}

void Thrust::execute(Engine& engine) {
    sprite.shift += direction * delta;
}

void Thrust::when_done(Engine& engine) {
    sprite = copy;
}
