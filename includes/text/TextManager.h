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
    void update(sf::RenderWindow* window, sf::View& view);
    void draw(sf::RenderWindow* window);
    void drawForDefaultView(sf::RenderWindow* window);
private:
    std::shared_ptr<EventBus> eventBus;
    sf::Sprite dialogueBoxSprite;
    sf::Text dialogueText;
    std::string stringToDraw;
    std::string stringReadyToDraw; //this will only be a part of stringToDraw, as the string is drawn one character at a time

    bool dialogueIsActive = false;
    bool dialoguePositionSet = false;
    void onControllerActionEvent(ControllerActionEvent* event);
    void onOpenDialogueEvent(OpenDialogueEvent* event);
    void closeDialogue();
    void setPositionsOnDialogueIsActive(sf::RenderWindow* window, sf::View& view);
    void updateDialogueBoxPosition(sf::View& view);
    void updateDialogueTextPosition(sf::RenderWindow* window, sf::View& view);
};


#endif //NEWNEW_TEXTMANAGER_H
