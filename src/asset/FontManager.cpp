#include "../../includes/asset/FontManager.h"

FontManager::FontManager() { }

void FontManager::loadFont(std::string filename) {
    loadResource<sf::Font>(filename, fontMap);
}

sf::Font* FontManager::getFont(std::string filename) {
    return fontMap[filename].get();
}

void FontManager::releaseFont(std::string filename) {
    releaseResource(filename, fontMap);
}

void FontManager::releaseFonts() {
    releaseFont(FontPath::OPENSANS_REGULAR);
    releaseFont(FontPath::OPENSANS_BOLD);
}