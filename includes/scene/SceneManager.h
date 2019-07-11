#ifndef NEWNEW_SCENEMANAGER_H
#define NEWNEW_SCENEMANAGER_H

#include "Scene.h"
#include "../asset/AssetPath.h"
#include "../asset/TextureManager.h"
#include "../events/EventBus.h"
#include "../events/event/ControllerMoveEvent.h"
#include "../collisions/CollisionManager.h"
#include "SFML/Graphics/RenderTexture.hpp"
#include "../npc/NpcManager.h"
#include "../text/TextManager.h"
#include "ViewManager.h"
#include "../util/XmlManager.h"
#include "SceneState.h"

class SceneManager {
public:
    void initialize(std::shared_ptr<EventBus> eventBus, sf::Font* font);
    void update(sf::Time elapsedTime, sf::RenderWindow* window);
    void drawToRenderTexture(sf::RenderTexture* renderTexture);
    void drawToRenderTextureWithDefaultView(sf::RenderTexture* renderTexture);
    void release();
private:
    void loadScene(std::string sceneName);
    void releaseScene();
    void onChangeSceneEvent(ChangeSceneEvent* event);
    void updateSceneState(sf::Time elapsedTime, sf::RenderWindow* window);
    void updateChangeSceneState();
    void drawSceneStateToRenderTexture(sf::RenderTexture* renderTexture);
    void drawChangeSceneStateToRenderTexture(sf::RenderTexture* renderTexture);

    std::unique_ptr<Scene> scene;
    std::shared_ptr<EventBus> eventBus;

    SceneState state = SceneState::STATE_SCENE;
    std::string nextSceneName;

    TextureManager textureManager;
    CollisionManager collisionManager;
    NpcManager npcManager;
    TextManager textManager;
    ViewManager viewManager;
    XmlManager xmlManager;
    Player player;
};


#endif //NEWNEW_SCENEMANAGER_H
