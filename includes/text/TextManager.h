#ifndef NEWNEW_TEXTMANAGER_H
#define NEWNEW_TEXTMANAGER_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include "../events/event/ControllerActionEvent.h"
#include "../events/event/CloseDialogueEvent.h"
#include "../events/event/OpenDialogueEvent.h"
#include "../events/EventBus.h"
#include <SFML/Graphics/Text.hpp>
#include "../../includes/events/EventBus.h"
#include "dialogue/DialogueEvent.h"
#include "../../includes/util/Logger.h"

class TextManager {
public:
    TextManager();
    void initialize(std::shared_ptr<EventBus> eventBus, sf::Texture* texture, sf::Font* font);
    void update(sf::RenderWindow* window, sf::View& view, sf::Time deltaTime);
    void drawToRenderTexture(sf::RenderTexture* renderTexture);
    void drawToRenderTextureForDefaultView(sf::RenderTexture* renderTexture);
    void setEntityDialogueEvents(std::vector<DialogueEvent> entityDialogueEvents);
private:
    std::shared_ptr<EventBus> eventBus;
    sf::Sprite dialogueBoxSprite;
    sf::Text dialogueText;
    std::string stringBeingDrawn;
    sf::Time stringDrawTimer;
    bool dialogueIsActive = false;
    bool dialoguePositionSet = false;
    Collidable entityPlayerInteractedWith;
    static Logger logger;

    std::unique_ptr<DialogueEvent> currentDialogueEvent;
    std::vector<DialogueEvent> entityDialogueEvents;
    DialogueEvent defaultDialogueEvent;

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
