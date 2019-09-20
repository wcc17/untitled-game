#include "../../../includes/entity/components/Animation.h"

Animation::Animation() : m_texture(NULL) { }

void Animation::addFrame(sf::IntRect rect) {
    m_frames.push_back(rect);
}

void Animation::setSpriteSheet(const sf::Texture &texture) {
    m_texture = &texture;
}

const sf::Texture* Animation::getSpriteSheet() const {
    return m_texture;
}

int Animation::getSize() const {
    return m_frames.size();
}

const sf::IntRect& Animation::getFrame(int n) const {
    return m_frames[n];
}