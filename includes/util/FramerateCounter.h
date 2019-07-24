#ifndef FRAMERATECOUNTER_H
#define FRAMERATECOUNTER_H


#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Text.hpp>

class FramerateCounter {

public:
    void initialize(sf::Font* font, sf::Vector2u windowSize, sf::Vector2f defaultWindowSize);
    sf::Time update();
    sf::Text getFpsText();
private:
    sf::Clock clock;
    sf::Text fpsText;
    int frames;
};


#endif //FRAMERATECOUNTER_H
