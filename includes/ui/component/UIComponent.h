#ifndef NEWNEW_UICOMPONENT_H
#define NEWNEW_UICOMPONENT_H


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <map>
#include "../../asset/TextureManager.h"
#include "../../map/ObjectType.h"
#include "../../asset/AssetPath.h"

class UIComponent {

public:
    void initialize(std::string name, ObjectType type);
    std::string getName();
    ObjectType getType();

private:
    std::string name;
    ObjectType type;
};


#endif //NEWNEW_UICOMPONENT_H
