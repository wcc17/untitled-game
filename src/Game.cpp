#include "../includes/Game.h"

Game::Game() {
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(640*2,480*2,32),"newnew");
//    window->setFramerateLimit(60);
    window->setVerticalSyncEnabled(true);

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

    textureManager->loadTexture(TexturePath::TEST_LEVEL_TEXTURE);
    level = std::make_unique<Level>(textureManager->getTexture(TexturePath::TEST_LEVEL_TEXTURE),
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
    sf::Time elapsedTime = framerateCounter->update();

    keyboardController.handleInput(player.get(), level.get());
    player->update(elapsedTime);
    level->update(elapsedTime);
}

void Game::draw() {
    window->clear(sf::Color::Black);

    window->setView(level->getView());

    window->draw(*level);
    window->draw(framerateCounter->getFpsText());
    window->draw(*player);

    window->display();
}

void Game::exit() {
    window->close();
    fontManager->releaseFonts();
    textureManager->releaseTextures();

    player.reset();
    level.reset();
    framerateCounter.reset();
    textureManager.reset();
    fontManager.reset();
    window.reset();
}