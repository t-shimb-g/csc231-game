#include "throw.h"
#include "tile.h"
#include "engine.h"

constexpr int duration = 10;
int sign = 1;

Throw::Throw(Sprite& sprite, Vec direction, int delta)
    :Event{duration}, sprite{sprite}, copy{sprite}, direction{direction}, delta{delta} {
    sprite.center = sprite.size / 2;

    if (direction == Vec{1, 0}) { // right
        sign = 1;
    }
    else if (direction == Vec{-1, 0}) { // left
        sign = -1;
    }
    else if (direction == Vec{0, 1}) { // up
        sprite.angle += 90;
        this->direction = direction * -1;
    }
    else { // down
        sprite.angle -= 90;
        this->direction = direction * -1;
    }
}
void Throw::execute(Engine& engine) {
    sprite.angle += 77 * sign; // Magic number
    sprite.shift += direction * delta;
}

void Throw::when_done(Engine& engine) {
    sprite = copy; // This will leave once item works
}
