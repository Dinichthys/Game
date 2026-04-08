#pragma once

#include "object.hpp"

namespace client {

static const std::string kWallImageFileName = "data/Wall.png";

class Wall : public Object {
    public:
        Wall(const math::Vec2u &pos)
            :Object(pos) {
            image_.LoadImageFromFile(kWallImageFileName);
        };

        ~Wall() = default;

        virtual void Draw(sf::RenderWindow &window) {
            image_.Draw(window);
        };

        virtual game::map::Type GetType() const {
            return game::map::Type::kWall;
        };
};

};
