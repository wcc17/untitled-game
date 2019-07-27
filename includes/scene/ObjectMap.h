#ifndef NEWNEW_OBJECTMAP_H
#define NEWNEW_OBJECTMAP_H


#include <tmxlite/ObjectGroup.hpp>
#include <map>
#include "../collisions/Collidable.h"
#include "../util/Logger.h"

class ObjectMap {

public:
    ObjectMap();
    virtual void loadObjectLayer(const tmx::ObjectGroup& layer);
    virtual void release();

protected:
    virtual void loadRectangleObjects(const tmx::Object& object);
    ObjectType determineObjectType(std::string typeName);
    std::string getObjectPropertyValue(std::string propertyName, const std::vector<tmx::Property> objectProperties);
    Logger logger;
};


#endif //NEWNEW_OBJECTMAP_H
