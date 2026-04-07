#include "client/client.hpp"

#include <limits>

#include "game/game.hpp"

namespace client {

static const size_t kSpeed = 50;

static const size_t kDefaultSpeed = 10;

Client::Client()
    :game_(nullptr), pos_(0, 0), radius_(kSpeed) {}

Client::Client(const math::Vec2f &pos)
    :game_(nullptr), pos_(pos), radius_(kSpeed) {}

Client::Client(const math::Vec2f &pos, double radius)
    :game_(nullptr), pos_(pos), radius_(radius) {}

void Client::Action() {
    // Eat();

    // Move();
};

void Client::Move() {
    auto &clients = game_->GetClients();

    double max_r_eat = 0;
    double max_x_eat = 0;
    double max_y_eat = 0;

    double max_r_hunter = std::numeric_limits<double>::max();
    double max_x_hunter = 0;
    double max_y_hunter = 0;
    for (auto &c : clients) {
        double r = c.GetRadius();

        if ((r < radius_) && (r > max_r_eat)) {
            max_r_eat = r;
            max_x_eat = c.GetX();
            max_y_eat = c.GetY();
        } else if ((r > radius_) && (r < max_r_hunter)) {
            max_r_hunter = r;
            max_x_hunter = c.GetX();
            max_y_hunter = c.GetY();
        }
    }

    if (max_r_eat < radius_) {
        pos_.GetX() += (max_x_eat - pos_.GetX()) * kSpeed / radius_;
        pos_.GetY() += (max_y_eat - pos_.GetY()) * kSpeed / radius_;
    } else if (max_r_hunter > radius_) {
        pos_.GetX() -= (max_x_hunter - pos_.GetX()) * kSpeed / radius_;
        pos_.GetY() -= (max_y_hunter - pos_.GetY()) * kSpeed / radius_;
    } else {
        pos_.GetX() += kDefaultSpeed;
        pos_.GetY() += kDefaultSpeed;
    }

    pos_.Clamp({0, 0}, {game::kWindowWidth - 2 * radius_, game::kWindowHeight - 2 * radius_});
};

void Client::Eat() {
    auto &foods = game_->GetFoods();

    for (size_t i = 0; i < foods.size(); i++) {
        if ((foods[i].GetPos() - pos_).Module() < radius_ + game::kFoodRadius) {
            radius_ += foods[i].GetWeight();
            foods.erase(foods.begin() + i);
            i--;
        }
    }
};

};
