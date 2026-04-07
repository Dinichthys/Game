#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "math/vertex.hpp"

namespace game {

class Game;

};

namespace client {

class Object {
    private:
        ::game::Game* game_;
        ::math::Vertex pos_;

    public:
        Object();

        Object(const ::math::Vertex &pos);

        Object(const ::math::Vertex &pos, double radius);

        virtual void Draw(sf::RenderWindow &window);

        virtual void Action();

        double GetX() {
            return pos_.GetX();
        };

        double GetY() {
            return pos_.GetY();
        };

        void SetGame(::game::Game *game) {
            game_ = game;
        };
};

};
