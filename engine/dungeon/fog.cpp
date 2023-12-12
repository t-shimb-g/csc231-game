#include "fog.h"
#include "dungeon.h"

Fog::Fog(double brightness_seen)
    :brightness_seen{brightness_seen} {}    

void Fog::update_visibility(Dungeon& dungeon, const Vec& new_position) {
    position = new_position;
    for (Vec pos : visible_tiles) {
        dungeon.tiles(pos).visible = false;
    }
    previously_seen_tiles.reserve(previously_seen_tiles.size() + visible_tiles.size());
    previously_seen_tiles.merge(visible_tiles);
    visible_tiles = dungeon.calculate_fov(position);
    for (Vec pos : visible_tiles) {
        dungeon.tiles(pos).visible = true;
    }
}

double Fog::brightness(const Vec& location) const {
    if (visible_tiles.count(location)) {
        double dist = distance(position, location);
        double value = std::clamp(0.1*(dist-1), 0.0, brightness_seen);
        return value;
    }
    else if (previously_seen_tiles.count(location)) {
        return brightness_seen;
    }
    else {
        return 1;
    }
}
