#ifndef NEWNEW_TEXTMANAGER_H
#define NEWNEW_TEXTMANAGER_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../controller/ControllerActionEvent.h"
#include "CloseDialogueEvent.h"
#include "OpenDialogueEvent.h"
#include "../events/EventBus.h"
#include <SFML/Graphics/Text.hpp>
#include "../../includes/events/EventBus.h"

class TextManager {
public:
    void initialize(std::shared_ptr<EventBus> eventBus, sf::Texture* texture, sf::Font* font, sf::View* view, sf::RenderWindow* window);
    void draw(sf::RenderWindow* window);
    void drawForDefaultView(sf::RenderWindow* window);
    void onControllerActionEvent(ControllerActionEvent* event);
    void onOpenDialogueEvent(OpenDialogueEvent* event);
private:
    std::shared_ptr<EventBus> eventBus;
    sf::Sprite dialogueBoxSprite;
    sf::Vector2f viewSize;
    sf::Text dialogueText;

    //TODO: any alternatives to keeping pointers to the window and view? global util? thats not really any better
    sf::RenderWindow* window;
    sf::View* view;

    bool showDialogueBox = false;
};


#endif //NEWNEW_TEXTMANAGER_H
