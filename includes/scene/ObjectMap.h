#ifndef NEWNEW_OBJECTMAP_H
#define NEWNEW_OBJECTMAP_H


#include <tmxlite/ObjectGroup.hpp>
#include "../collisions/Collidable.h"

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
    Collidable getPlayerCollidable();

protected:
    void release();

private:
    void loadRectangleObjects(const tmx::Object& object);
    CollidableType determineCollidableType(std::string typeName);
    std::vector<std::shared_ptr<Collidable>> mapCollidables;
    std::vector<Collidable> npcCollidables;
    Collidable playerCollidable;
};


#endif //NEWNEW_OBJECTMAP_H
