#pragma once

#include <stdlib.h>

namespace game {

namespace map {

enum Type {
    kWall,
    kFree,
    kClient,
    kBomb
};

struct Elem {
    Type type;
    Object *object;
};

static constexpr const size_t kMapWidth = 21;
static constexpr const size_t kMapHeight = 13;

static const Elem Map[kMapHeight][kMapWidth] = {
    {{kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr},},
    {{kWall, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kWall, nullptr},},
    {{kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr},},
    {{kWall, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kWall, nullptr},},
    {{kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr},},
    {{kWall, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kWall, nullptr},},
    {{kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr},},
    {{kWall, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kWall, nullptr},},
    {{kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr},},
    {{kWall, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kWall, nullptr},},
    {{kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr}, {kFree, nullptr}, {kWall, nullptr},},
    {{kWall, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kFree, nullptr}, {kWall, nullptr},},
    {{kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr}, {kWall, nullptr},},
};

};

};
