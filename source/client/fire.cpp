#include "client/fire.hpp"

#include "game/game.hpp"

namespace client {

void Fire::Action() {
    if (drawn_) {
        game_->RemoveObj(this);
    }
};

};
