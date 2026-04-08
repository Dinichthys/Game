#pragma once

#include "object.hpp"

#include "image/image.hpp"

namespace client {

static const std::string kBombImageFileName = "data/Bomb.png";

static const size_t kStartClockNum = 3;

class Bomb : public Object {
    private:
        size_t clock_;

    public:
        Bomb(const math::Vec2u &pos)
            :Object(pos){
            image_.LoadImageFromFile(kBombImageFileName);
            clock_ = kStartClockNum;
        };

        ~Bomb() = default;

        virtual void Draw(sf::RenderWindow &window) {
            image_.Draw(window);
        };

        virtual void Action() {
            clock_--;
            if (clock_ == 0) {
                Boom();
            }
        };

        virtual game::map::Type GetType() const {
            return game::map::Type::kBomb;
        };

    private:
        void Boom();
};

};
