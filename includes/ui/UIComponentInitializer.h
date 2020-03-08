#ifndef NEWNEW_UICOMPONENTINITIALIZER_H
#define NEWNEW_UICOMPONENTINITIALIZER_H


#include "../asset/TextureManager.h"
#include "../../includes/asset/AssetPath.h"
#include "../../includes/ui/UIComponentType.h"
#include "component/menu_component/MenuWithSelectorComponent.h"
#include "component/menu_component/DialogueMenuComponent.h"
#include <SFML/Graphics/Font.hpp>

class UIComponentInitializer {

public:
    DialogueMenuComponent initializeDialogueMenuComponent(TextureManager& textureManager, std::shared_ptr<EventBus> eventBus, float windowScale, sf::Font* font);
    MenuWithSelectorComponent initializeStartMenuComponent(TextureManager& textureManager, std::shared_ptr<EventBus> eventBus, float windowScale, sf::Font* font);
    MenuWithSelectorComponent initializePartyMenuComponent(TextureManager& textureManager, std::shared_ptr<EventBus> eventBus, float windowScale, sf::Font* font);
    MenuWithSelectorComponent initializeBattleMenuComponent(TextureManager& textureManager, std::shared_ptr<EventBus> eventBus, float windowScale, sf::Font* font);
    void release(TextureManager& textureManager);

private:
    void initializeMenuOptionComponent(int index, std::string displayText, UIComponentType opensToMenu, MenuWithSelectorComponent& menuComponent);
};


#endif //NEWNEW_UICOMPONENTINITIALIZER_H
