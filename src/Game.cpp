#include "../includes/Game.h"

Game::Game() {
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(960*2,540*2,32),"newnew", sf::Style::Titlebar | sf::Style::Close);
    window->setFramerateLimit(60);
//    window->setVerticalSyncEnabled(true);

    initialize();
}

void Game::initialize() {
    fontManager.loadFont(AssetPath::OPENSANS_REGULAR);
    framerateCounter.initialize(fontManager.getFont(AssetPath::OPENSANS_REGULAR));

    textureManager.loadTexture(AssetPath::PLAYER_TEXTURE); //TODO: should textureManager just be passed to LevelManager? LevelManager will eventually need to load textures based on something happening in the game. should game ever be loading textures?
    levelManager.initialize(textureManager.getTexture(AssetPath::PLAYER_TEXTURE), window->getSize());
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
    sf::Time elapsedTime = framerateCounter.update();
    keyboardController.handleInput(&levelManager);
    levelManager.update(elapsedTime);
}

void Game::draw() {
    //TODO: should I draw everything to a texture first? would that help with the cracks in the tiles when resizing the window?
    window->clear(sf::Color::Black);
    levelManager.draw(window.get());
    window->setView(window->getDefaultView());
    window->draw(framerateCounter.getFpsText());
    window->display();
}

void Game::exit() {
    window->close();
    fontManager.releaseFonts();
    textureManager.releaseTextures();
    window.reset();
}
