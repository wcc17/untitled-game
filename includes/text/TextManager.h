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
#include "dialogue/DialogueEvent.h"

class TextManager {
public:
    void initialize(std::shared_ptr<EventBus> eventBus, sf::Texture* texture, sf::Font* font);
    void update(sf::RenderWindow* window, sf::View& view, sf::Time deltaTime);
    void draw(sf::RenderWindow* window);
    void drawForDefaultView(sf::RenderWindow* window);
private:
    std::shared_ptr<EventBus> eventBus;
    std::unique_ptr<DialogueEvent> dialogueEvent;
    sf::Sprite dialogueBoxSprite;
    sf::Text dialogueText;
    std::string stringBeingDrawn;
    sf::Time stringDrawTimer;
    bool dialogueIsActive = false;
    bool dialoguePositionSet = false;

    void onControllerActionEvent(ControllerActionEvent* event);
    void onOpenDialogueEvent(OpenDialogueEvent* event);
    void closeDialogue();
    void setPositionsOnDialogueIsActive(sf::RenderWindow* window, sf::View& view);
    void updateDialogueBoxPosition(sf::View& view);
    void updateDialogueTextPosition(sf::RenderWindow* window, sf::View& view);
    void initializeText();
    void updateText(sf::Time deltaTime);
    void drawMoreText();
    void rushDrawText();
    void startNextDialogue();
};


#endif //NEWNEW_TEXTMANAGER_H
