#pragma once

#include <SFML/Graphics.hpp>

#include "math/vertex.hpp"

#include "game/map.hpp"

namespace game {

class Game;

};

namespace client {

class Object {
    private:
        game::Game* game_;
        math::Vec2u pos_;

    public:
        Object(const math::Vec2u &pos)
            :game_(nullptr), pos_(pos) {};

        virtual ~Object() {};

        virtual void Draw(sf::RenderWindow &window) = 0;

        virtual void Action() = 0;

        virtual game::map::Type GetType() const = 0;

        size_t GetX() {
            return pos_.x_;
        };

        size_t GetY() {
            return pos_.y_;
        };

        void SetGame(::game::Game *game) {
            game_ = game;
        };
};

};
