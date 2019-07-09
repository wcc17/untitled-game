#include "../../includes/asset/TextureManager.h"
#include "../../includes/asset/AssetPath.h"

TextureManager::TextureManager() { }

void TextureManager::loadTexture(std::string filename) {
    loadResource<sf::Texture>(filename, textureMap);
}

sf::Texture* TextureManager::getTexture(std::string filename) {
    return textureMap[filename].get();
}

void TextureManager::releaseTexture(std::string filename) {
    releaseResource(filename, textureMap);
}