#ifndef CPP7_SURFACES_H
#define CPP7_SURFACES_H

#include <iostream>
#include <functional>
#include <cmath>
#include <numbers>
#include <utility>

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
    return [=](Point p) -> Real { return s > 0 ? std::floor(p.x / s) : 0; };
}

inline Surface checker(Real s = 1) {
    return [=](Point p) -> Real {
        return s > 0 &&
            std::abs(std::fmod(std::floor(p.x / s), 2)) ==
            std::abs(std::fmod(std::floor(p.y / s), 2))
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
        return s > 0 && std::abs(std::fmod(std::floor(
            std::sqrt(p.x * p.x + p.y * p.y) / s), 2)) == 0
            ? 1 : 0;
    };
}

inline Surface ellipse(Real a = 1, Real b = 1) {
    return [=](Point p) -> Real {
        return a > 0 && b > 0 &&
            (p.x * p.x) / (a * a) + (p.y * p.y) / (b * b) <= 1
            ? 1 : 0;
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
        return s > 0 && std::abs(std::fmod(std::ceil(p.x / s), 2)) == 1 ? 1 : 0;
    };
}

inline Surface rotate(const Surface& f, Real deg) {
    Real rad = (-1) * deg * std::numbers::pi_v<Real> / 180;

    return [=](Point p) -> Real {
        return std::invoke(f,
                           Point(p.x * std::cos(rad) - p.y * std::sin(rad),
                                 p.y * std::cos(rad) + p.x * std::sin(rad)));
    };
}

inline Surface translate(const Surface& f, Point v) {
    return [=](Point p) -> Real {
        return std::invoke(f, Point(p.x - v.x, p.y - v.y));
    };
}

inline Surface scale(const Surface& f, Point s) {
    return [=](Point p) -> Real {
        return std::invoke(f, Point(p.x / s.x, p.y / s.y));
    };
}

inline Surface invert(const Surface& f) {
    return [=](Point p) -> Real {
        return std::invoke(f, Point(p.y, p.x));
    };
}

inline Surface flip(const Surface& f) {
    return [=](Point p) -> Real {
        return std::invoke(f, Point(p.x * (-1), p.y));
    };
}

inline Surface mul(const Surface& f, Real c) {
    return [=](Point p) -> Real {
        return std::invoke(f, p) * c;
    };
}

inline Surface add(const Surface& f, Real c) {
    return [=](Point p) -> Real {
        return std::invoke(f, p) + c;
    };
}

template<typename Func, typename... ArgsFunc>
inline decltype(auto) evaluate(const Func& h, const ArgsFunc&... f) {
    return [=](auto p) -> decltype(auto) {
        return std::invoke(h, f(p)...);
    };
}

inline decltype(auto) compose() {
    return [](auto p) -> decltype(auto) {
        return p;
    };
}

template<typename Func, typename... ArgsFunc>
inline decltype(auto) compose(const Func& first, const ArgsFunc&... f) {
    return [=](auto p) -> decltype(auto) {
        return compose(f...)(std::invoke(first, p));
    };
}

#endif //CPP7_SURFACES_H
