#ifndef NEWNEW_GAME_H
#define NEWNEW_GAME_H

#include <SFML/Graphics.hpp>
#include "asset/FontManager.h"
#include "asset/TextureManager.h"
#include "FramerateCounter.h"
#include "EventHandler.h"
#include "controller/KeyboardController.h"
#include "asset/AssetPath.h"
#include "LevelManager.h"

class Game {

public:
    Game();
    void run();
private:
    std::unique_ptr<sf::RenderWindow> window;

    //NOTE: there is the possibility that memory issues might happen with all of these allocated this way. Could switch to pointers for certain classes if memory becomes an issue
    FramerateCounter framerateCounter;
    FontManager fontManager;
    TextureManager textureManager;
    EventHandler eventHandler;
    KeyboardController keyboardController;
    LevelManager levelManager;

    void initialize();
    void update();
    void draw();
    void exit();
};


#endif //NEWNEW_GAME_H
