#pragma once

#include "object.hpp"

#include "image/image.hpp"

namespace client {

static const std::string kBoxImageFileName = "data/Box.png";

class Box : public Object {
    private:
        image::Image image_;

    public:
        Box(const math::Vec2u &pos)
            :Object(pos), image_(pos, kBoxImageFileName) {};

        ~Box() = default;

        virtual void Draw(sf::RenderWindow &window) {
            image_.Draw(window);
        };

        virtual void Action() {};

        virtual game::map::Type GetType() const {
            return game::map::Type::kBox;
        };
};

};
