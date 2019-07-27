#ifndef NEWNEW_UICOMPONENT_H
#define NEWNEW_UICOMPONENT_H


#include <SFML/Graphics/Sprite.hpp>
#include <map>
#include "../../asset/TextureManager.h"
#include "../../map/ObjectType.h"
#include "../../asset/AssetPath.h"

class UIComponent {

public:
    void initialize(std::string name, ObjectType type, sf::FloatRect boundingBox);
    std::string getName();
    ObjectType getType();
    sf::FloatRect getBoundingBox();

private:
    std::string name;
    ObjectType type;
    sf::FloatRect boundingBox;
};


#endif //NEWNEW_UICOMPONENT_H
