#include "../../../includes/entity/character/NpcEntity.h"

void NpcEntity::initialize(sf::Texture* texture) {
    //TODO: name should come from the TileSet. Not sure how I'll swing this yet
    AnimatedEntity::initialize(texture, "npc1", CollidableType::NPC);

//    this->setPosition(); //TODO: position needs to be set before initializing animations?
    this->setFrameTime(sf::seconds(0.16f)); //TODO: not sure where I want to load this from yet
    initializeAnimations();
}

//TODO: this is the exact same as Player. I think this won't always be the same for specific types of Entities. Leaving for now
void NpcEntity::initializeAnimations() {

    //TODO: these constants are temporary until I figure out where I want to load this information from. Probably from a more specific derived NpcEntity class
    //TODO: replace 16.f for width, 26.f for height
    walkingAnimationDown.setSpriteSheet(*this->getTexture());
    walkingAnimationDown.addFrame(sf::IntRect(0, 0, 16.f, 26.f));
    walkingAnimationDown.addFrame(sf::IntRect(16.f, 0, 16.f, 26.f));
    walkingAnimationDown.addFrame(sf::IntRect(16.f*2, 0, 16.f, 26.f));
    walkingAnimationDown.addFrame(sf::IntRect(16.f*3, 0, 16.f, 26.f));

    walkingAnimationRight.setSpriteSheet(*this->getTexture());
    walkingAnimationRight.addFrame(sf::IntRect(0, 26.f, 16.f, 26.f));
    walkingAnimationRight.addFrame(sf::IntRect(16.f, 26.f, 16.f, 26.f));
    walkingAnimationRight.addFrame(sf::IntRect(16.f*2, 26.f, 16.f, 26.f));
    walkingAnimationRight.addFrame(sf::IntRect(16.f*3, 26.f, 16.f, 26.f));

    walkingAnimationUp.setSpriteSheet(*this->getTexture());
    walkingAnimationUp.addFrame(sf::IntRect(0, 26.f*2, 16.f, 26.f));
    walkingAnimationUp.addFrame(sf::IntRect(16.f, 26.f*2, 16.f, 26.f));
    walkingAnimationUp.addFrame(sf::IntRect(16.f*2, 26.f*2, 16.f, 26.f));
    walkingAnimationUp.addFrame(sf::IntRect(16.f*3, 26.f*2, 16.f, 26.f));

    walkingAnimationLeft.setSpriteSheet(*this->getTexture());
    walkingAnimationLeft.addFrame(sf::IntRect(0, 26.f*3, 16.f, 26.f));
    walkingAnimationLeft.addFrame(sf::IntRect(16.f, 26.f*3, 16.f, 26.f));
    walkingAnimationLeft.addFrame(sf::IntRect(16.f*2, 26.f*3, 16.f, 26.f));
    walkingAnimationLeft.addFrame(sf::IntRect(16.f*3, 26.f*3, 16.f, 26.f));

    this->currentAnimation = &walkingAnimationDown;
}