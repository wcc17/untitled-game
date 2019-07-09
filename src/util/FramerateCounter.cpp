#include "../../includes/util/FramerateCounter.h"

void FramerateCounter::initialize(sf::Font* font) {
    frames = 0;
    fpsText.setString(std::to_string(0));
    fpsText.setFont(*font);
    fpsText.setCharacterSize(36);
    fpsText.setPosition(fpsText.getGlobalBounds().width/2, fpsText.getGlobalBounds().height/2);
}

sf::Time FramerateCounter::update() {
    frames++;
    sf::Time elapsedTime = clock.restart();

    if (frames % 10 == 0) {
        float elapsed = elapsedTime.asSeconds();
        float fps = 1.0f / elapsed;
        fpsText.setString(std::to_string(fps));
    }

    return elapsedTime;
}

sf::Text FramerateCounter::getFpsText() {
    return fpsText;
}