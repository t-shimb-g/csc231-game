#pragma once

#include "vec.h"
#include <unordered_set>

class Dungeon;

class Fog {
public:
    Fog(double brightness_seen=0.7);
    void update_visibility(Dungeon& dungeon, const Vec& position);

    double brightness(const Vec& location) const;
    
private:
    double brightness_seen;
    Vec position;
    std::unordered_set<Vec> visible_tiles, previously_seen_tiles;
};
