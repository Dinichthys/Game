#include "client/client.hpp"

#include <limits>
#include <iostream>

#include "game/game.hpp"

namespace client {

static const size_t kSpeed = 50;

static const size_t kDefaultSpeed = 10;

static const std::string kAnimationRightFirst   = "data/Guy/Right1.png";
static const std::string kAnimationRightSecond  = "data/Guy/Right2.png";
static const std::string kAnimationLeftFirst    = "data/Guy/Left1.png";
static const std::string kAnimationLeftSecond   = "data/Guy/Left2.png";
static const std::string kAnimationUpFirst      = "data/Guy/Up1.png";
static const std::string kAnimationUpSecond     = "data/Guy/Up2.png";
static const std::string kAnimationDownFirst    = "data/Guy/Down1.png";
static const std::string kAnimationDownSecond   = "data/Guy/Down2.png";

static size_t ManhattanDistance(const math::Vec2u &a, const math::Vec2u &b);

void Client::Draw(sf::RenderWindow &window) {
    game_->GetServer()->SendMsg(id_, kDrawStr, game::kGamePrefix);
    image_.Draw(window);
};

void Client::Animate() {
    game_->GetServer()->SendMsg(id_, kAnimateStr, game::kGamePrefix);
};

void Client::Action() {
    game_->GetServer()->SendMsg(id_, kActionStr, game::kGamePrefix);
};

void Client::SetPos(math::Vec2u new_pos) {
    pos_ = new_pos;
    image_.SetPos(new_pos);

    std::ostringstream msg;
    msg << kSetPosStr << ' ' << new_pos.x_ << ' ' << new_pos.y_;
    game_->GetServer()->SendMsg(id_, msg.str(), game::kGamePrefix);
};

void ServerClient::SetServer(server::Server *server) {
    server_ = server;
    server->SendMsg(game::kGamePrefix, game::kAddClientStr
        + ' ' + std::to_string(pos_.x_)
        + ' ' + std::to_string(pos_.y_), id_);
};

void ServerClient::Animate() {
    std::string files[2] = {kClientImageFileName, kClientImageFileName};
    math::Vec2f dir = {0, 0};
    switch(direction_) {
        case client::Direction::kDown : {
            if (counter_frames_ == 0) {
                server_->SendMsg(game::kGamePrefix, game::kImageStr
                    + ' ' + kImageSetPosStr
                    + ' ' + std::to_string(pos_.x_)
                    + ' ' + std::to_string(pos_.y_ + 1), id_);
            }
            dir.y_ = -static_cast<double>(game::kElemSize) / static_cast<double>(game::kAnimationFramesNum);
            files[0] = kAnimationDownFirst;
            files[1] = kAnimationDownSecond;
            break;
        };
        case client::Direction::kUp : {
            if (counter_frames_ == 0) {
                server_->SendMsg(game::kGamePrefix, game::kImageStr
                    + ' ' + kImageSetPosStr
                    + ' ' + std::to_string(pos_.x_)
                    + ' ' + std::to_string(pos_.y_ - 1), id_);
            }
            dir.y_ = static_cast<double>(game::kElemSize) / static_cast<double>(game::kAnimationFramesNum);
            files[0] = kAnimationUpFirst;
            files[1] = kAnimationUpSecond;
            break;
        };
        case client::Direction::kLeft : {
            if (counter_frames_ == 0) {
                server_->SendMsg(game::kGamePrefix, game::kImageStr
                    + ' ' + kImageSetPosStr
                    + ' ' + std::to_string(pos_.x_ + 1)
                    + ' ' + std::to_string(pos_.y_), id_);
            }
            dir.x_ = -static_cast<double>(game::kElemSize) / static_cast<double>(game::kAnimationFramesNum);
            files[0] = kAnimationLeftFirst;
            files[1] = kAnimationLeftSecond;
            break;
        };
        case client::Direction::kRight : {
            if (counter_frames_ == 0) {
                server_->SendMsg(game::kGamePrefix, game::kImageStr
                    + ' ' + kImageSetPosStr
                    + ' ' + std::to_string(pos_.x_ - 1)
                    + ' ' + std::to_string(pos_.y_), id_);
            }
            dir.x_ = static_cast<double>(game::kElemSize) / static_cast<double>(game::kAnimationFramesNum);
            files[0] = kAnimationRightFirst;
            files[1] = kAnimationRightSecond;
            break;
        };
        default:
            return;
    }

    if (counter_frames_ == 0) {
        server_->SendMsg(game::kGamePrefix, game::kAddTopLevelImageStr, id_);
    }

    server_->SendMsg(game::kGamePrefix, game::kImageStr
        + ' ' + kImageMoveStr
        + ' ' + std::to_string(dir.x_)
        + ' ' + std::to_string(dir.y_), id_);

    server_->SendMsg(game::kGamePrefix, game::kImageStr
        + ' ' + kImageLoadFromFileStr
        + ' ' + files[counter_frames_ % 2], id_);

    counter_frames_++;

    if (counter_frames_ == game::kAnimationFramesNum - 1) {
        counter_frames_ = 0;
        direction_ = Direction::kInvalid;

        server_->SendMsg(game::kGamePrefix, game::kImageStr
            + ' ' + kImageLoadFromFileStr
            + ' ' + kClientImageFileName, id_);

        server_->SendMsg(game::kGamePrefix, game::kImageStr
            + ' ' + kImageSetPosStr
            + ' ' + std::to_string(pos_.x_)
            + ' ' + std::to_string(pos_.y_), id_);

        server_->SendMsg(game::kGamePrefix, game::kEraseTopLevelImageStr, id_);
    }
};

void ServerClient::Action() {
    if (analyzed_) {
        return;
    }

    analyzed_ = true;
    Move();
};

void ServerClient::Move() {
    size_t boxes_num = 0;
    server_->SendMsg(game::kGamePrefix, game::kGetBoxesNumStr, id_);
    std::istringstream(received_msg_) >> boxes_num;

    size_t min_distance = std::numeric_limits<size_t>::max();
    math::Vec2u pos = {0, 0};

    math::Vec2u box_pos;
    for (size_t i = 0; i < boxes_num; i++) {
        server_->SendMsg(game::kGamePrefix, game::kGetBoxPosStr, id_);
        std::istringstream(received_msg_) >> box_pos.x_ >> box_pos.y_;
        size_t distance = ManhattanDistance(box_pos, pos_);

        if (distance < min_distance) {
            min_distance = distance;
            pos = box_pos;
        }
    }

    int32_t tile_type;
    server_->SendMsg(game::kGamePrefix, game::kGetTypeStr
                    + ' ' + std::to_string(pos_.x_)
                    + ' ' + std::to_string(pos_.y_), id_);
    std::istringstream(received_msg_) >> tile_type;
    if (min_distance == 1 && tile_type != game::map::Type::kBomb) {
        server_->SendMsg(game::kGamePrefix, game::kAddBombStr
                        + ' ' + std::to_string(pos_.x_)
                        + ' ' + std::to_string(pos_.y_), id_);
        return;
    }

    math::Vec2s dir[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    Direction dir_type[4] = {Direction::kRight, Direction::kLeft, Direction::kUp, Direction::kDown};

    int neigh[4] = {};

    for (size_t i = 0; i < 4; i++) {
        server_->SendMsg(game::kGamePrefix, game::kGetTypeStr
                        + ' ' + std::to_string(pos_.x_ + dir[i].x_)
                        + ' ' + std::to_string(pos_.y_ + dir[i].y_), id_);
        std::istringstream(received_msg_) >> neigh[i];
    }
    if (pos_.x_ < pos.x_ && neigh[0] == game::map::Type::kFree) {
        server_->SendMsg(game::kGamePrefix, game::kMoveStr
                        + ' ' + std::to_string(dir[0].x_)
                        + ' ' + std::to_string(dir[0].y_), id_);
        direction_ = dir_type[0];
        return;
    }
    if (pos_.x_ > pos.x_ && neigh[1]== game::map::Type::kFree) {
        server_->SendMsg(game::kGamePrefix, game::kMoveStr
                        + ' ' + std::to_string(dir[1].x_)
                        + ' ' + std::to_string(dir[1].y_), id_);
        direction_ = dir_type[1];
        return;
    }
    if (pos_.y_ < pos.y_ && neigh[2] == game::map::Type::kFree) {
        server_->SendMsg(game::kGamePrefix, game::kMoveStr
                        + ' ' + std::to_string(dir[2].x_)
                        + ' ' + std::to_string(dir[2].y_), id_);
        direction_ = dir_type[2];
        return;
    }
    if (pos_.y_ > pos.y_ && neigh[3] == game::map::Type::kFree) {
        server_->SendMsg(game::kGamePrefix, game::kMoveStr
                        + ' ' + std::to_string(dir[3].x_)
                        + ' ' + std::to_string(dir[3].y_), id_);
        direction_ = dir_type[3];
        return;
    }

    for (size_t i = 0; i < 4; i++) {
        if (neigh[i] == game::map::Type::kFree) {
            server_->SendMsg(game::kGamePrefix, game::kMoveStr
                            + ' ' + std::to_string(dir[i].x_)
                            + ' ' + std::to_string(dir[i].y_), id_);
            direction_ = dir_type[i];
            return;
        }
    }
};

void ServerClient::Draw() {
    analyzed_ = false;
};

void ServerClient::SetPos(std::istringstream &str) {
    str >> pos_.x_ >> pos_.y_;
};

static size_t ManhattanDistance(const math::Vec2u &a, const math::Vec2u &b) {
    return std::abs(int64_t(b.x_) - int64_t(a.x_)) + std::abs(int64_t(b.y_) - int64_t(a.y_));
};

};
