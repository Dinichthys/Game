#include "client/client.hpp"

#include <limits>

#include "game/game.hpp"

namespace client {

static const size_t kSpeed = 50;

static const size_t kDefaultSpeed = 10;

static size_t ManhattanDistance(const math::Vec2u &a, const math::Vec2u &b);

void Client::Animate(sf::RenderWindow &window) {

};

void Client::Action() {
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

    game::map::Type neigh[4] = {
        game_->GetType({pos_.x_ + 1, pos_.y_}), // r
        game_->GetType({pos_.x_ - 1, pos_.y_}), // l
        game_->GetType({pos_.x_, pos_.y_ + 1}), // t
        game_->GetType({pos_.x_, pos_.y_ - 1}), // b
    };

    if (pos_.x_ < pos.x_ && neigh[0] == game::map::Type::kFree) {
        game_->Move(this, dir[0]);
        return;
    }
    if (pos_.x_ > pos.x_ && neigh[1]== game::map::Type::kFree) {
        game_->Move(this, dir[1]);
        return;
    }
    if (pos_.y_ < pos.y_ && neigh[2] == game::map::Type::kFree) {
        game_->Move(this, dir[2]);
        return;
    }
    if (pos_.y_ > pos.y_ && neigh[3] == game::map::Type::kFree) {
        game_->Move(this, dir[3]);
        return;
    }

    for (size_t i = 0; i < 4; i++) {
        if (neigh[i] == game::map::Type::kFree) {
            game_->Move(this, dir[i]);
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
