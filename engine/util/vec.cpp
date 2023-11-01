#include "vec.h"
#include <cmath>


bool operator==(const Vec& a, const Vec& b) {
    return a.x == b.x && a.y == b.y;
}

bool operator!=(const Vec& a, const Vec& b) {
    return !(a == b);
}

Vec operator+(const Vec& a, const Vec& b) {
    return Vec{a.x+b.x, a.y+b.y};
}

Vec& operator+=(Vec& a, const Vec& b) {
    a.x += b.x;
    a.y += b.y;
    return a;
}

Vec operator-(const Vec& a, const Vec& b) {
    return Vec{a.x-b.x, a.y-b.y};
}

Vec operator*(const Vec& v, int scalar) {
    return Vec{v.x*scalar, v.y*scalar};
}

Vec operator*(int scalar, const Vec& v) {
    return v*scalar;
}

Vec operator/(const Vec& v, int scalar) {
    if (scalar == 0) {
        throw std::runtime_error("Cannot divide a Vec by zero");
    }
    return Vec{v.x/scalar, v.y/scalar};
}

std::ostream& operator<<(std::ostream& os, const Vec& vec) {
    return os << "(" << vec.x << ", " << vec.y << ")";
}

double distance(const Vec& a, const Vec& b) {
    auto difference = a - b;
    return std::sqrt(std::pow(difference.x, 2) + std::pow(difference.y, 2));
}
