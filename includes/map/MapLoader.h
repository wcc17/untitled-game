#ifndef NEWNEW_MAPLOADER_H
#define NEWNEW_MAPLOADER_H


#include "../asset/TextureManager.h"

class MapLoader {

public:
    void loadMenuMap(TextureManager& textureManager);
    void loadTileMap(TextureManager& textureManager);
};


#endif //NEWNEW_MAPLOADER_H
