#pragma once

#include <math.h>

namespace math {

class Vertex {
    private:
        double x_;
        double y_;

    public:
        Vertex(double x, double y)
            :x_(x), y_(y) {};

        double &GetX() {
            return x_;
        };
        double &GetY() {
            return y_;
        };

        void Clamp(Vertex low, Vertex high) {
            x_ = (low.x_ < x_) ? ((x_ < high.x_) ? x_ : high.x_) : low.x_;
            y_ = (low.y_ < y_) ? ((y_ < high.y_) ? y_ : high.y_) : low.y_;
        };

        Vertex operator-(const Vertex &o) {
            return {x_ - o.x_, y_ - o.y_};
        };

        double SquareDistance() {
            return x_ * x_ + y_ * y_;
        };

        double Module() {
            return sqrt(SquareDistance());
        };
};

};
