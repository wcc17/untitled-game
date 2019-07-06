#include "../includes/Game.h"

Logger Game::logger("Game");

Game::Game() {
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1920,1080,32),"newnew", sf::Style::Titlebar | sf::Style::Close);
     window->setFramerateLimit(60);
//    window->setVerticalSyncEnabled(true);

    initialize();
}

void Game::initialize() {
    eventBus = std::make_shared<EventBus>();
    fontManager.loadFont(AssetPath::OPENSANS_REGULAR);
    framerateCounter.initialize(fontManager.getFont(AssetPath::OPENSANS_REGULAR));
    keyboardController.initialize(eventBus);
    sceneManager.initialize(eventBus, fontManager.getFont(AssetPath::OPENSANS_REGULAR));

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

    //draw to player view
    sceneManager.draw(window.get());

    //draw to default view
    window->setView(window->getDefaultView());
    sceneManager.drawForDefaultView(window.get());
    window->draw(framerateCounter.getFpsText());

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
