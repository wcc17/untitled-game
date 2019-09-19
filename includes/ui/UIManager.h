#ifndef NEWNEW_UIMANAGER_H
#define NEWNEW_UIMANAGER_H


#include <SFML/Graphics/RenderTexture.hpp>
#include "../asset/TextureManager.h"
#include "../asset/AssetPath.h"
#include "../events/EventBus.h"
#include "../events/event/ControllerMenuEvent.h"
#include "dialogue/DialogueManager.h"
#include "../events/event/ControllerCancelEvent.h"
#include "../events/event/ControllerMoveEvent.h"
#include "../events/event/ControllerMenuMoveEvent.h"
#include "component/menu_component/MenuWithSelectorComponent.h"
#include "component/menu_component/DialogueMenuComponent.h"
#include "../../includes/events/event/OpenMenuEvent.h"
#include "../../includes/events/event/CloseMenuEvent.h"
#include "UIComponentInitializer.h"

class UIManager {

public:
    void initialize(std::shared_ptr<EventBus> eventBus, TextureManager& textureManager, sf::Font* font, sf::Vector2u windowSize, sf::Vector2f defaultWindowSize);
    void update(sf::RenderTexture& renderTexture, sf::View& view, sf::Time deltaTime);
    void drawToRenderTexture(sf::RenderTexture* renderTexture);
    void release(TextureManager& textureManager);
    void resetOnNewScene(std::vector<DialogueEvent> entityDialogueEvents);

private:
    std::shared_ptr<EventBus> eventBus;

    UIComponentInitializer uiComponentInitializer;
    BaseMenuComponent* activeMenuComponent = nullptr;

    //TODO: should be able to eventually combine startMenuComponent and partyMenuComponent and re-initialize it when one is ready to be used
    MenuWithSelectorComponent startMenuComponent;
    DialogueMenuComponent dialogueMenuComponent;
    MenuWithSelectorComponent partyMenuComponent;

    void initializeComponents(TextureManager& textureManager, float windowScale, sf::Font* font);
    void onControllerMenuEvent(ControllerMenuEvent* event);
    void onControllerActionEvent(ControllerActionEvent* event);
    void onControllerCancelEvent(ControllerCancelEvent* event);
    void onControllerMenuMoveEvent(ControllerMenuMoveEvent* event);
    void onOpenDialogueEvent(OpenDialogueEvent* event);
    void onCloseDialogueEvent(CloseDialogueEvent* event);
    void onOpenMenuEvent(OpenMenuEvent* event);
    void onCloseMenuEvent(CloseMenuEvent* event);
};


#endif //NEWNEW_UIMANAGER_H
