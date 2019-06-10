#ifndef NEWNEW_VIEWMANAGER_H
#define NEWNEW_VIEWMANAGER_H


#include <SFML/Graphics/View.hpp>
#include <SFML/System/Time.hpp>
#include <cmath>

class ViewManager {
public:
    void initializeViewForLevel(sf::Vector2f mapSizeInPixels, sf::Vector2u windowSize);
    void update(sf::Time deltaTime);
    sf::View getView() const;

    void moveUp();
    void moveLeft();
    void moveDown();
    void moveRight();
    void stop();
    sf::Vector2f getViewPosition();
private:
    sf::View view;
    sf::Vector2f movement;

    void resetMovement();
};


#endif //NEWNEW_VIEWMANAGER_H
