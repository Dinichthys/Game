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

void Client::Animate() {
    std::string files[2] = {kClientImageFileName, kClientImageFileName};
    math::Vec2f dir = {0, 0};
    switch(direction_) {
        case client::Direction::kDown : {
            if (counter_frames_ == 0) {
                image_.SetPos({pos_.x_, pos_.y_ + 1});
            }
            dir.y_ = -static_cast<double>(game::kElemSize) / static_cast<double>(game::kAnimationFramesNum);
            files[0] = kAnimationDownFirst;
            files[1] = kAnimationDownSecond;
            break;
        };
        case client::Direction::kUp : {
            if (counter_frames_ == 0) {
                image_.SetPos({pos_.x_, pos_.y_ - 1});
            }
            dir.y_ = static_cast<double>(game::kElemSize) / static_cast<double>(game::kAnimationFramesNum);
            files[0] = kAnimationUpFirst;
            files[1] = kAnimationUpSecond;
            break;
        };
        case client::Direction::kLeft : {
            if (counter_frames_ == 0) {
                image_.SetPos({pos_.x_ + 1, pos_.y_});
            }
            dir.x_ = -static_cast<double>(game::kElemSize) / static_cast<double>(game::kAnimationFramesNum);
            files[0] = kAnimationLeftFirst;
            files[1] = kAnimationLeftSecond;
            break;
        };
        case client::Direction::kRight : {
            if (counter_frames_ == 0) {
                image_.SetPos({pos_.x_ - 1, pos_.y_});
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
        game_->AddTopLevelImage(&image_);
    }

    image_.Move(dir);
    image_.LoadImageFromFile(files[counter_frames_ % 2]);

    counter_frames_++;

    if (counter_frames_ == game::kAnimationFramesNum - 1) {
        counter_frames_ = 0;
        direction_ = Direction::kInvalid;
        image_.LoadImageFromFile(kClientImageFileName);
        image_.SetPos(pos_);
        game_->EraseTopLevelImage(&image_);
    }
};

void Client::Action() {
    if (analyzed_) {
        return;
    }
    analyzed_ = true;
    Move();
};

void Client::Move() {
    auto &boxes = game_->GetBoxes();

    size_t min_distance = std::numeric_limits<size_t>::max();
    math::Vec2u pos = {0, 0};

    for (auto &b : boxes) {
        size_t distance = ManhattanDistance(b->GetPos(), pos_);

        if (distance < min_distance) {
            min_distance = distance;
            pos = b->GetPos();
        }
    }

    if (min_distance == 1 && game_->GetType(pos_) != game::map::Type::kBomb) {
        game_->AddBomb(pos_);
        return;
    }

    math::Vec2s dir[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    Direction dir_type[4] = {Direction::kRight, Direction::kLeft, Direction::kUp, Direction::kDown};

    game::map::Type neigh[4] = {
        game_->GetType({pos_.x_ + 1, pos_.y_}), // r
        game_->GetType({pos_.x_ - 1, pos_.y_}), // l
        game_->GetType({pos_.x_, pos_.y_ + 1}), // t
        game_->GetType({pos_.x_, pos_.y_ - 1}), // b
    };

    if (pos_.x_ < pos.x_ && neigh[0] == game::map::Type::kFree) {
        game_->Move(this, dir[0]);
        direction_ = dir_type[0];
        return;
    }
    if (pos_.x_ > pos.x_ && neigh[1]== game::map::Type::kFree) {
        game_->Move(this, dir[1]);
        direction_ = dir_type[1];
        return;
    }
    if (pos_.y_ < pos.y_ && neigh[2] == game::map::Type::kFree) {
        game_->Move(this, dir[2]);
        direction_ = dir_type[2];
        return;
    }
    if (pos_.y_ > pos.y_ && neigh[3] == game::map::Type::kFree) {
        game_->Move(this, dir[3]);
        direction_ = dir_type[3];
        return;
    }

    for (size_t i = 0; i < 4; i++) {
        if (neigh[i] == game::map::Type::kFree) {
            game_->Move(this, dir[i]);
            direction_ = dir_type[i];
            return;
        }
    }
};

static size_t ManhattanDistance(const math::Vec2u &a, const math::Vec2u &b) {
    return std::abs(int64_t(b.x_) - int64_t(a.x_)) + std::abs(int64_t(b.y_) - int64_t(a.y_));
};

// void Client::Eat() {
//     auto &foods = game_->GetFoods();
//
//     for (size_t i = 0; i < foods.size(); i++) {
//         if ((foods[i].GetPos() - pos_).Module() < radius_ + game::kFoodRadius) {
//             radius_ += foods[i].GetWeight();
//             foods.erase(foods.begin() + i);
//             i--;
//         }
//     }
// };

};
