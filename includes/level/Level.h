#ifndef NEWNEW_LEVEL_H
#define NEWNEW_LEVEL_H


#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Time.hpp>
#include <cmath>
#include "TileMap.h"
#include "../entity/Entity.h"
#include "../asset/AssetPath.h"

class Level : public sf::Drawable, public sf::Transformable, public TileMap {
public:
    void initialize(std::string tileMapPath);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update(sf::Time deltaTime);
    void handleCollisions();
    void handleNoTypeCollision();
    void handleDoorCollision();
    void handleSignCollision();
};


#endif //NEWNEW_LEVEL_H
