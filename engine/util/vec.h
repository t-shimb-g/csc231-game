#pragma once

#include <ostream>
#include <functional>
#include <array>

struct Vec {
    int x, y;
};


bool operator==(const Vec& a, const Vec& b);
bool operator!=(const Vec& a, const Vec& b);

Vec operator+(const Vec& a, const Vec& b);
Vec& operator+=(Vec& a, const Vec& b);
Vec operator-(const Vec& a, const Vec& b);
Vec operator*(const Vec& v, int scalar);
Vec operator*(int scalar, const Vec& v);
Vec operator/(const Vec& v, int scalar);

std::ostream& operator<<(std::ostream& os, const Vec& vec);

double distance(const Vec& a, const Vec& b);


namespace std {
    template<> struct hash<Vec> {
        size_t operator()(const Vec& p) const {
            return hash<int>{}(p.x) ^ (hash<int>{}(p.y) << 1);
        }
    };
}

// cartesian directions
constexpr std::array<Vec, 4> Directions = {Vec{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
