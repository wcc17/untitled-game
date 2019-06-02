#include "../includes/Game.h"

Game::Game() {
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(640,480,32),"newnew");
    window->setFramerateLimit(60);

    initializeManagers();
}

void Game::initializeManagers() {
    fontManager = std::make_unique<FontManager>();
    fontManager->loadFont(FontPath::OPENSANS_REGULAR);

    framerateCounter = std::make_unique<FramerateCounter>(fontManager->getFont(FontPath::OPENSANS_REGULAR));
}

void Game::run() {
    while (!eventHandler.getShouldExitGame() && window->isOpen()){
        eventHandler.handleEvents(window.get(), &keyboardController);

        if (!eventHandler.getShouldExitGame()) {
            update();
            draw();
        }
    }

    exit();
}

void Game::update() {
    keyboardController.handleInput();
    framerateCounter->update();
}

void Game::draw() {
    window->clear(sf::Color::Black);
    window->draw(framerateCounter->getFpsText());
    window->display();
}

void Game::exit() {
    window->close();
    fontManager->releaseFonts();

    framerateCounter.reset();
    fontManager.reset();
    window.reset();
}