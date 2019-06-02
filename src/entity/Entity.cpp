#include "../../includes/entity/Entity.h"

Entity::Entity(sf::Texture *texture) {
    this->setTexture(*texture);

    //TODO: need a better way to set the scale. other sprites will need to have the same scale
    this->scale(sf::Vector2f(10.f, 10.f));
}