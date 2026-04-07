#pragma once

#include "object.hpp"

#include "image/image.hpp"

namespace client {

static const std::string kFireImageFileName = "data/Fire.png";

class Fire : public Object {
    private:
        image::Image image_;

    public:
        Fire(const math::Vec2u &pos)
            :Object(pos), image_(pos, kFireImageFileName) {};

        ~Fire() = default;

        virtual void Draw(sf::RenderWindow &window) {
            image_.Draw(window);
        };

        virtual void Action() {};

        virtual game::map::Type GetType() const {
            return game::map::Type::kFire;
        };
};

};
