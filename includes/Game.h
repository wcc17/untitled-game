#ifndef NEWNEW_GAME_H
#define NEWNEW_GAME_H

#include <SFML/Graphics.hpp>
#include "asset/FontManager.h"
#include "asset/TextureManager.h"
#include "FramerateCounter.h"
#include "EventHandler.h"
#include "controller/KeyboardController.h"
#include "entity/character/Player.h"
#include "asset/AssetPath.h"
#include "entity/level/Level.h"

class Game {

public:
    Game();
    void run();
private:
    std::unique_ptr<sf::RenderWindow> window;
    std::unique_ptr<FramerateCounter> framerateCounter;
    std::unique_ptr<FontManager> fontManager;
    std::unique_ptr<TextureManager> textureManager;
    EventHandler eventHandler;
    KeyboardController keyboardController;

    std::unique_ptr<Player> player;
    std::unique_ptr<Level> level;

    void update();
    void draw();
    void initializeManagers();
    void exit();
};


#endif //NEWNEW_GAME_H
