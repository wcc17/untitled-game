#ifndef NEWNEW_UICOMPONENTINITIALIZER_H
#define NEWNEW_UICOMPONENTINITIALIZER_H


#include "../asset/TextureManager.h"
#include "../../includes/asset/AssetPath.h"
#include "../../includes/ui/UIComponentType.h"
#include "component/MenuComponent.h"
#include "component/menu_component/DialogueMenuComponent.h"
#include <SFML/Graphics/Font.hpp>

class UIComponentInitializer {

public:
    DialogueMenuComponent initializeDialogueMenuComponent(TextureManager& textureManager, float windowScale, sf::Font* font);
    MenuComponent initializeStartMenuComponent(TextureManager& textureManager, float windowScale, sf::Font* font, sf::FloatRect selectorBounds);
    MenuComponent initializePartyMenuComponent(TextureManager& textureManager, float windowScale, sf::Font* font, sf::FloatRect selectorBounds);
    void release(TextureManager& textureManager);

private:
    void initializeMenuOptionComponent(int index, std::string displayText, std::string opensToMenu, MenuComponent& startMenuComponent);
};


#endif //NEWNEW_UICOMPONENTINITIALIZER_H
