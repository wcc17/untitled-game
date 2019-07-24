#include "../../../includes/ui/component/UIComponent.h"
#include "../../../includes/asset/AssetPath.h"

void UIComponent::initialize(std::string assetName, sf::Texture* texture) {
    this->assetName = assetName;
    setTexture(*texture);
}

std::string UIComponent::getAssetName() {
    return this->assetName;
}