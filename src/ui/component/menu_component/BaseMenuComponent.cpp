#include "../../../../includes/ui/component/menu_component/BaseMenuComponent.h"

void BaseMenuComponent::initialize(
        sf::Font* font,
        float windowScale,
        sf::Texture* componentTexture,
        ScreenPosition screenPosition,
        UIComponentType componentType) {
    this->font = font;
    this->windowScale = windowScale;
    this->screenPosition = screenPosition;
    this->menuSprite.setTexture(*componentTexture);
    this->componentType = componentType;
}

void BaseMenuComponent::update(sf::RenderTexture &renderTexture, sf::View &view, sf::Time deltaTime) {
    updatePositionForView(renderTexture, view);
}

void BaseMenuComponent::drawToRenderTexture(sf::RenderTexture *renderTexture) {
    renderTexture->draw(menuSprite);

    sf::View originalView = renderTexture->getView();
    renderTexture->setView(renderTexture->getDefaultView());
    for(MenuOptionComponent menuOptionComponent : menuOptions) {
        renderTexture->draw(menuOptionComponent);
    }
    renderTexture->setView(originalView);
}

void BaseMenuComponent::addMenuOption(MenuOptionComponent menuOption) {
    menuOption.setFillColor(sf::Color::Black);
    menuOption.setLineSpacing(1.f);
    menuOption.setFont(*font);
    menuOption.setCharacterSize(72 * windowScale);

    menuOptions.push_back(menuOption);
    sortMenuOptions();
}

void BaseMenuComponent::sortMenuOptions() {
    std::sort(menuOptions.begin(), menuOptions.end());
}

void BaseMenuComponent::updatePositionForView(sf::RenderTexture& renderTexture, sf::View& view) {
    float menuComponentX = 0;
    float menuComponentY = 0;

    switch(screenPosition) {
        case TOP_LEFT:
            menuComponentX = view.getCenter().x - (view.getSize().x / 2);
            menuComponentY = view.getCenter().y - (view.getSize().y / 2);
            break;
        case TOP_SECOND_QUADRANT:
            //TODO: I'm not sure if this works yet
            menuComponentX = view.getCenter().x - (view.getSize().x / 4);
            menuComponentY = view.getCenter().y - (view.getSize().y / 2);
            break;
        case TOP_THIRD_QUADRANT:
            //TODO: I'm not sure if this works yet
            menuComponentX = view.getCenter().x + (view.getSize().x / 4);
            menuComponentY = view.getCenter().y - (view.getSize().y / 2);
            break;
        case TOP_RIGHT:
            menuComponentX = view.getCenter().x + (view.getSize().x / 2) - (menuSprite.getTextureRect().width);
            menuComponentY = view.getCenter().y - (view.getSize().y / 2);
            break;
        case BOTTOM_LEFT:
            menuComponentX = view.getCenter().x - (view.getSize().x / 2);
            menuComponentY = view.getCenter().y + (view.getSize().y / 2) - (menuSprite.getTextureRect().height);
            break;
        case BOTTOM_SECOND_QUADRANT:
            //TODO: I'm not sure if this works yet
            menuComponentX = view.getCenter().x - (view.getSize().x / 4);
            menuComponentY = view.getCenter().y + (view.getSize().y / 2) - (menuSprite.getTextureRect().height);
            break;
        case BOTTOM_THIRD_QUADRANT:
            //TODO: I'm not sure if this works yet
            menuComponentX = view.getCenter().x + (view.getSize().x / 4);
            menuComponentY = view.getCenter().y + (view.getSize().y / 2) - (menuSprite.getTextureRect().height);
            break;
        case BOTTOM_RIGHT:
            menuComponentX = view.getCenter().x + (view.getSize().x / 2) + (menuSprite.getTextureRect().width);
            menuComponentY = view.getCenter().y - (view.getSize().y / 2) - (menuSprite.getTextureRect().height);
            break;
        case CENTERED:
            //TODO: this doesn't work?
            break;
    }

    menuSprite.setPosition(menuComponentX, menuComponentY);

    for(MenuOptionComponent menuOptionComponent : menuOptions) {
        for (int i = 0; i < menuOptions.size(); i++) {
            updateMenuComponentTextPosition(renderTexture, view, menuOptions[i]);
        }
    }
}

void BaseMenuComponent::updateMenuComponentTextPosition(sf::RenderTexture& renderTexture, sf::View& view, MenuOptionComponent& menuOptionComponent) {
    float x = menuSprite.getPosition().x;
    float y = menuSprite.getPosition().y + (menuOptionComponent.getIndex() * (menuSprite.getGlobalBounds().height / (menuOptions.size())));

    x += (defaultTextOffset.x + textOffset.x);
    y += (defaultTextOffset.y + textOffset.y);

    sf::Vector2i coordsToPixel = renderTexture.mapCoordsToPixel(sf::Vector2f(x, y), view);
    menuOptionComponent.setPosition(sf::Vector2f(coordsToPixel.x, coordsToPixel.y));
}

bool BaseMenuComponent::componentActionIsFinished() {
    return true;
}

std::string BaseMenuComponent::getActiveMenuOptionName() {
    return "";
}

UIComponentType BaseMenuComponent::getUIComponentType() {
    return this->componentType;
}