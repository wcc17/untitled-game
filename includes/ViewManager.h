#ifndef NEWNEW_VIEWMANAGER_H
#define NEWNEW_VIEWMANAGER_H


#include <SFML/Graphics/View.hpp>
#include <SFML/System/Time.hpp>
#include <cmath>

class ViewManager {
public:
    void initializeViewForLevel(sf::Vector2f mapSizeInPixels);
    void update(sf::Time deltaTime);
    sf::View getView() const;

    void moveView(sf::Time deltaTime);
    void moveUp();
    void moveLeft();
    void moveDown();
    void moveRight();
    void stop();
    void undoMovement();
    sf::Vector2f getViewPosition();
private:
    sf::View view;
    sf::Vector2f movement;
    sf::Vector2f previousPosition;

    void resetMovement();
};


#endif //NEWNEW_VIEWMANAGER_H
