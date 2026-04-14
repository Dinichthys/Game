#include "client/object.hpp"

#include "image/image.hpp"

namespace client {

void Object::UpdateTexture(std::istringstream &msg) {
    std::string method;
    msg >> method;

    ImageMethodType type = kImageStrToMethod.at(method);
    switch(type) {
        case ImageMethodType::kImageSetPos :
            SetPos(msg);
            break;
        case ImageMethodType::kImageMove :
            Move(msg);
            break;
        case ImageMethodType::kImageLoadFromFile :
            LoadFromFile(msg);
            break;
    }
};

void Object::SetPos(std::istringstream &msg) {
    math::Vec2u pos;
    msg >> pos.x_ >> pos.y_;
    image_.SetPos(pos);
};

void Object::Move(std::istringstream &msg) {
    math::Vec2f dir{0, 0};
    msg >> dir.x_ >> dir.y_;
    image_.Move(dir);
};

void Object::LoadFromFile(std::istringstream &msg) {
    std::string file_name;
    msg >> file_name;
    image_.LoadImageFromFile(file_name);
};

};
