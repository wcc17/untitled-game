#ifndef NEWNEW_SCENEMANAGER_H
#define NEWNEW_SCENEMANAGER_H

#include "Scene.h"
#include "../asset/AssetPath.h"
#include "../asset/TextureManager.h"
#include "../events/EventBus.h"
#include "../events/event/ControllerMoveEvent.h"
#include "../collisions/CollisionManager.h"
#include "../npc/NpcManager.h"
#include "../text/TextManager.h"
#include "ViewManager.h"

class SceneManager {
public:
    void initialize(std::shared_ptr<EventBus> eventBus, sf::Font* font);
    void update(sf::Time elapsedTime);
    void draw(sf::RenderWindow* window);
    void drawForDefaultView(sf::RenderWindow* window);
    void release();
private:
    TextureManager textureManager;
    CollisionManager collisionManager;
    NpcManager npcManager;
    TextManager textManager;
    ViewManager viewManager;

    Player player;
    Scene scene;
};


#endif //NEWNEW_SCENEMANAGER_H
