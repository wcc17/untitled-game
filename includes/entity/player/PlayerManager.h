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
    void update(sf::Time deltaTime, sf::Vector2u mapTileSize, sf::Vector2u mapSizeInPixels);
    void draw(sf::RenderWindow* window);
    Player getPlayer() const;
    sf::View getView() const;

private:
    void onMoveEvent(ControllerMoveEvent* event);
    void onCollisionEvent(PlayerCollisionEvent* event);
    void setViewCenterFromPlayerPosition();
    void adjustPlayerAndViewPositions();

    MoveDirection currentDirection = MoveDirection::NONE;
    std::shared_ptr<EventBus> eventBus;
    sf::View view;
    Player player;
};


#endif //NEWNEW_PLAYERMANAGER_H
