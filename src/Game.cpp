#include <tinyxml2.h>
#include "../includes/Game.h"

Logger Game::logger("Game");
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

Game::Game() {
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32),"newnew", sf::Style::Titlebar | sf::Style::Close);
     window->setFramerateLimit(60);
//    window->setVerticalSyncEnabled(true);

    initialize();

    if (!renderTexture.create(SCREEN_WIDTH, SCREEN_HEIGHT)) {
        logger.logError("Error creating renderTexture. Exiting Game");
    }
}

void Game::initialize() {
    eventBus = std::make_shared<EventBus>();
    fontManager.loadFont(AssetPath::MUNRO_REGULAR);
    framerateCounter.initialize(fontManager.getFont(AssetPath::MUNRO_REGULAR));
    keyboardController.initialize(eventBus);
    sceneManager.initialize(eventBus, fontManager.getFont(AssetPath::MUNRO_REGULAR));

    eventBus->subscribe(this, &Game::onExitGameEvent);
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
    sf::Time deltaTime = framerateCounter.update();
    keyboardController.handleInput(events);
    sceneManager.update(deltaTime, window.get());
}

void Game::draw() {
    window->clear(sf::Color::Black);

    //draw everything to renderTexture
    renderTexture.clear();
    sceneManager.drawToRenderTexture(&renderTexture);

    //draw to renderTexture with default view for text
    renderTexture.setView(renderTexture.getDefaultView());
    renderTexture.draw(framerateCounter.getFpsText());

    //prepare renderTexture for display
    renderTexture.display();
    renderSprite.setTexture(renderTexture.getTexture());
    renderSprite.setColor(sceneManager.getSceneTransparency(renderSprite.getColor()));

    //draw renderTexture to window and display
    window->draw(renderSprite);
    window->display();
}

void Game::exit() {
    window->close();
    fontManager.releaseFonts();
    sceneManager.release();
    eventBus.reset();
    window.reset();
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

void Game::onExitGameEvent(ExitGameEvent* event) {
    logger.logError("Exiting game. Reason given: %s", event->exitMessage.c_str());
    shouldExitGame = true;
}
