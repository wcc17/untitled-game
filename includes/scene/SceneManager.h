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
#include "../events/event/OpenMenuEvent.h"
#include "../events/event/CloseMenuEvent.h"
#include "../events/event/ChangeSceneToNewMapEvent.h"
#include "../events/event/ChangeSceneToBattleEvent.h"
#include "OverworldScene.h"
#include "BattleScene.h"
#include "SceneStateHandler.h"

class SceneManager {
public:
    void initialize(std::shared_ptr<EventBus> eventBus, sf::Font* font, sf::Vector2u windowSize, sf::Vector2f defaultWindowSize);
    void update(sf::Time elapsedTime, sf::RenderTexture& renderTexture);
    void drawToRenderTexture(sf::RenderTexture* renderTexture);
    void release();
    sf::Color getSceneTransparency(sf::Color currentColor);
private:
    void loadScene(std::string previousSceneName, std::string sceneName);
    void releaseScene();
    void updateSceneState(sf::Time elapsedTime, sf::RenderTexture& renderTexture);
    void updateSceneTransition(sf::Time elapsedTime);
    void updateChangeSceneState();
    void updatePauseState(sf::Time elapsedTime, sf::RenderTexture& renderTexture);
    void drawSceneStateToRenderTexture(sf::RenderTexture* renderTexture);
    void onChangeSceneToNewMapEvent(ChangeSceneToNewMapEvent* event);
    void onChangeSceneToBattleEvent(ChangeSceneToBattleEvent* event);
    void onOpenMenuEvent(OpenMenuEvent* event);
    void onCloseMenuEvent(CloseMenuEvent* event);
    void onControllerMenuEvent(ControllerMenuEvent* event);
    void onControllerActionEvent(ControllerActionEvent* event);
    void onControllerCancelEvent(ControllerCancelEvent* event);
    void onControllerMenuMoveEvent(ControllerMenuMoveEvent* event);
    void onOpenDialogueEvent(OpenDialogueEvent* event);
    void onCloseDialogueEvent(CloseDialogueEvent* event);

    float sceneAlpha = 255.f;

    std::unique_ptr<Scene> scene;
    std::shared_ptr<EventBus> eventBus;
    sf::Font* font;
    sf::Vector2u windowSize;
    sf::Vector2f defaultWindowSize;

    SceneState state = SceneState::STATE_TRANSITION_SCENE_IN;
    std::string nextSceneName;

    TextureManager textureManager;
    ViewManager viewManager;
    SceneStateHandler sceneStateHandler;
};


#endif //NEWNEW_SCENEMANAGER_H
