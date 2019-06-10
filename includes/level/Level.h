#ifndef NEWNEW_LEVEL_H
#define NEWNEW_LEVEL_H


#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <cmath>
#include "TileMap.h"

class Level : public sf::Drawable, public sf::Transformable, public TileMap {
public:
    void initialize(std::string tileMapPath);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    std::vector<Collidable> handleCollisions();
};


#endif //NEWNEW_LEVEL_H
