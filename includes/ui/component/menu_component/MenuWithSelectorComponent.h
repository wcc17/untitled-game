#ifndef NEWNEW_MENUWITHSELECTORCOMPONENT_H
#define NEWNEW_MENUWITHSELECTORCOMPONENT_H


#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "../MenuOptionComponent.h"
#include "../../../controller/MoveDirection.h"
#include "../../../util/Logger.h"
#include "../MenuScreenPosition.h"
#include "BaseMenuComponent.h"
#include "../../../events/event/OpenMenuEvent.h"
#include "../../../events/event/CloseMenuEvent.h"

class MenuWithSelectorComponent : public BaseMenuComponent {

public:
    void initialize(
            std::shared_ptr<EventBus> eventBus,
            sf::Font* font,
            float windowScale,
            sf::Texture* componentTexture,
            sf::Texture* selectorTexture,
            ScreenPosition screenPosition);
    void update(sf::RenderTexture& renderTexture, sf::View& view, sf::Time deltaTime) override;
    void drawToRenderTexture(sf::RenderTexture* renderTexture) override;

    void changeActiveMenuOption(MoveDirection direction);
    UIComponentType getActiveMenuOptionNextMenu();

    void onControllerMenuEvent(ControllerMenuEvent* event) override;
    void onControllerActionEvent(ControllerActionEvent* event) override;
    void onControllerCancelEvent(ControllerCancelEvent* event) override;
    void onControllerMenuMoveEvent(ControllerMenuMoveEvent* event) override;

private:
    sf::Sprite menuSelectorSprite;
    int selectedMenuOptionIndex = 0;

    void updateSelectorPositionBasedOnMenuComponent();
    sf::Vector2f getSelectorPositionBasedOnSelectedMenuOption(sf::Vector2f selectorDimensions);
};


#endif //NEWNEW_MENUWITHSELECTORCOMPONENT_H
