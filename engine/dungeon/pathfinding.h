#pragma once

#include "vec.h"
#include <vector>

class Dungeon;
using Path = std::vector<Vec>;

Path breadth_first(const Dungeon& dungeon, const Vec& start, const Vec& stop);
