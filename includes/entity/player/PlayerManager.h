#ifndef NEWNEW_PLAYERMANAGER_H
#define NEWNEW_PLAYERMANAGER_H


#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <cmath>
#include "../../events/EventBus.h"
#include "../../collisions/PlayerCollisionEvent.h"
#include "Player.h"

class PlayerManager {
public:
    void initialize(std::shared_ptr<EventBus> eventBus, sf::Texture* playerTexture, const Collidable& playerCollidable);
    void update(sf::Time deltaTime, const sf::Vector2u& mapTileSize);
    void draw(sf::RenderWindow* window);
    Player getPlayer();
    sf::View* getView(); //TODO: does this have to be a pointer? Should it be a shared_ptr? View being a pointer is evidence that View needs to be moved to ViewManager and handled in GameManager

private:
    void onCollisionEvent(PlayerCollisionEvent* event);
    void setViewCenterFromPlayerPosition();
    void adjustPlayerAndViewPositions();

    std::shared_ptr<EventBus> eventBus;
    std::unique_ptr<sf::View> view;
    Player player;
};


#endif //NEWNEW_PLAYERMANAGER_H
