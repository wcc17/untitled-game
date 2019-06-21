#include "../includes/Game.h"

Game::Game() {
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(960*2,540*2,32),"newnew", sf::Style::Titlebar | sf::Style::Close);
//     window->setFramerateLimit(60);
    window->setVerticalSyncEnabled(true);

    initialize();
}

void Game::initialize() {
    gameManager.initialize(window.get());
}

void Game::run() {
    while(!shouldExitGame && window->isOpen()) {
        std::vector<sf::Event> events = handleEvents();

        if(!shouldExitGame) {
            update(events);
            draw();
        }
    }

    exit();
}

void Game::update(std::vector<sf::Event> events) {
    gameManager.update(events);
}

std::vector<sf::Event> Game::handleEvents() {
    std::vector<sf::Event> events;
    sf::Event event;
    while (!shouldExitGame && window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            shouldExitGame = true;
        } else {
            events.push_back(event);
        }
    }

    return events;
}

void Game::draw() {
    window->clear(sf::Color::Black);
    gameManager.draw(window.get());
    window->display();
}

void Game::exit() {
    window->close();
    gameManager.release();
    window.reset();
}
