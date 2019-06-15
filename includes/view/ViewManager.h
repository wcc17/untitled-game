#ifndef NEWNEW_VIEWMANAGER_H
#define NEWNEW_VIEWMANAGER_H


#include <SFML/Graphics/View.hpp>
#include <SFML/System/Time.hpp>
#include <cmath>
#include "../events/EventBus.h"
#include "../controller/ControllerMoveEvent.h"
#include "../collisions/PlayerCollisionEvent.h"

class ViewManager {
public:
    void initialize(std::shared_ptr<EventBus> eventBus);
    void initializeViewForLevel(sf::Vector2f mapSizeInPixels);
    void update(sf::Time deltaTime);
    sf::View getView() const;

    void onMoveEvent(ControllerMoveEvent* event);
    void onCollisionEvent(PlayerCollisionEvent* event);
    void fixPositionOnCollision(sf::FloatRect playerRect, sf::FloatRect otherRect);
    void moveView(sf::Time deltaTime);
private:
    std::shared_ptr<EventBus> eventBus;
    sf::View view;
    sf::Vector2f movement;

    void roundViewCenter();
    void resetMovement();
};


#endif //NEWNEW_VIEWMANAGER_H
