#include "../../../includes/ui/component/MenuOptionComponent.h"

void MenuOptionComponent::initialize(std::string name, ObjectType type, sf::FloatRect boundingBox, int index, std::string displayText) {
    UIComponent::initialize(name, type, boundingBox);
    this->index = index;
    setString(displayText);
}

void MenuOptionComponent::setPositionRelativeToNewPosition(sf::Vector2f &newPosition, sf::RenderTexture& renderTexture) {
    //menu options also need to be drawn relative to the default view
    sf::Vector2i componentPositionInPixels = renderTexture.mapCoordsToPixel(newPosition); //0, 0 in the view converted to window pixels

    float windowScale = renderTexture.getDefaultView().getSize().x / renderTexture.getView().getSize().x;

    //Tiled menu maps are drawn according to the view size, so have to scale the positions to the actual window size to draw to the default view
    float adjustedX = componentPositionInPixels.x + (initialPosition.x * windowScale);
    float adjustedY = componentPositionInPixels.y + (initialPosition.y * windowScale);

    sf::Vector2f componentPosition = sf::Vector2f(adjustedX, adjustedY);

    sf::Text::setPosition(componentPosition);
    boundingBox.left = newPosition.x;
    boundingBox.top = newPosition.y;
}
