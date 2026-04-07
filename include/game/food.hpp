#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "math/vertex.hpp"

namespace game {

static const size_t kFoodRadius = 5;
static const size_t kFoodMaxWeight = 100;
static const size_t kFoodMinWeight = 5;

class Food {
    private:
        math::Vec2f pos_;
        size_t weight_;

    public:
        Food(const math::Vec2f &pos, size_t weight)
            :pos_(pos), weight_(weight) {};

        size_t GetWeight() const {
            return weight_;
        };

        math::Vec2f GetPos() const {
            return pos_;
        };

        void Draw(sf::RenderWindow &window) {
            sf::CircleShape c(kFoodRadius);

            size_t color_num = size_t(rand() * 3ull) / RAND_MAX;
            size_t color = weight_ * 255 / kFoodMaxWeight;

            if (color_num == 0) {
                c.setFillColor(sf::Color(255, color, color));
            } else if (color_num == 1) {
                c.setFillColor(sf::Color(color, 255, color));
            } else {
                c.setFillColor(sf::Color(color, color, 255));
            }

            c.setPosition(pos_.GetX(), pos_.GetY());

            window.draw(c);
        };
};

};
