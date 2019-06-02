//
// Created by William Curry on 2019-05-30.
//

#ifndef FRAMERATECOUNTER_H
#define FRAMERATECOUNTER_H


#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Text.hpp>

class FramerateCounter {

private:
    sf::Clock clock;
    std::unique_ptr<sf::Text> fpsText;
    int frames;

public:
    FramerateCounter(sf::Font* font);
    void update();
    sf::Text getFpsText();
};


#endif //FRAMERATECOUNTER_H
