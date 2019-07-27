#ifndef NEWNEW_SCENEOBJECTMAP_H
#define NEWNEW_SCENEOBJECTMAP_H

#include "ObjectMap.h"

class SceneObjectMap : public ObjectMap {

public:
    SceneObjectMap();
    void loadObjectLayer(const tmx::ObjectGroup& layer) override;
    void release() override;
    std::vector<std::shared_ptr<Collidable>>& getMapCollidables();
    std::vector<Collidable> getNpcCollidables();
    std::map<std::string, sf::IntRect> getNpcMoveBoundariesMap();
    std::map<std::string, std::string> getNpcNameToNpcAssetNameMap();
    Collidable getPlayerCollidable(std::string spawnName);
    std::string getPlayerSpawnPointName(std::string sceneName);
protected:
    void loadRectangleObjects(const tmx::Object& object) override;
private:
    std::map<std::string, sf::IntRect> npcMoveBoundaries;
    std::vector<Collidable> npcCollidables;
    std::map<std::string, std::string> npcNameToNpcAssetNameMap;
    std::vector<std::shared_ptr<Collidable>> mapCollidables;
    std::map<std::string, Collidable> playerCollidables;
    Logger logger;
};


#endif //NEWNEW_SCENEOBJECTMAP_H
