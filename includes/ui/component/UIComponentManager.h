#ifndef NEWNEW_UICOMPONENTMANAGER_H
#define NEWNEW_UICOMPONENTMANAGER_H


#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "UIComponent.h"
#include "../../asset/AssetPath.h"
#include "../../events/EventBus.h"
#include "../../events/event/OpenMenuEvent.h"
#include "../../events/event/CloseMenuEvent.h"
#include "../../map/MenuMap.h"
#include "../../map/TileMap.h"
#include "MenuLayer.h"
#include "../../map/MapLoader.h"
#include "../../map/MenuMap.h"

class UIComponentManager {

public:
    void drawToRenderTexture(sf::RenderTexture* renderTexture);
    void release(TextureManager& textureManager);
    bool isMenuActive();
    void resetForNewScene();
    void onControllerMenuEvent();
    void onControllerCancelEvent();
    void onControllerActionEvent();
    void onControllerMenuMoveEvent(MoveDirection direction);

private:
    enum ComponentState {
        STATE_READY,
        STATE_INACTIVE,
        STATE_ACTIVE
    };

    static Logger logger;
    std::shared_ptr<EventBus> eventBus;
    ComponentState state = STATE_INACTIVE;
    MenuLayer playerMenuLayer;

    void updateComponentOriginPosition(sf::RenderTexture& renderTexture, sf::View& view);
    void closeMenu();
};


#endif //NEWNEW_UICOMPONENTMANAGER_H
