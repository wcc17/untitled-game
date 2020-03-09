#ifndef NEWNEW_MENUWITHSELECTORCOMPONENT_H
#define NEWNEW_MENUWITHSELECTORCOMPONENT_H


#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "../MenuOptionComponent.h"
#include "../../../controller/MoveDirection.h"
#include "../../../util/Logger.h"
#include "../MenuScreenPosition.h"
#include "BaseMenuComponent.h"
#include "../../../events/event/PauseGameEvent.h"
#include "../../../events/event/UnPauseGameEvent.h"

class MenuWithSelectorComponent : public BaseMenuComponent {

public:
    void initialize(
            sf::Font* font,
            float windowScale,
            sf::Texture* componentTexture,
            sf::Texture* selectorTexture,
            ScreenPosition screenPosition);
    void update(sf::RenderTexture& renderTexture, sf::View& view, sf::Time deltaTime) override;
    void drawToRenderTexture(sf::RenderTexture* renderTexture) override;
    void handleControllerMenuMoveButtonPressed(MoveDirection direction) override;

    void changeActiveMenuOption(MoveDirection direction);
    std::string getActiveMenuOptionName();
    UIComponentType getNextMenuType();


private:
    sf::Sprite menuSelectorSprite;
    int selectedMenuOptionIndex = 0;

    void updateSelectorPositionBasedOnMenuComponent();
    sf::Vector2f getSelectorPositionBasedOnSelectedMenuOption();
};


#endif //NEWNEW_MENUWITHSELECTORCOMPONENT_H
