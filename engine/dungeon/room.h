#pragma once

#include "vec.h"
#include <vector>

class Room {
public:
    Vec position, size;
};

bool overlaps(const Room& a, const Room& b);
std::ostream& operator<<(std::ostream& os, const Room& room);

using Rooms = std::vector<Room>;
