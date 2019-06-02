#include "../includes/Game.h"
#include "../includes/asset/TexturePath.h"

Game::Game() {
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(640*2,480*2,32),"newnew");
    window->setFramerateLimit(60);

    initializeManagers();
}

void Game::initializeManagers() {
    fontManager = std::make_unique<FontManager>();
    textureManager = std::make_unique<TextureManager>();

    fontManager->loadFont(FontPath::OPENSANS_REGULAR);
    framerateCounter = std::make_unique<FramerateCounter>(fontManager->getFont(FontPath::OPENSANS_REGULAR));

    textureManager->loadTexture(TexturePath::PLAYER_TEXTURE);
    player = std::make_unique<Player>(textureManager->getTexture(TexturePath::PLAYER_TEXTURE),
            window->getSize().x, window->getSize().y);
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
    window->draw(*player);
    window->display();
}

void Game::exit() {
    window->close();
    fontManager->releaseFonts();
    textureManager->releaseTextures();

    framerateCounter.reset();
    fontManager.reset();
    window.reset();
}