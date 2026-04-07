#pragma once

#include "object.hpp"

#include "image/image.hpp"

namespace client {

static const std::string kFreeImageFileName = "data/Grass.png";

class Free : public Object {
    private:
        image::Image image_;

    public:
        Free(const math::Vec2u &pos)
            :Object(pos), image_(pos, kFreeImageFileName) {};

        ~Free() = default;

        virtual void Draw(sf::RenderWindow &window) {
            image_.Draw(window);
        };

        virtual void Action() {};

};

};
