#pragma once

#include "object.hpp"

#include "image/image.hpp"

namespace client {

static const std::string kBoxImageFileName = "data/Box.png";

class Box : public Object {
    public:
        Box(const math::Vec2u &pos)
            :Object(pos){
            image_.LoadImageFromFile(kBoxImageFileName);
        };

        ~Box() = default;

        virtual void Draw(sf::RenderWindow &window) {
            image_.Draw(window);
        };

        virtual game::map::Type GetType() const {
            return game::map::Type::kBox;
        };
};

};
