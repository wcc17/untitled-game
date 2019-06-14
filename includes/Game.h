#ifndef NEWNEW_GAME_H
#define NEWNEW_GAME_H

#include <SFML/Graphics.hpp>
#include "asset/FontManager.h"
#include "asset/AssetPath.h"
#include "manager/GameManager.h"
#include "FramerateCounter.h"

class Game {

public:
    Game();
    void run();
private:
    std::unique_ptr<sf::RenderWindow> window;
    bool shouldExitGame = false;

    //NOTE: there is the possibility that memory issues might happen with all of these allocated this way. Could switch to pointers for certain classes if memory becomes an issue
    FramerateCounter framerateCounter;
    FontManager fontManager;
    GameManager gameManager;

    void initialize();
    std::vector<sf::Event> handleEvents();
    void update(std::vector<sf::Event> events);
    void draw();
    void exit();
};


#endif //NEWNEW_GAME_H
