#ifndef NEWNEW_OBJECTMAP_H
#define NEWNEW_OBJECTMAP_H


#include <tmxlite/ObjectGroup.hpp>
#include "../collisions/Collidable.h"

class ObjectMap {

public:
    void loadObjectLayer(tmx::ObjectGroup layer);
    std::vector<Collidable> getMapCollidables();
    std::vector<Collidable> getNpcCollidables();

protected:
    void release();

private:
    std::vector<Collidable> mapCollidables;
    std::vector<Collidable> npcCollidables;
    void loadRectangleObjects(tmx::Object object, std::string layerName);
    CollidableType getCollidableType(std::string typeName);
};


#endif //NEWNEW_OBJECTMAP_H
