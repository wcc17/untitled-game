#ifndef NEWNEW_LEVELMANAGER_H
#define NEWNEW_LEVELMANAGER_H

#include "ViewManager.h"
#include "../entity/character/Player.h"
#include "../level/Level.h"
#include "../../includes/asset/AssetPath.h"
#include "../../includes/asset/TextureManager.h"
#include "../../includes/events/EventBus.h"
#include "../controller/MoveEvent.h"

class LevelManager {
public:
    void initialize(std::shared_ptr<EventBus> eventBus);
    void update(sf::Time elapsedTime);
    void draw(sf::RenderWindow* window);
    void release();
private:
    TextureManager textureManager;
    ViewManager viewManager;
    Level level;
    Player player;
    void handleCollisions();
    void handleWallCollision();
    void handleDoorCollision();
    void handleSignCollision();
    void handlePlayerCollision();
};


#endif //NEWNEW_LEVELMANAGER_H
