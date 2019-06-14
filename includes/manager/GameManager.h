#ifndef NEWNEW_GAMEMANAGER_H
#define NEWNEW_GAMEMANAGER_H

#include "LevelManager.h"
#include "../controller/KeyboardController.h"
#include "../events/EventBus.h"

class GameManager {
public:
    void initialize();
    void update(sf::Time deltaTime, std::vector<sf::Event> sfEvents);
    void draw(sf::RenderWindow* window);
    void release();
private:
    LevelManager levelManager;
    KeyboardController keyboardController;
    std::shared_ptr<EventBus> eventBus;
};


#endif //NEWNEW_GAMEMANAGER_H
