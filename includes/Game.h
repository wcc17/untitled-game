#ifndef NEWNEW_GAME_H
#define NEWNEW_GAME_H

#include <SFML/Graphics.hpp>
#include "asset/FontManager.h"
#include "asset/AssetPath.h"
#include "FramerateCounter.h"
#include "events/EventBus.h"
#include "scene/SceneManager.h"
#include "controller/KeyboardController.h"

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

    void initialize();
    std::vector<sf::Event> handleEvents();
    void update(std::vector<sf::Event> events);
    void draw();
    void exit();
};


#endif //NEWNEW_GAME_H
