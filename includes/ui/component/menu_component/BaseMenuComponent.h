#ifndef NEWNEW_BASEMENUCOMPONENT_H
#define NEWNEW_BASEMENUCOMPONENT_H

#include <memory>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/View.hpp>
#include "../MenuOptionComponent.h"
#include "../../../controller/MoveDirection.h"
#include "../../../util/Logger.h"
#include "../MenuScreenPosition.h"

class BaseMenuComponent {

public:
    virtual void initialize(
            sf::Font* font,
            float windowScale,
            sf::Texture* componentTexture,
            ScreenPosition screenPosition,
            UIComponentType componentType);
    virtual void update(sf::RenderTexture& renderTexture, sf::View& view, sf::Time deltaTime);
    virtual void drawToRenderTexture(sf::RenderTexture* renderTexture);
    virtual bool componentActionIsFinished();

    virtual void handleControllerMenuButtonPressed() {};
    virtual void handleControllerActionButtonPressed() {};
    virtual void handleControllerCancelButtonPressed() {};
    virtual void handleControllerMenuMoveButtonPressed(MoveDirection direction) {};
    virtual void openDialogueWithSubstitutions(
            std::string nameOfDialogueTextAsset,
            std::vector<std::string> textSubstitutions) {};
    virtual void openDialogue(std::string nameOfDialogueTextAsset) {};
    virtual std::string getActiveMenuOptionName();

    void addMenuOption(MenuOptionComponent menuOption);
    UIComponentType getUIComponentType();

protected:
    sf::Font* font;
    std::vector<MenuOptionComponent> menuOptions;
    sf::Sprite menuSprite;
    sf::Vector2f defaultTextOffset = sf::Vector2f(10, 5);
    float windowScale;
    ScreenPosition screenPosition;
    sf::Vector2f textOffset;
    UIComponentType componentType = UIComponentType::NO_COMPONENT_TYPE;

    void updatePositionForView(sf::RenderTexture& renderTexture, sf::View& view);
    void sortMenuOptions();
    void updateMenuComponentTextPosition(sf::RenderTexture& renderTexture, sf::View& view, MenuOptionComponent& menuOptionComponent);
};


#endif //NEWNEW_BASEMENUCOMPONENT_H
