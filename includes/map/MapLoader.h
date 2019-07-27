#ifndef NEWNEW_MAPLOADER_H
#define NEWNEW_MAPLOADER_H


#include <tmxlite/Map.hpp>
#include "MenuObjectMap.h"
#include "../asset/TextureManager.h"
#include "../asset/AssetPath.h"
#include "../map/TileMap.h"
#include "../ui/component/MenuLayer.h"
#include "../ui/component/MenuComponent.h"
#include "SceneMap.h"
#include "MenuMap.h"

class MapLoader {

public:
    MenuMap loadMenuMap(TextureManager& textureManager, std::string sceneName);
    SceneMap loadSceneMap(TextureManager& textureManager, std::string sceneName);
private:
    static Logger logger;
};


#endif //NEWNEW_MAPLOADER_H
