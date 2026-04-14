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

static void GenerateClients(server::Server &server);

void RunGame() {
    sf::RenderWindow window(sf::VideoMode (kWindowWidth, kWindowHeight), kWindowName);

    Game game;

    server::Server server;
    server.AddPlugin(&game);

    GenerateClients(server);
    game.GenerateBoxes(kBoxesNumber);

    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            }
        }

        game.Action();

        game.Animate(window);

        game.Draw(window);

        window.display();

        usleep(kTimePerFrameUSec);
    }

    window.close();
}

void Game::GenerateBoxes(size_t number) {
    for(size_t i = 0; i < number; i++) {
        size_t width = (rand() * map::kMapWidth) / RAND_MAX;
        size_t height = (rand() * map::kMapHeight) / RAND_MAX;

        auto &elem = map_[width + height * map::kMapWidth];
        if (elem.back() != nullptr && elem.back()->GetType() != map::Type::kFree) {
            continue;
        }

        AddBox(new client::Box{{width, height}});
    }
}

static void GenerateClients(server::Server &server) {
    server.AddClient(new client::ServerClient({1, 1}));
    server.AddClient(new client::ServerClient({map::kMapWidth - 2, 1}));
    server.AddClient(new client::ServerClient({1, map::kMapHeight - 2}));
    server.AddClient(new client::ServerClient({map::kMapWidth - 2, map::kMapHeight - 2}));
}

};
