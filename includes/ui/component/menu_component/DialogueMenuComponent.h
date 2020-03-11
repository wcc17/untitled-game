#ifndef NEWNEW_DIALOGUEMENUCOMPONENT_H
#define NEWNEW_DIALOGUEMENUCOMPONENT_H

#include <string>
#include "MenuWithSelectorComponent.h"
#include "../../dialogue/DialogueManager.h"

class DialogueMenuComponent : public BaseMenuComponent {
public:
    void initialize(
            sf::Font *font,
            float windowScale,
            sf::Texture *componentTexture,
            ScreenPosition screenPosition,
            UIComponentType componentType) override;
    void update(
            sf::RenderTexture& renderTexture,
            sf::View& view,
            sf::Time deltaTime) override;
    void setEntityDialogueEvents(std::vector<DialogueEvent> entityDialogueEvents);
    void openDialogueWithSubstitutions(
            std::string nameOfDialogueTextAsset,
            std::vector<std::string> textSubstitutions) override;
    void openDialogue(std::string nameOfDialogueTextAsset) override;
    void handleControllerActionButtonPressed() override;
    bool componentActionIsFinished() override;

private:
    DialogueManager dialogueManager;
    void updateTextShownInComponent(std::string textToDraw);
};


#endif //NEWNEW_DIALOGUEMENUCOMPONENT_H
