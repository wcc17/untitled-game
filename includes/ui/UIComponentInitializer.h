#ifndef NEWNEW_UICOMPONENTINITIALIZER_H
#define NEWNEW_UICOMPONENTINITIALIZER_H


#include "../asset/TextureManager.h"
#include "../../includes/asset/AssetPath.h"
#include "../../includes/ui/UIComponentType.h"
#include "component/menu_component/MenuWithSelectorComponent.h"
#include "component/menu_component/DialogueMenuComponent.h"
#include "../scene/battle/BattleSceneMenuChoice.h"
#include "../scene/overworld/OverworldStartMenuChoice.h"
#include <SFML/Graphics/Font.hpp>

class UIComponentInitializer {

public:
    DialogueMenuComponent initializeDialogueMenuComponent(
            TextureManager& textureManager,
            float windowScale,
            sf::Font* font);
    MenuWithSelectorComponent initializeStartMenuComponent(
            TextureManager& textureManager,
            float windowScale,
            sf::Font* font);
    MenuWithSelectorComponent initializePartyMenuComponent(
            TextureManager& textureManager,
            float windowScale,
            sf::Font* font);
    MenuWithSelectorComponent initializeBattleMenuComponent(
            TextureManager& textureManager,
            float windowScale,
            sf::Font* font,
            bool isPartyLeader,
            int indexOfCharacterInParty);
    void release(TextureManager& textureManager);

private:
    void initializeMenuOptionComponent(
            int index,
            std::string displayText,
            MenuWithSelectorComponent& menuComponent);
};


#endif //NEWNEW_UICOMPONENTINITIALIZER_H
