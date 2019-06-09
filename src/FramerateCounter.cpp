#include <cmath>
#include "../includes/FramerateCounter.h"

FramerateCounter::FramerateCounter(sf::Font* font) {
    frames = 0;
    fpsText = std::unique_ptr<sf::Text>(new sf::Text(std::to_string(0), *font, 16));
    fpsText->setPosition(fpsText->getGlobalBounds().width/2, fpsText->getGlobalBounds().height/2);
    fpsText->scale({0.5f, 0.5f});
}

sf::Time FramerateCounter::update(sf::Vector2f viewPosition) {
    frames++;
    sf::Time elapsedTime = clock.restart();

    if (frames % 5 == 0) {
        float elapsed = elapsedTime.asSeconds();
        float fps = 1.0f / elapsed;
        fpsText->setString(std::to_string(fps));
    }

    //TODO: fix, no constants here, going to need ViewManager for this
    fpsText->setPosition(viewPosition.x - 190, viewPosition.y - 108);
    fpsText->setPosition(std::round(fpsText->getPosition().x), std::round(fpsText->getPosition().y));

    return elapsedTime;
}

sf::Text FramerateCounter::getFpsText() {
    return *fpsText;
}