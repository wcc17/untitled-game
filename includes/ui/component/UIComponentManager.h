#ifndef NEWNEW_UICOMPONENTMANAGER_H
#define NEWNEW_UICOMPONENTMANAGER_H


#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "UIComponent.h"
#include "../../asset/AssetPath.h"

class UIComponentManager {

public:
    void initialize(TextureManager& textureManager);
    void update(sf::RenderWindow* window, sf::View& view, sf::Time deltaTime);
    void drawToRenderTexture(sf::RenderTexture* renderTexture);
    void release(TextureManager& textureManager);
    bool isMenuActive();
    void onControllerMenuEvent();
    void onControllerEscapeEvent();
    void onControllerActionEvent();

private:
    UIComponent playerMenuComponent;
    bool menuIsActive = false;
    bool positionsSet = false;

    void updateComponentPositions(sf::RenderWindow* window, sf::View& view);
};


#endif //NEWNEW_UICOMPONENTMANAGER_H
