#include "../includes/Game.h"

Game::Game() {
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1920,1080,32),"newnew");
//    window->setFramerateLimit(60);
    window->setVerticalSyncEnabled(true);

    initializeManagers();
}

void Game::initializeManagers() {
    fontManager = std::make_unique<FontManager>();
    textureManager = std::make_unique<TextureManager>();

    fontManager->loadFont(AssetPath::OPENSANS_REGULAR);
    framerateCounter = std::make_unique<FramerateCounter>(fontManager->getFont(AssetPath::OPENSANS_REGULAR));

    textureManager->loadTexture(AssetPath::PLAYER_TEXTURE);
    levelManager.initialize(textureManager->getTexture(AssetPath::PLAYER_TEXTURE), window->getSize());
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
    sf::Time elapsedTime = framerateCounter->update(levelManager.getViewPosition());
    keyboardController.handleInput(&levelManager);
    levelManager.update(elapsedTime);
}

void Game::draw() {
    window->clear(sf::Color::Black);
//    window->draw(framerateCounter->getFpsText());
    levelManager.draw(window.get());
    window->display();
}

void Game::exit() {
    window->close();
    fontManager->releaseFonts();
    textureManager->releaseTextures();

    framerateCounter.reset();
    textureManager.reset();
    fontManager.reset();
    window.reset();
}
