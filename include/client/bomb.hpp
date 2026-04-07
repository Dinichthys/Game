#pragma once

#include "object.hpp"

#include "image/image.hpp"

namespace client {

static const std::string kBombImageFileName = "data/Bomb.png";

class Bomb : public Object {
    private:
        image::Image image_;

    public:
        Bomb(const math::Vec2u &pos)
            :Object(pos), image_(pos, kBombImageFileName) {};

        ~Bomb() = default;

        virtual void Draw(sf::RenderWindow &window) {
            image_.Draw(window);
        };

        virtual void Action() {};

        virtual game::map::Type GetType() const {
            return game::map::Type::kBomb;
        };
};

};
