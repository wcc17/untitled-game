#ifndef NEWNEW_GAMEMANAGER_H
#define NEWNEW_GAMEMANAGER_H

#include "LevelManager.h"
#include "../controller/KeyboardController.h"

class GameManager {
public:
    void initialize();
    void update(sf::Time deltaTime);
    void draw(sf::RenderWindow* window);
    void release();
private:
    LevelManager levelManager;
    KeyboardController keyboardController;
};


#endif //NEWNEW_GAMEMANAGER_H
