#ifndef NEWNEW_MAPLOADER_H
#define NEWNEW_MAPLOADER_H


#include <tmxlite/Map.hpp>
#include "MenuMap.h"
#include "../asset/TextureManager.h"
#include "../asset/AssetPath.h"
#include "../map/TileMap.h"
#include "../ui/component/MenuLayer.h"
#include "../ui/component/MenuComponent.h"
#include "SceneMap.h"

class MapLoader {

public:
    MenuLayer loadMenuLayerMap(TextureManager& textureManager, std::string menuName);
    SceneMap loadSceneMap(TextureManager& textureManager, std::string sceneName);
private:
    static Logger logger;
};


#endif //NEWNEW_MAPLOADER_H
