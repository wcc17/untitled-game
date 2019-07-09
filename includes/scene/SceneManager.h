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
#include "../util/XmlManager.h"

class SceneManager {
public:
    void initialize(std::shared_ptr<EventBus> eventBus, sf::Font* font);
    void update(sf::Time elapsedTime, sf::RenderWindow* window);
    void draw(sf::RenderWindow* window);
    void drawForDefaultView(sf::RenderWindow* window);
    void release();
private:
    void loadScene(std::string sceneName);

    std::unique_ptr<Scene> scene;
    std::shared_ptr<EventBus> eventBus;

    TextureManager textureManager;
    CollisionManager collisionManager;
    NpcManager npcManager;
    TextManager textManager;
    ViewManager viewManager;
    XmlManager xmlManager;
    Player player;
};


#endif //NEWNEW_SCENEMANAGER_H
