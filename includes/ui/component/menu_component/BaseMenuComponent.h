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
#include "../../../events/Event.h"
#include "../../../events/EventBus.h"
#include "../../../events/event/ControllerMenuEvent.h"
#include "../../../events/event/ControllerActionEvent.h"
#include "../../../events/event/ControllerCancelEvent.h"
#include "../../../events/event/ControllerMenuMoveEvent.h"
#include "../../../events/event/OpenDialogueEvent.h"

class BaseMenuComponent {

public:
    virtual void initialize(
            std::shared_ptr<EventBus> eventBus,
            sf::Font* font,
            float windowScale,
            sf::Texture* componentTexture,
            ScreenPosition screenPosition);
    virtual void update(sf::RenderTexture& renderTexture, sf::View& view, sf::Time deltaTime);
    virtual void drawToRenderTexture(sf::RenderTexture* renderTexture);

    void addMenuOption(MenuOptionComponent menuOption);

    virtual void onControllerMenuEvent(ControllerMenuEvent* event) {};
    virtual void onControllerActionEvent(ControllerActionEvent* event) {};
    virtual void onControllerCancelEvent(ControllerCancelEvent* event) {};
    virtual void onControllerMenuMoveEvent(ControllerMenuMoveEvent* event) {};
    virtual void onOpenDialogueEvent(OpenDialogueEvent* event) {};

protected:
    std::shared_ptr<EventBus> eventBus;
    sf::Font* font;
    std::vector<MenuOptionComponent> menuOptions;
    sf::Sprite menuSprite;
    sf::Vector2f defaultTextOffset = sf::Vector2f(10, 5);
    float windowScale;
    ScreenPosition screenPosition;
    sf::Vector2f textOffset;

    void updatePositionForView(sf::RenderTexture& renderTexture, sf::View& view);
    void sortMenuOptions();
    void updateMenuComponentTextPosition(sf::RenderTexture& renderTexture, sf::View& view, MenuOptionComponent& menuOptionComponent);

};


#endif //NEWNEW_BASEMENUCOMPONENT_H