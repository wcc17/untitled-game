#ifndef NEWNEW_OBJECTMAP_H
#define NEWNEW_OBJECTMAP_H


#include <tmxlite/ObjectGroup.hpp>
#include <map>
#include "../collisions/Collidable.h"
#include "../util/Logger.h"

class ObjectMap {

public:
    void loadObjectLayer(const tmx::ObjectGroup& layer);

    /**
     * Lifecycle of map collidables and npcCollidables
     * NpcCollidables are copied into NpcManager a single time and used to create NpcEntity shared pointers that NpcManager handless
     *
     * Collidables are returned from getMapCollidables, which returns a reference to our vector of shared Collidable pointers
     * These pointers are passed to CollisionManager.handleCollisions, where they are checked for different types of collisions between player and collision
     * If a collidable has a hard collision with another entity, a reference to that collidable will be passed to the entity
     * If a collidable has a vicinity collision, the pointer will be passed to the entity. The entity clears these at the end of each frame and I confirmed that the strong ref count goes down to normal levels
     */
    std::vector<std::shared_ptr<Collidable>>& getMapCollidables();
    std::vector<Collidable> getNpcCollidables();
    std::map<std::string, sf::IntRect> getNpcMoveBoundariesMap();
    std::map<std::string, std::string> getNpcNameToNpcAssetNameMap();
    Collidable getPlayerCollidable();

protected:
    void release();

private:
    void loadRectangleObjects(const tmx::Object& object);
    ObjectType determineObjectType(std::string typeName);
    std::string getObjectPropertyValue(std::string propertyName, const std::vector<tmx::Property> objectProperties);
    std::map<std::string, sf::IntRect> npcMoveBoundaries;
    std::vector<Collidable> npcCollidables;
    std::map<std::string, std::string> npcNameToNpcAssetNameMap;
    std::vector<std::shared_ptr<Collidable>> mapCollidables;
    Collidable playerCollidable;

    static Logger logger;
};


#endif //NEWNEW_OBJECTMAP_H
