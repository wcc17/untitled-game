//
// Created by William Curry on 2019-05-30.
//

#include "../includes/FramerateCounter.h"

FramerateCounter::FramerateCounter(sf::Font* font) {
    frames = 0;
    fpsText = std::unique_ptr<sf::Text>(new sf::Text(std::to_string(0), *font, 16));
    fpsText->setPosition(fpsText->getGlobalBounds().width/2, fpsText->getGlobalBounds().height/2);
}

void FramerateCounter::update() {
    frames++;
    float elapsed = clock.restart().asSeconds();

    if (frames % 5 == 0) {
        float fps = 1.0f / elapsed;
        fpsText->setString(std::to_string(fps));
    }
}

sf::Text FramerateCounter::getFpsText() {
    return *fpsText;
}