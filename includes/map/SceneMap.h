#ifndef NEWNEW_SCENEMAP_H
#define NEWNEW_SCENEMAP_H


#include "SceneObjectMap.h"
#include "Map.h"
#include "../asset/TextureManager.h"

class SceneMap : public Map {
public:
    void loadObjectLayer(const tmx::ObjectGroup& layer) override;
    std::vector<std::shared_ptr<Collidable>>& getMapCollidables();
    std::vector<Collidable> getNpcCollidables();
    std::map<std::string, sf::IntRect> getNpcMoveBoundariesMap();
    Collidable getPlayerCollidable(std::string spawnName);
    std::map<std::string, std::string> getNpcNameToNpcAssetNameMap();
    std::string getPlayerSpawnPointName(std::string sceneName);
    void release(TextureManager& textureManager) override;
private:
    SceneObjectMap sceneObjectMap;
};


#endif //NEWNEW_SCENEMAP_H
