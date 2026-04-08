#pragma once

#include <SFML/Graphics.hpp>

#include "math/vertex.hpp"

namespace image {

class Image {
    private:
        bool uploaded_;

        sf::Sprite sprite_;
        sf::Texture texture_;

        math::Rect2f rect_info_;

        std::vector<unsigned char> data_;
        math::Vec2u data_size_;

    public:
        Image(const math::Vec2u &pos);

        void LoadImageFromFile(const std::string &file_name);

        void Draw(sf::RenderWindow &window) {
            window.draw(sprite_);
        };

        void SetPos(const math::Vec2u &new_pos);

    private:
        void ImageDataRedraw();
        void SetPicture(const std::string& file_name);
};

};
