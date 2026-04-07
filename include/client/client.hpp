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

class Client {
    private:
        ::game::Game* game_;
        ::math::Vertex pos_;
        double radius_;

    public:
        Client();

        Client(const ::math::Vertex &pos);

        Client(const ::math::Vertex &pos, double radius);

        void Draw(sf::RenderWindow &window) {
            sf::CircleShape c(radius_);

            c.setFillColor(sf::Color::Red);
            c.setPosition(pos_.GetX(), pos_.GetY());

            window.draw(c);
        };

        void Action();

        double GetRadius() {
            return radius_;
        };

        double GetX() {
            return pos_.GetX();
        };

        double GetY() {
            return pos_.GetY();
        };

        void SetGame(::game::Game *game) {
            game_ = game;
        };

    private:
        void Move();

        void Eat();
};

};
