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

#include "game/food.hpp"

namespace game {

static const std::string kWindowName = "agar.io";

static const size_t kFoodNumber = 1000;
static const size_t kClientsNumber = 10;

static const size_t kClientMaxRadius = 30;
static const size_t kClientMinRadius = 10;

void RunGame() {
    sf::RenderWindow window(sf::VideoMode (kWindowWidth, kWindowHeight), kWindowName);

    Game game;
    // game.AddClient({{100, 100}, 50});
    // game.AddClient({{300, 300}, 25});

    game.GenerateFood(kFoodNumber);
    game.GenerateClients(kClientsNumber);

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

void Game::GenerateFood(size_t number) {
    for(size_t i = 0; i < number; i++) {
        AddFood({{((double)rand() * kWindowWidth) / RAND_MAX, ((double)rand() * kWindowHeight) / RAND_MAX},
                        (rand() * kFoodMaxWeight) / RAND_MAX + kFoodMinWeight});
    }
}

void Game::GenerateClients(size_t number) {
    for(size_t i = 0; i < number; i++) {
        AddClient({{((double)rand() * kWindowWidth) / RAND_MAX, ((double)rand() * kWindowHeight) / RAND_MAX},
                        ((double)rand() * kClientMaxRadius) / RAND_MAX + kClientMinRadius});
    }
}

};
