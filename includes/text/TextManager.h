#ifndef NEWNEW_TEXTMANAGER_H
#define NEWNEW_TEXTMANAGER_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../events/event/ControllerActionEvent.h"
#include "../events/event/CloseDialogueEvent.h"
#include "../events/event/OpenDialogueEvent.h"
#include "../events/EventBus.h"
#include <SFML/Graphics/Text.hpp>
#include "../../includes/events/EventBus.h"

class TextManager {
public:
    void initialize(std::shared_ptr<EventBus> eventBus, sf::Texture* texture, sf::Font* font);
    void update();
    void draw(sf::RenderWindow* window);
    void drawForDefaultView(sf::RenderWindow* window);
    void onControllerActionEvent(ControllerActionEvent* event);
    void onOpenDialogueEvent(OpenDialogueEvent* event);
private:
    std::shared_ptr<EventBus> eventBus;
    sf::Sprite dialogueBoxSprite;
    sf::Text dialogueText;

    bool showDialogueBox = false;
};


#endif //NEWNEW_TEXTMANAGER_H
