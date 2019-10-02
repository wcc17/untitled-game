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
#include "../ui/dialogue/DialogueManager.h"
#include "ViewManager.h"
#include "../util/XmlManager.h"
#include "SceneState.h"
#include "../ui/UIManager.h"
#include "../events/event/OpenMenuEvent.h"
#include "../events/event/CloseMenuEvent.h"
#include "OverworldScene.h"

class SceneManager {
public:
    void initialize(std::shared_ptr<EventBus> eventBus, sf::Font* font, sf::Vector2u windowSize, sf::Vector2f defaultWindowSize);
    void update(sf::Time elapsedTime, sf::RenderTexture& renderTexture);
    void drawToRenderTexture(sf::RenderTexture* renderTexture);
    void release();
    sf::Color getSceneTransparency(sf::Color currentColor);
private:
    void loadScene(std::string previousSceneName, std::string sceneName);
    void setNextScene();
    void releaseScene();
    void updateSceneState(sf::Time elapsedTime, sf::RenderTexture& renderTexture);
    void updateSceneTransition(sf::Time elapsedTime);
    void updateChangeSceneState();
    void updatePauseState(sf::Time elapsedTime, sf::RenderTexture& renderTexture);
    void drawSceneStateToRenderTexture(sf::RenderTexture* renderTexture);
    void onChangeSceneEvent(ChangeSceneEvent* event);
    void onOpenMenuEvent(OpenMenuEvent* event);
    void onCloseMenuEvent(CloseMenuEvent* event);
    void onAggressiveNpcCollisionEvent(AggressiveNpcCollisionEvent* event);

    float sceneAlpha = 255.f;

    std::unique_ptr<OverworldScene> scene; //TODO: should just be a base Scene
//    std::unique_ptr<OverworldScene> currentOverworldScene;
//    std::unique_ptr<BattleScene> currentBattleScene;
    std::shared_ptr<EventBus> eventBus;

    SceneState state = SceneState::STATE_TRANSITION_SCENE_IN;
    std::string nextSceneName;

    TextureManager textureManager;
    XmlManager xmlManager;
    UIManager uiManager;
    ViewManager viewManager;
};


#endif //NEWNEW_SCENEMANAGER_H
