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
    void release();
    sf::Color getSceneTransparency(sf::Color currentColor);
private:
    void loadScene(std::string sceneName);
    void setNextScene();
    void releaseScene();
    void onChangeSceneEvent(ChangeSceneEvent* event);
    void updateSceneState(sf::Time elapsedTime, sf::RenderWindow* window);
    void updateSceneTransition(sf::Time elapsedTime);
    void updateChangeSceneState();
    void drawSceneStateToRenderTexture(sf::RenderTexture* renderTexture);
    void drawChangeSceneStateToRenderTexture(sf::RenderTexture* renderTexture);
    float sceneAlpha = 255.f;

    std::unique_ptr<Scene> scene;
    std::shared_ptr<EventBus> eventBus;

    SceneState state = SceneState::STATE_TRANSITION_SCENE_IN;
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
