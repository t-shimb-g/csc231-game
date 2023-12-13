#pragma once

#include "vec.h"

#include <vector>
#include <optional>
#include <set>


// forward declarations
class Dungeon;

// Albert Ford's Symmetric Shadow-casting
class Quadrant {
public:
    enum class Cardinal { North, East, South, West };

    Quadrant();
    Quadrant(Cardinal direction, const Vec& origin);

    // converts tile coords (row, col) to dungeon coords (x, y)
    // for the given Cardinal direction
    [[nodiscard]] Vec transform(const Vec& tile) const;
        
    Cardinal direction;
    Vec origin;
};

using Fraction = Vec;

    
class Row {
public:
    Row(int depth, const Fraction& start_slope, const Fraction& end_slope);
    [[nodiscard]] std::vector<Vec> tiles() const;
    [[nodiscard]] Row next() const;
        
    int depth;
    Fraction start_slope, end_slope;
};
    
class FieldOfView {
public:
    explicit FieldOfView(const Dungeon& dungeon);

    const std::set<Vec>& compute(const Vec& position);
    void mark_visible(const Vec& position);

    // helper functions for dealing with current quadrant
    void reveal(const Vec& tile);
    bool is_wall(std::optional<Vec> tile);
    bool is_floor(std::optional<Vec> tile);
    void scan(Row row);

private:
    const Dungeon& dungeon;
    std::set<Vec> visible;
    Quadrant quadrant;
};

Fraction slope(const Vec& tile);
bool is_symmetric(const Row& row, const Vec& tile);
int round_ties_up(double n);
int round_ties_down(double n);
double to_decimal(const Fraction& fraction);
