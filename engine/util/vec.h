#pragma once

#include <ostream>
#include <functional>
#include <array>

class Vec {
public:
    int x{0}, y{0};
};

bool operator<(const Vec& a, const Vec& b);
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
        void hash_combine(std::size_t& seed, int value) const {
            // from boost hash_combine docs
            seed ^= hash<int>{}(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }

        size_t operator()(const Vec& p) const {
            std::size_t seed = 0;
            hash_combine(seed, p.x);
            hash_combine(seed, p.y);
            return seed;
        }
    };
}

// cartesian directions
constexpr std::array<Vec, 4> Directions = {Vec{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
