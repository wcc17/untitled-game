#ifndef NEWNEW_LEVELMANAGER_H
#define NEWNEW_LEVELMANAGER_H

#include "ViewManager.h"
#include "entity/character/Player.h"
#include "level/Level.h"

class LevelManager {
public:
    void initialize(sf::Texture* playerTexture, sf::Vector2u windowSize);
    void update(sf::Time elapsedTime);
    void draw(sf::RenderWindow* window);

    void handleMoveUp();
    void handleMoveLeft();
    void handleMoveDown();
    void handleMoveRight();
    void handleMoveStop();

    sf::Vector2f getViewPosition();
private:
    ViewManager viewManager;
    Level level;
    Player player;
};


#endif //NEWNEW_LEVELMANAGER_H
