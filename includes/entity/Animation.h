#ifndef NEWNEW_ANIMATION_H
#define NEWNEW_ANIMATION_H

//https://github.com/SFML/SFML/wiki/Source:-AnimatedSprite

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>

class Animation {
public:
    Animation();

    void addFrame(sf::IntRect rect);
    void setSpriteSheet(const sf::Texture& texture);
    const sf::Texture* getSpriteSheet() const;
    int getSize() const;
    const sf::IntRect& getFrame(int n) const;

private:
    std::vector<sf::IntRect> m_frames;
    const sf::Texture* m_texture;
};


#endif //NEWNEW_ANIMATION_H
