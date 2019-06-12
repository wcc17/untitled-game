#ifndef NEWNEW_LEVELMANAGER_H
#define NEWNEW_LEVELMANAGER_H

#include "ViewManager.h"
#include "entity/character/Player.h"
#include "level/Level.h"
#include "../includes/asset/AssetPath.h"

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
private:
    ViewManager viewManager;
    Level level;
    Player player;
    void handleCollisions();
    void handleNoTypeCollision();
    void handleDoorCollision();
    void handleSignCollision();
    void handlePlayerCollision();
};


#endif //NEWNEW_LEVELMANAGER_H
