#ifndef NEWNEW_LEVEL_H
#define NEWNEW_LEVEL_H


#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Time.hpp>
#include <cmath>
#include "TileMap.h"
#include "../Entity.h"
#include "../../../includes/asset/AssetPath.h"

class Level : public sf::Drawable, public sf::Transformable, public TileMap, public Entity {
public:
    Level(float windowWidth, float windowHeight, std::string tileMapPath);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update(sf::Time deltaTime);
    void handleCollisions();
    void handleNoTypeCollision();
    void handleDoorCollision();
    void handleSignCollision();
    void moveUp();
    void moveLeft();
    void moveDown();
    void moveRight();
    void stop();
    sf::View getView() const;
    sf::Vector2f getViewPosition();

private:
    sf::View view;
    sf::Vector2f movement;
    float speed;

    void resetMovement();
};


#endif //NEWNEW_LEVEL_H
