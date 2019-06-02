//
// Created by William Curry on 2019-05-31.
//

#ifndef NEWNEW_GAME_H
#define NEWNEW_GAME_H

#include <SFML/Graphics.hpp>
#include "asset/FontManager.h"
#include "FramerateCounter.h"
#include "EventHandler.h"
#include "controller/KeyboardController.h"

class Game {

public:
    Game();
    void run();

private:
    std::unique_ptr<sf::RenderWindow> window;
    std::unique_ptr<FontManager> fontManager;
    std::unique_ptr<FramerateCounter> framerateCounter;
    EventHandler eventHandler;
    KeyboardController keyboardController;
    void update();
    void draw();
    void initializeManagers();
    void exit();
};


#endif //NEWNEW_GAME_H
