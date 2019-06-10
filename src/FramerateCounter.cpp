#include <cmath>
#include "../includes/FramerateCounter.h"

FramerateCounter::FramerateCounter(sf::Font* font) {
    frames = 0;
    fpsText = std::unique_ptr<sf::Text>(new sf::Text(std::to_string(0), *font, 24));
    fpsText->setPosition(fpsText->getGlobalBounds().width/2, fpsText->getGlobalBounds().height/2);
}

sf::Time FramerateCounter::update() {
    frames++;
    sf::Time elapsedTime = clock.restart();

    if (frames % 5 == 0) {
        float elapsed = elapsedTime.asSeconds();
        float fps = 1.0f / elapsed;
        fpsText->setString(std::to_string(fps));
    }

    return elapsedTime;
}

sf::Text FramerateCounter::getFpsText() {
    return *fpsText;
}