#include "client/bomb.hpp"

#include "game/game.hpp"

namespace client {

static const size_t kRadiusBoom = 3;

void Bomb::Boom() {
    bool dir[4] = {true, true, true, true};

    for (size_t i = 1; i < kRadiusBoom; i++) {
        if (dir[0]) {
            dir[0] = game_->Boom({pos_.x_ + i, pos_.y_});
        }
        if (dir[1]) {
            dir[1] = game_->Boom({pos_.x_ - i, pos_.y_});
        }
        if (dir[2]) {
            dir[2] = game_->Boom({pos_.x_, pos_.y_ + i});
        }
        if (dir[3]) {
            dir[3] = game_->Boom({pos_.x_, pos_.y_ - i});
        }
    }

    game_->RemoveObj(this);
};

};
