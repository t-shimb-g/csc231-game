#pragma once

#include "sprite.h"
#include <vector>

class AnimatedSprite {
public:
    AnimatedSprite();
    AnimatedSprite(const std::vector<Sprite>& sprites, int ticks_per_frame, int starting_frame=0);
    void flip(bool flip); // flip sprite horizontally
    void update();        // move to next frame of animation
    Sprite get_sprite() const;
    int number_of_frames() const;
    bool visible;
        
private:
    std::vector<Sprite> sprites;
    int ticks_per_frame{1}, current_frame{0}, time{0};
};
    
