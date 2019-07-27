#include "../../includes/map/MenuMap.h"

void MenuMap::loadObjectLayer(const tmx::ObjectGroup& layer) {
    menuObjectMap.loadObjectLayer(layer);
}

MenuObjectMap MenuMap::getMenuObjectMap() {
    return menuObjectMap;
}

MenuLayer MenuMap::getPlayerMenuLayer() {
    return playerMenuLayer;
}

void MenuMap::setPlayerMenuLayer(MenuLayer playerMenuLayer) {
    this->playerMenuLayer = playerMenuLayer;
}
