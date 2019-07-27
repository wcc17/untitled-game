#ifndef NEWNEW_UICOMPONENTMANAGER_H
#define NEWNEW_UICOMPONENTMANAGER_H


#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "UIComponent.h"
#include "../../asset/AssetPath.h"
#include "../../events/EventBus.h"
#include "../../events/event/OpenMenuEvent.h"
#include "../../events/event/CloseMenuEvent.h"
#include "../../scene/MenuObjectMap.h"
#include "../../scene/TileMap.h"

class UIComponentManager {

public:
    void initialize(std::shared_ptr<EventBus> eventBus, TextureManager& textureManager);
    void update(sf::RenderWindow* window, sf::View& view, sf::Time deltaTime);
    void drawToRenderTexture(sf::RenderTexture* renderTexture);
    void release(TextureManager& textureManager);
    bool isMenuActive();
    void resetForNewScene();
    void onControllerMenuEvent();
    void onControllerCancelEvent();
    void onControllerActionEvent();

private:
    enum ComponentState {
        STATE_READY,
        STATE_INACTIVE,
        STATE_ACTIVE
    };

    static Logger logger;
    std::shared_ptr<EventBus> eventBus;
    sf::Texture* tileMapTexture;
    ComponentState state = STATE_INACTIVE;
    MenuComponent playerMenuComponent;
    MenuObjectMap menuObjectMap;
    TileMap tileMap;
    std::string tilesetImagePath;

    void loadMenuMap(TextureManager& textureManager);
    void updateComponentPositions(sf::RenderWindow* window, sf::View& view);
    void closeMenu();
};


#endif //NEWNEW_UICOMPONENTMANAGER_H
