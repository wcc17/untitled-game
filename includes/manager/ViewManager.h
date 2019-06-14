#ifndef NEWNEW_VIEWMANAGER_H
#define NEWNEW_VIEWMANAGER_H


#include <SFML/Graphics/View.hpp>
#include <SFML/System/Time.hpp>
#include <cmath>
#include "../events/EventBus.h"
#include "../controller/MoveEvent.h"
#include "CollisionEvent.h"

class ViewManager {
public:
    void initialize(std::shared_ptr<EventBus> eventBus);
    void initializeViewForLevel(sf::Vector2f mapSizeInPixels);
    void update(sf::Time deltaTime);
    sf::View getView() const;

    void onMoveEvent(MoveEvent* event);
    void onCollisionEvent(CollisionEvent* event);
    void moveView(sf::Time deltaTime);
    void undoMovement();
    sf::Vector2f getViewPosition();
private:
    std::shared_ptr<EventBus> eventBus;
    sf::View view;
    sf::Vector2f movement;
    sf::Vector2f previousPosition;

    void roundViewCenter();
    void resetMovement();
};


#endif //NEWNEW_VIEWMANAGER_H
