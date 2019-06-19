#ifndef NEWNEW_SCENEMANAGER_H
#define NEWNEW_SCENEMANAGER_H

#include "../entity/player/PlayerManager.h"
#include "Scene.h"
#include "../asset/AssetPath.h"
#include "../asset/TextureManager.h"
#include "../events/EventBus.h"
#include "../controller/ControllerMoveEvent.h"
#include "../collisions/CollisionManager.h"
#include "../npc/NpcManager.h"

class SceneManager {
public:
    void initialize(std::shared_ptr<EventBus> eventBus);
    void update(sf::Time elapsedTime);
    void draw(sf::RenderWindow* window);
    void release();
private:
    TextureManager textureManager;
    PlayerManager playerManager;
    CollisionManager collisionManager;
    NpcManager npcManager;
    Scene scene;
};


#endif //NEWNEW_SCENEMANAGER_H
