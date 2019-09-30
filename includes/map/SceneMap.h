#ifndef NEWNEW_SCENEMAP_H
#define NEWNEW_SCENEMAP_H

#include "Map.h"
#include "../collisions/Collidable.h"

class SceneMap : public Map {

public:
    SceneMap();
    void loadObjectLayer(const tmx::ObjectGroup& layer);
    virtual void release(TextureManager& textureManager) override;
    std::vector<std::shared_ptr<Collidable>>& getMapCollidables();
    std::vector<Collidable> getNpcCollidables();
    std::map<std::string, sf::IntRect> getNpcMoveBoundariesMap();
    std::map<std::string, std::vector<tmx::Property>> getNpcNameToPropertiesMap();
    Collidable getPlayerCollidable(std::string spawnName);
    std::string getPlayerSpawnNameForPreviousToCurrentSceneTransition(std::string sceneName);
protected:
    void loadRectangleObjects(const tmx::Object& object) override;
private:
    std::map<std::string, sf::IntRect> npcMoveBoundaries;
    std::vector<Collidable> npcCollidables;
    std::map<std::string, std::vector<tmx::Property>> npcNameToNpcPropertyMap;
    std::vector<std::shared_ptr<Collidable>> mapCollidables;
    std::map<std::string, Collidable> playerCollidables;
    Logger logger;
};


#endif //NEWNEW_SCENEMAP_H
