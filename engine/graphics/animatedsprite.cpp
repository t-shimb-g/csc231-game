#include "animatedsprite.h"


AnimatedSprite::AnimatedSprite()
    :sprites{Sprite{}}, ticks_per_frame{1}, current_frame{0}, time{0} {}    

AnimatedSprite::AnimatedSprite(const std::vector<Sprite>& sprites, int ticks_per_frame,
                               int starting_frame)
    :visible{true}, sprites{sprites}, ticks_per_frame{ticks_per_frame},
     current_frame{starting_frame}, time{0} {}

void AnimatedSprite::flip(bool flip) {
    for (Sprite& sprite : sprites) {
        sprite.flip = flip;
    }
}

void AnimatedSprite::update() {
    if (!visible) {
        return;
    }
    ++time;
    if (time >= ticks_per_frame) {
        current_frame = (current_frame + 1) % sprites.size();
    }
}

Sprite AnimatedSprite::get_sprite() const {
    return sprites.at(current_frame);
}

int AnimatedSprite::number_of_frames() const {
    return sprites.size();
}
