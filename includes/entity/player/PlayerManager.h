#ifndef NEWNEW_PLAYERMANAGER_H
#define NEWNEW_PLAYERMANAGER_H


#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <cmath>
#include "../../events/EventBus.h"
#include "../../controller/ControllerMoveEvent.h"
#include "../../collisions/PlayerCollisionEvent.h"
#include "Player.h"

class PlayerManager {
public:
    void initialize(std::shared_ptr<EventBus> eventBus, sf::Texture* playerTexture, Collidable playerCollidable);
    void update(sf::Time deltaTime);
    void draw(sf::RenderWindow* window);
    void move(sf::Time deltaTime);
    Player getPlayer() const;
    sf::View getView() const;

private:
    void onMoveEvent(ControllerMoveEvent* event);
    void onCollisionEvent(PlayerCollisionEvent* event);
    void setViewCenterFromPlayerPosition();
    void adjustPlayerAndViewPositions();


    std::shared_ptr<EventBus> eventBus;
    sf::View view;
    Player player;
};


#endif //NEWNEW_PLAYERMANAGER_H
