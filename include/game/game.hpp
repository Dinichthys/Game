#pragma once

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "client/object.hpp"
#include "client/client.hpp"
#include "client/wall.hpp"
#include "client/free.hpp"
#include "client/box.hpp"
#include "client/bomb.hpp"
#include "client/fire.hpp"

#include "map.hpp"

namespace game {

struct MapElem {
    client::Object *top;
    client::Object *bottom;
};

class Game {
    private:
        std::vector<client::Client *> clients_;
        std::vector<client::Box *> boxes_;

        std::vector<MapElem> map_;

    public:
        Game()
            :clients_(), boxes_() {
            for (size_t y = 0; y < map::kMapHeight; y++) {
                for (size_t x = 0; x < map::kMapWidth; x++) {
                    switch(map::kMap[x + y * map::kMapWidth]) {
                        case map::Type::kBomb : {
                            map_.push_back({new client::Bomb({x, y}), nullptr});
                            break;
                        };
                        case map::Type::kClient : {
                            map_.push_back({new client::Client({x, y}), nullptr});
                            break;
                        };
                        case map::Type::kFire : {
                            map_.push_back({new client::Fire({x, y}), nullptr});
                            break;
                        };
                        case map::Type::kBox : {
                            map_.push_back({new client::Box({x, y}), nullptr});
                            break;
                        };
                        case map::Type::kFree : {
                            map_.push_back({nullptr, new client::Free({x, y})});
                            break;
                        };
                        case map::Type::kWall : {
                            map_.push_back({new client::Wall({x, y}), nullptr});
                            break;
                        };
                    }
                }
            }
        };

        ~Game() {
            for (auto elem : map_) {
                delete elem.top;
                delete elem.bottom;
            }
        };

        void AddClient(client::Client *c) {
            auto &elem = map_[c->GetX() + c->GetY() * map::kMapWidth];
            if (elem.top != nullptr) {
                delete elem.top;
            }
            c->SetGame(this);
            elem.top = c;
            clients_.push_back(c);
        };

        void AddBox(client::Box *b) {
            auto &elem = map_[b->GetX() + b->GetY() * map::kMapWidth];
            if (elem.top != nullptr) {
                delete elem.top;
            }
            b->SetGame(this);
            elem.top = b;
            boxes_.push_back(b);
        };

        void Draw(sf::RenderWindow &window) {
            DrawMap(window);
        };

        void ClientsAction() {
            for (auto c : clients_) {
                c->Action();
            }
        };

        std::vector<client::Client *> &GetClients() {
            return clients_;
        };

        std::vector<client::Box *> &GetFoods() {
            return boxes_;
        };

        void GenerateBoxes(size_t number);

        void GenerateClients();

    private:
        void DrawMap(sf::RenderWindow &window) {
            for (auto &elem : map_) {
                if (elem.bottom) {
                    elem.bottom->Draw(window);
                }
                if (elem.top) {
                    elem.top->Draw(window);
                }
            }
        };
};

static const size_t kElemSize = 50;

static const size_t kWindowWidth = kElemSize * map::kMapWidth;
static const size_t kWindowHeight = kElemSize * map::kMapHeight;

void RunGame();

};
