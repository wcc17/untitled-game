#ifndef NEWNEW_LEVEL_H
#define NEWNEW_LEVEL_H


#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

class Level : public sf::Sprite {
public:
    Level(sf::Texture* texture, float windowWidth, float windowHeight);
    sf::View getView() const;
    void update(sf::Time deltaTime);
    void moveUp();
    void moveLeft();
    void moveDown();
    void moveRight();
    void stop();

private:
    sf::View view;
    sf::Vector2f movement;
    float speed;

    void resetMovement();
};


#endif //NEWNEW_LEVEL_H
