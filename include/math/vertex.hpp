#pragma once

#include <math.h>

namespace math {

struct Vec2f {
    double x_;
    double y_;

    Vec2f(double x, double y)
        :x_(x), y_(y) {};

    double &GetX() {
        return x_;
    };
    double &GetY() {
        return y_;
    };

    void Clamp(Vec2f low, Vec2f high) {
        x_ = (low.x_ < x_) ? ((x_ < high.x_) ? x_ : high.x_) : low.x_;
        y_ = (low.y_ < y_) ? ((y_ < high.y_) ? y_ : high.y_) : low.y_;
    };

    Vec2f operator-(const Vec2f &o) {
        return {x_ - o.x_, y_ - o.y_};
    };
    Vec2f operator+(const Vec2f &o) {
        return {x_ + o.x_, y_ + o.y_};
    };

    double SquareDistance() {
        return x_ * x_ + y_ * y_;
    };

    double Module() {
        return sqrt(SquareDistance());
    };
};

struct Vec2u {
    size_t x_;
    size_t y_;
};

struct Vec2s {
    ssize_t x_;
    ssize_t y_;
};

struct Rect2f {
    Vec2f size_;
    Vec2f pos_;
};

};
