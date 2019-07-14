#ifndef NEWNEW_GAME_H
#define NEWNEW_GAME_H

#include <SFML/Graphics.hpp>
#include "asset/FontManager.h"
#include "asset/AssetPath.h"
#include "util/FramerateCounter.h"
#include "events/EventBus.h"
#include "scene/SceneManager.h"
#include "controller/KeyboardController.h"
#include "events/event/ExitGameEvent.h"

class Game {

public:
    Game();
    void run();
private:
    std::unique_ptr<sf::RenderWindow> window;
    std::shared_ptr<EventBus> eventBus;
    SceneManager sceneManager;
    KeyboardController keyboardController;
    FramerateCounter framerateCounter;
    FontManager fontManager;
    bool shouldExitGame = false;
    static Logger logger;

    sf::RenderTexture renderTexture; //TODO: should be a unique_ptr that Game controls?
    sf::Sprite renderSprite;

    void initialize();
    void update(std::vector<sf::Event> events);
    void draw();
    void exit();
    std::vector<sf::Event> handleEvents();
    void onExitGameEvent(ExitGameEvent* event);
};


#endif //NEWNEW_GAME_H
