#ifndef NEWNEW_GAMEMANAGER_H
#define NEWNEW_GAMEMANAGER_H

#include "../scene/SceneManager.h"
#include "../controller/KeyboardController.h"
#include "../events/EventBus.h"
#include "../asset/FontManager.h"
#include "../FramerateCounter.h"

class GameManager {
public:
    void initialize(sf::RenderWindow* window);
    void update(std::vector<sf::Event> sfEvents);
    void draw(sf::RenderWindow* window);
    void release();
private:
    SceneManager sceneManager;
    KeyboardController keyboardController;
    FramerateCounter framerateCounter;
    FontManager fontManager;

    std::shared_ptr<EventBus> eventBus;
};


#endif //NEWNEW_GAMEMANAGER_H
