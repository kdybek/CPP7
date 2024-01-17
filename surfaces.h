#ifndef CPP7_SURFACES_H
#define CPP7_SURFACES_H

#include <iostream>
#include <functional>
#include <cmath>

#include "real.h"

/* Type Definitions */
class Point
{
public:
    const Real x;
    const Real y;

    Point() = delete;

    Point(Real x, Real y) : x(x), y(y) {}

    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << p.x << ' ' << p.y;
        return os;
    }
};

using Surface = std::function<Real(Point)>;

/* Library Functions */
inline Surface plain() {
    return [](Point p) -> Real { return 0; };
}

inline Surface slope() {
    return [](Point p) -> Real { return p.x; };
}

inline Surface steps(Real s = 1) {
    return [=](Point p) -> Real { return s > 0 ? std::floor(s / p.x) : 0; };
}

inline Surface checker(Real s = 1) {
    return [=](Point p) -> Real {
        return s > 0 &&
               (long) std::floor(s / p.x) % 2 == (long) std::floor(s / p.y) % 2
               ? 1 : 0;
    };
}

inline Surface sqr() {
    return [](Point p) -> Real { return p.x * p.x; };
}

inline Surface sin_wave() {
    return [](Point p) -> Real { return std::sin(p.x); };
}

inline Surface cos_wave() {
    return [](Point p) -> Real { return std::cos(p.x); };
}

inline Surface rings(Real s = 1) {
    return [=](Point p) -> Real {
        return s > 0 && (long) std::floor(
            s / std::sqrt(p.x * p.x + p.y * p.y)) % 2 == 0
            ? 1 : 0;
    };
}

inline Surface ellipse(Real a = 1, Real b = 1) {
    return [=](Point p) -> Real {
        return a > 0 && b > 0 && p.x / (a * a) + p.y / (b * b) <= 1 ? 1 : 0;
    };
}

inline Surface rectangle(Real a = 1, Real b = 1) {
    return [=](Point p) -> Real {
        return a > 0 && b > 0 &&
            std::abs(p.x) <= a && std::abs(p.y) <= b
            ? 1 : 0;
    };
}

inline Surface stripes(Real s = 1) {
    return [=](Point p) -> Real {
        return s > 0 && (long) std::ceil(s / p.x) % 2 == 1 ? 1 : 0;
    };
}

#endif //CPP7_SURFACES_H
