#pragma once

#include "object.hpp"

#include "image/image.hpp"

namespace client {

static const std::string kWallImageFileName = "data/Wall.png";

class Wall : public Object {
    private:
        image::Image image_;

    public:
        Wall(const math::Vec2u &pos)
            :Object(pos), image_(pos, kWallImageFileName) {};

        ~Wall() = default;

        virtual void Draw(sf::RenderWindow &window) {
            image_.Draw(window);
        };

        virtual void Action() {};

};

};
