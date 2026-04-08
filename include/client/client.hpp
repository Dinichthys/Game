#pragma once

#include "object.hpp"

#include "image/image.hpp"

namespace client {

static const std::string kClientImageFileName = "data/Guy.png";

enum Direction {
    kInvalid,
    kLeft,
    kRight,
    kUp,
    kDown
};

class Client : public Object {
    private:
        Direction direction_;
        bool analyzed_;
        size_t counter_frames_;

    public:
        Client(const math::Vec2u &pos)
            :Object(pos), direction_(Direction::kInvalid), analyzed_(false), counter_frames_(0) {
            image_.LoadImageFromFile(kClientImageFileName);
        };

        ~Client() = default;

        virtual void Draw(sf::RenderWindow &window) {
            analyzed_ = false;
            image_.Draw(window);
        };

        virtual void Action();

        virtual void Animate();

        virtual game::map::Type GetType() const {
            return game::map::Type::kClient;
        };

    private:
        void Move();
};

};
