#include "image/image.hpp"

extern "C" {
    #define STB_IMAGE_IMPLEMENTATION
    #include "stb/stb_image.h"
}

#include "game/game.hpp"

namespace image {

static const size_t kRGBASizeEncoding = 4;

Image::Image(const math::Vec2u &pos, const std::string &file_name)
    :uploaded_(false), sprite_(), texture_(),
    rect_info_({{game::kElemSize, game::kElemSize}, {double(pos.x_ * game::kElemSize), double(pos.y_ * game::kElemSize)}}),
    data_(), data_size_() {
    SetPicture(file_name);
    ImageDataRedraw();
    sprite_.setTexture(texture_);
    sprite_.setPosition(rect_info_.pos_.x_, rect_info_.pos_.y_);
};

void Image::SetPicture(const std::string& file_name) {
    int n = 0, width = 0, height = 0;
    unsigned char* data = stbi_load(file_name.c_str(), &width, &height, &n, kRGBASizeEncoding);
    if (data == nullptr) {
        uploaded_ = false;
        return;
    }

    data_ = std::vector<unsigned char>(data, data + width * height * kRGBASizeEncoding);
    data_size_ = {size_t(width), size_t(height)};
    uploaded_ = true;

    stbi_image_free(data);
}

void Image::ImageDataRedraw() {
    sf::Image image;
    image.create(rect_info_.size_.x_, rect_info_.size_.y_);

    if (!uploaded_) {
        for (size_t x = 0; x < rect_info_.size_.x_; x++) {
            for (size_t y = 0; y < rect_info_.size_.y_; y++) {
                image.setPixel(x, y, sf::Color::Black);
            }
        }
        texture_.loadFromImage(image);
        return;
    }

    for (size_t x = 0; x < rect_info_.size_.x_; x++) {
        for (size_t y = 0; y < rect_info_.size_.y_; y++) {
            size_t cur_x = x * data_size_.x_ / rect_info_.size_.x_;
            size_t cur_y = y * data_size_.y_ / rect_info_.size_.y_;

            size_t index = kRGBASizeEncoding * (cur_y * data_size_.x_ + cur_x);
            image.setPixel(x, y, {
                data_[index + 0],
                data_[index + 1],
                data_[index + 2],
                data_[index + 3]
            });
        }
    }

    texture_.loadFromImage(image);
    return;
}

}
