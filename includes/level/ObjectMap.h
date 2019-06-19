#ifndef NEWNEW_OBJECTMAP_H
#define NEWNEW_OBJECTMAP_H


#include <tmxlite/ObjectGroup.hpp>
#include "../collisions/Collidable.h"

class ObjectMap {

public:
    void loadObjectLayer(const tmx::ObjectGroup& layer);
    std::vector<Collidable>& getMapCollidables(); //NOTE: returning a reference since they are used so often. Take care not to modify
    std::vector<Collidable> getNpcCollidables();
    Collidable getPlayerCollidable();

protected:
    void release();

private:
    void loadRectangleObjects(const tmx::Object& object);
    CollidableType determineCollidableType(std::string typeName);
    std::vector<Collidable> mapCollidables;
    std::vector<Collidable> npcCollidables;
    Collidable playerCollidable;
};


#endif //NEWNEW_OBJECTMAP_H
