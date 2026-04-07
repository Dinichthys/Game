#pragma once

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "client/client.hpp"
#include "client/object.hpp"
#include "client/wall.hpp"
#include "client/free.hpp"

#include "game/food.hpp"

#include "map.hpp"

namespace game {

class Game {
    private:
        std::vector<::client::Client> clients_;
        std::vector<Food> foods_;

        std::vector<client::Object *> map_;

    public:
        Game()
            :clients_(), foods_() {
            for (size_t y = 0; y < map::kMapHeight; y++) {
                for (size_t x = 0; x < map::kMapWidth; x++) {
                    switch(map::kMap[x + y * map::kMapWidth]) {
                        case map::Type::kBomb : {
                            break;
                        };
                        case map::Type::kClient : {
                            break;
                        };
                        case map::Type::kFire : {
                            break;
                        };
                        case map::Type::kFree : {
                            map_.push_back(new client::Free({x, y}));
                            break;
                        };
                        case map::Type::kWall : {
                            map_.push_back(new client::Wall({x, y}));
                            break;
                        };
                    }
                }
            }
        };

        ~Game() {
            for (auto elem : map_) {
                delete elem;
            }
        };

        void AddClient(::client::Client &c) {
            c.SetGame(this);
            clients_.push_back(c);
        };
        void AddClient(::client::Client &&c) {
            c.SetGame(this);
            clients_.push_back(c);
        };

        void AddFood(Food &&f) {
            foods_.push_back(f);
        };

        void Draw(sf::RenderWindow &window) {
            DrawMap(window);
            DrawFoods(window);
            DrawClients(window);
        };

        void ClientsAction() {
            for (auto &c : clients_) {
                c.Action();
            }
        };

        std::vector<::client::Client> &GetClients() {
            return clients_;
        };

        std::vector<Food> &GetFoods() {
            return foods_;
        };

        void GenerateFood(size_t number);

        void GenerateClients(size_t number);

    private:
        void DrawClients(sf::RenderWindow &window) {
            for (auto &c : clients_) {
                c.Draw(window);
            }
        };

        void DrawFoods(sf::RenderWindow &window) {
            for (auto &f : foods_) {
                f.Draw(window);
            }
        };

        void DrawMap(sf::RenderWindow &window) {
            for (auto &elem : map_) {
                elem->Draw(window);
            }
        };
};

static const size_t kElemSize = 50;

static const size_t kWindowWidth = kElemSize * map::kMapWidth;
static const size_t kWindowHeight = kElemSize * map::kMapHeight;

void RunGame();

};
