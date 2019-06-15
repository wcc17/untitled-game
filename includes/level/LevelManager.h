#ifndef NEWNEW_LEVELMANAGER_H
#define NEWNEW_LEVELMANAGER_H

#include "../view/ViewManager.h"
#include "../entity/character/Player.h"
#include "Scene.h"
#include "../asset/AssetPath.h"
#include "../asset/TextureManager.h"
#include "../events/EventBus.h"
#include "../controller/ControllerMoveEvent.h"
#include "../collisions/CollisionManager.h"
#include "../npc/NpcManager.h"

class LevelManager {
public:
    void initialize(std::shared_ptr<EventBus> eventBus);
    void update(sf::Time elapsedTime);
    void draw(sf::RenderWindow* window);
    void release();
private:
    TextureManager textureManager;
    ViewManager viewManager;
    CollisionManager collisionManager;
    NpcManager npcManager;
    Scene scene;
    Player player;
};


#endif //NEWNEW_LEVELMANAGER_H
