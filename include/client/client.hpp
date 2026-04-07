#pragma once

#include "object.hpp"

#include "image/image.hpp"

namespace client {

static const std::string kClientImageFileName = "data/Guy.png";

class Client : public Object {
    private:
        image::Image image_;

    public:
        Client(const math::Vec2u &pos)
            :Object(pos), image_(pos, kClientImageFileName) {};

        ~Client() = default;

        virtual void Draw(sf::RenderWindow &window) {
            image_.Draw(window);
        };

        virtual void Action();

        virtual game::map::Type GetType() const {
            return game::map::Type::kClient;
        };

    private:
        void Move();
};

};
