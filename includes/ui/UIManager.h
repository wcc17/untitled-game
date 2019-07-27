#ifndef NEWNEW_UIMANAGER_H
#define NEWNEW_UIMANAGER_H


#include <SFML/Graphics/RenderTexture.hpp>
#include "../asset/TextureManager.h"
#include "../asset/AssetPath.h"
#include "../events/EventBus.h"
#include "component/UIComponent.h"
#include "../events/event/ControllerMenuEvent.h"
#include "dialogue/DialogueManager.h"
#include "component/UIComponentManager.h"
#include "../events/event/ControllerCancelEvent.h"

class UIManager {

public:
    void initialize(std::shared_ptr<EventBus> eventBus, TextureManager& textureManager, sf::Font* font, sf::Vector2u windowSize, sf::Vector2f defaultWindowSize);
    void update(sf::RenderWindow* window, sf::View& view, sf::Time deltaTime);
    void drawToRenderTexture(sf::RenderTexture* renderTexture);
    void release(TextureManager& textureManager);
    void resetMenu();
    void resetOnNewScene(std::vector<DialogueEvent> entityDialogueEvents);

private:
    std::shared_ptr<EventBus> eventBus;

    DialogueManager dialogueManager;
    UIComponentManager uiComponentManager;

    void onControllerMenuEvent(ControllerMenuEvent* event);
    void onControllerActionEvent(ControllerActionEvent* event);
    void onControllerCancelEvent(ControllerCancelEvent* event);
    void onOpenDialogueEvent(OpenDialogueEvent* event);
};


#endif //NEWNEW_UIMANAGER_H