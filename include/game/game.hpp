#pragma once

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "client/client.hpp"

#include "game/food.hpp"

namespace game {

class Game {
    private:
        std::vector<::client::Client> clients_;
        std::vector<Food> foods_;

    public:
        Game() = default;

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
};

static const size_t kWindowWidth = 1080;
static const size_t kWindowHeight = 720;

void RunGame();

};
