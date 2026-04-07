#pragma once

#include <stdlib.h>

#include "client/object.hpp"

namespace game {

namespace map {

enum Type {
    kWall,
    kFree,
    kClient,
    kBomb,
    kFire
};

static constexpr const size_t kMapWidth = 21;
static constexpr const size_t kMapHeight = 13;

static const std::vector<Type> kMap = {
    kWall, kWall, kWall, kWall, kWall, kWall, kWall, kWall, kWall, kWall, kWall, kWall, kWall, kWall, kWall, kWall, kWall, kWall, kWall, kWall, kWall,
    kWall, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kWall,
    kWall, kFree, kWall, kFree, kWall, kFree, kWall, kFree, kWall, kFree, kWall, kFree, kWall, kFree, kWall, kFree, kWall, kFree, kWall, kFree, kWall,
    kWall, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kWall,
    kWall, kFree, kWall, kFree, kWall, kFree, kWall, kFree, kWall, kFree, kWall, kFree, kWall, kFree, kWall, kFree, kWall, kFree, kWall, kFree, kWall,
    kWall, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kWall,
    kWall, kFree, kWall, kFree, kWall, kFree, kWall, kFree, kWall, kFree, kWall, kFree, kWall, kFree, kWall, kFree, kWall, kFree, kWall, kFree, kWall,
    kWall, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kWall,
    kWall, kFree, kWall, kFree, kWall, kFree, kWall, kFree, kWall, kFree, kWall, kFree, kWall, kFree, kWall, kFree, kWall, kFree, kWall, kFree, kWall,
    kWall, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kWall,
    kWall, kFree, kWall, kFree, kWall, kFree, kWall, kFree, kWall, kFree, kWall, kFree, kWall, kFree, kWall, kFree, kWall, kFree, kWall, kFree, kWall,
    kWall, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kFree, kWall,
    kWall, kWall, kWall, kWall, kWall, kWall, kWall, kWall, kWall, kWall, kWall, kWall, kWall, kWall, kWall, kWall, kWall, kWall, kWall, kWall, kWall,
};

};

};
