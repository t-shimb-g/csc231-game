#pragma once

#include "vec.h"


// represents a 2D image in the game
struct Sprite {
    int texture_id{-1}; // assigned automatically when requested from graphics engine
    Vec location{0, 0}; // upper left corner of sprite in image
    Vec size{0, 0};     // size (width, height) of sprite in image
    Vec shift{0, 0};    // pixels to shift by when displaying
    Vec center{0, 0};   // position to rotate about
    double angle{0.0};  // angle of rotation
    bool flip{false};   // whether to flip sprite horizontally
};
