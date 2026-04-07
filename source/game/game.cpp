#include "game/game.hpp"

#include <stdlib.h>
#include <malloc.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

namespace game {

static const std::string kWindowName = "Bomber";

static const size_t kBoxesNumber = 100;

static const size_t kClientMaxRadius = 30;
static const size_t kClientMinRadius = 10;

void RunGame() {
    sf::RenderWindow window(sf::VideoMode (kWindowWidth, kWindowHeight), kWindowName);

    Game game;

    game.GenerateBoxes(kBoxesNumber);
    game.GenerateClients();

    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            }
        }
        window.clear();

        game.ClientsAction();

        game.Draw(window);

        window.display();

        usleep(1000000);
    }

    window.close();
}

void Game::GenerateBoxes(size_t number) {
    for(size_t i = 0; i < number; i++) {
        size_t width = (rand() * map::kMapWidth) / RAND_MAX;
        size_t height = (rand() * map::kMapHeight) / RAND_MAX;

        auto &elem = map_[width + height * map::kMapWidth];
        if (elem.top != nullptr || elem.bottom == nullptr || elem.bottom->GetType() != map::Type::kFree) {
            continue;
        }

        AddBox(new client::Box{{width, height}});
    }
}

void Game::GenerateClients() {
    AddClient(new client::Client({1, 1}));
    AddClient(new client::Client({map::kMapWidth - 2, 1}));
    AddClient(new client::Client({1, map::kMapHeight - 2}));
    AddClient(new client::Client({map::kMapWidth - 2, map::kMapHeight - 2}));
}

};
