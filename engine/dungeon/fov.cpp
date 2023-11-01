#include "fov.h"
#include "dungeon.h"
#include <cmath>


Quadrant::Quadrant(Cardinal direction, const Vec& origin)
    :direction{direction}, origin{origin} {}

Vec Quadrant::transform(const Vec& tile) const {
    auto [row, col] = tile;
    if (direction == Cardinal::North) {
        return origin + Vec{col, -row};
    }
    else if (direction == Cardinal::South) {
        return origin + Vec{col, row};
    }
    else if (direction == Cardinal::East) {
        return origin + Vec{row, col};
    }
    else { // Cardinal::West
        return origin + Vec{-row, col};
    }
}


Row::Row(int depth, const Fraction& start_slope, const Fraction& end_slope)
    :depth{depth}, start_slope{start_slope}, end_slope{end_slope} {}

std::vector<Vec> Row::tiles() const {
    Fraction start{start_slope};
    start.x *= depth;
    int min_col = round_ties_up(to_decimal(start));
    Fraction end{end_slope};
    end.x *= depth;
    int max_col = round_ties_down(to_decimal(end));

    std::vector<Vec> tiles;
    for (int col = min_col; col <= max_col; ++col) {
        tiles.push_back({depth, col});
    }
    return tiles;
}
    
Row Row::next() const {
    return Row{depth + 1, start_slope, end_slope};
}


FieldOfView::FieldOfView(const Dungeon& dungeon)
    :dungeon{dungeon} {}

std::unordered_set<Vec> FieldOfView::compute(const Vec& position) {
    visible.clear();
    mark_visible(position);

    for (int i = 0; i < 4; ++i) {
        quadrant = Quadrant(static_cast<Quadrant::Cardinal>(i), position);
        auto first_row = Row{1, Fraction{-1, 1}, Fraction{1, 1}};
        scan(first_row);
    }

    return visible;
}

void FieldOfView::mark_visible(const Vec& position) {
    visible.insert(position);
}

void FieldOfView::reveal(const Vec& tile) {
    auto position = quadrant.transform(tile);
    mark_visible(position);
}
    
bool FieldOfView::is_wall(std::optional<Vec> tile) {
    if (!tile) {
        return false;
    }
    auto position = quadrant.transform(tile.value());
    return dungeon.is_blocking(position);
}
    
bool FieldOfView::is_floor(std::optional<Vec> tile) {
    if (!tile) {
        return false;
    }
    auto position = quadrant.transform(tile.value());
    return !dungeon.is_blocking(position);
}
    
void FieldOfView::scan(Row row) {
    std::optional<Vec> prev_tile;
    for (const auto& tile : row.tiles()) {
        if (is_wall(tile) || is_symmetric(row, tile)) {
            reveal(tile);
        }
            
        if (is_wall(prev_tile) && is_floor(tile)) {
            row.start_slope = slope(tile);
        }
            
        if (is_floor(prev_tile) && is_wall(tile)) {
            Row next_row = row.next();
            next_row.end_slope = slope(tile);
            scan(next_row);
        }

        prev_tile = tile;
    }

    if (is_floor(prev_tile)) {
        scan(row.next());
    }
}


Fraction slope(const Vec& tile) {
    auto [row_depth, col] = tile;
    return Fraction{2 * col - 1, 2 * row_depth};
}
    
bool is_symmetric(const Row& row, const Vec& tile) {
    auto [row_depth, col] = tile;
    Fraction start{row.start_slope};
    start.x *= row.depth;
    Fraction end{row.end_slope};
    end.x *= row.depth;
    return col >= to_decimal(start) && col <= to_decimal(end);
}
    
int round_ties_up(double n) {
    return std::floor(n + 0.5);
}
    
int round_ties_down(double n) {
    return std::ceil(n - 0.5);
}

double to_decimal(const Fraction& fraction) {
    return static_cast<double>(fraction.x) / fraction.y;
}

