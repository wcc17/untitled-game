#ifndef NEWNEW_MAPLOADER_H
#define NEWNEW_MAPLOADER_H


#include <tmxlite/Map.hpp>
#include "../asset/TextureManager.h"
#include "../asset/AssetPath.h"
#include "../map/TileMap.h"
#include "../ui/component/menu_component/MenuWithSelectorComponent.h"
#include "SceneMap.h"

class MapLoader {

public:
    SceneMap loadSceneMap(TextureManager& textureManager, std::string sceneName);
private:
    static Logger logger;
};


#endif //NEWNEW_MAPLOADER_H
