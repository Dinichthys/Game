#pragma once

#include <map>
#include <string>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "math/vertex.hpp"

#include "game/map.hpp"

#include "image/image.hpp"

namespace game {

class Game;

};

namespace client {

class Object {
    protected:
        game::Game *game_;
        math::Vec2u pos_;

        image::Image image_;

    public:
        Object(const math::Vec2u &pos)
            :game_(nullptr), pos_(pos), image_(pos) {};

        virtual ~Object() {};

        virtual void Draw(sf::RenderWindow &window) = 0;

        virtual void Action() {};

        virtual void Animate() {};

        virtual game::map::Type GetType() const = 0;

        math::Vec2u GetPos() const {
            return pos_;
        };

        size_t GetX() const {
            return pos_.x_;
        };

        size_t GetY() const {
            return pos_.y_;
        };

        void SetGame(game::Game *game) {
            game_ = game;
        };

        virtual void SetPos(math::Vec2u new_pos) {
            pos_ = new_pos;
            image_.SetPos(new_pos);
        };

        image::Image *GetImage() {
            return &image_;
        };

        void UpdateTexture(std::istringstream &msg);
        void SetPos(std::istringstream &msg);
        void Move(std::istringstream &msg);
        void LoadFromFile(std::istringstream &msg);
};

enum ImageMethodType {
    kImageSetPos,
    kImageMove,
    kImageLoadFromFile
};

static const std::string kImageSetPosStr        = "SetPos";
static const std::string kImageMoveStr          = "Move";
static const std::string kImageLoadFromFileStr  = "LoadFromFile";

static const std::map<std::string, ImageMethodType> kImageStrToMethod {
    {kImageSetPosStr, kImageSetPos},
    {kImageMoveStr, kImageMove},
    {kImageLoadFromFileStr, kImageLoadFromFile}
};

};
