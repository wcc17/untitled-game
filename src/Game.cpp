#include "../includes/Game.h"

Logger Game::logger("Game");
const int DEFAULT_SCREEN_WIDTH = 1920;
const int DEFAULT_SCREEN_HEIGHT = 1080;
const int SCREEN_WIDTH = DEFAULT_SCREEN_WIDTH;
const int SCREEN_HEIGHT = DEFAULT_SCREEN_HEIGHT;

Game::Game() {
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32),"newnew", sf::Style::Titlebar | sf::Style::Close);
//     window->setFramerateLimit(60);
    window->setVerticalSyncEnabled(true);
    window->setKeyRepeatEnabled(false);

    initialize();

    if (!renderTexture.create(SCREEN_WIDTH, SCREEN_HEIGHT)) {
        logger.logError("Error creating renderTexture. Exiting Game");
    }
}

void Game::initialize() {
    eventBus = std::make_shared<EventBus>();
    fontManager.loadFont(AssetPath::MUNRO_REGULAR);
    framerateCounter.initialize(fontManager.getFont(AssetPath::MUNRO_REGULAR), window->getSize(), sf::Vector2f(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT));
    keyboardController.initialize(eventBus);
    sceneManager.initialize(eventBus, fontManager.getFont(AssetPath::MUNRO_REGULAR), window->getSize(), sf::Vector2f(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT));

    eventBus->subscribe(this, &Game::onExitGameEvent, "Game");
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
    sceneManager.update(deltaTime, renderTexture);
}

void Game::draw() {
    window->clear(sf::Color::Black);

    //draw everything to renderTexture
    renderTexture.clear();
    sceneManager.drawToRenderTexture(&renderTexture);

    //draw to renderTexture with default view for text
    sf::View view = renderTexture.getView();
    renderTexture.setView(renderTexture.getDefaultView());
    renderTexture.draw(framerateCounter.getFpsText());

    //prepare renderTexture for display
    renderTexture.display();
    renderSprite.setTexture(renderTexture.getTexture());
    renderSprite.setColor(sceneManager.getSceneTransparency(renderSprite.getColor()));

    //draw renderTexture to window and display
    window->draw(renderSprite);
    window->display();

    renderTexture.setView(view);
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
