#include "../../../../includes/ui/component/menu_component/PartyMenuComponent.h"

void PartyMenuComponent::initializeMenuComponent(sf::Font* font, float windowScale) {
    partyMemberNames.push_back("Charlie");
    partyMemberNames.push_back("Louie");
    partyMemberNames.push_back("Henry");
    partyMemberNames.push_back("Edgar");
    partyMemberNames.push_back("Victoria");
    partyMemberNames.push_back("Tracy");

    buildMenuOptions();

    MenuComponent::initializeMenuComponent(font, windowScale);
}

void PartyMenuComponent::buildMenuOptions() {
    //get a copy of the base menu option, then remove it from the list of menu options to avoid duplicates
    MenuOptionComponent baseMenuOption = this->getBaseMenuOption();
    menuOptions.clear();

    float menuHeight = this->getBoundingBox().height;
    float menuOptionHeight = baseMenuOption.getBoundingBox().height;
    int numberOfPartyMembers = partyMemberNames.size();

    float spaceBetweenMenuOptions = menuHeight / (partyMemberNames.size() * menuOptionHeight);

    for(int i = 0; i < numberOfPartyMembers; i++) {
        MenuOptionComponent menuOption;
        std::string displayText = partyMemberNames[i];
        std::string opensToMenu = ""; //TODO: will open to another menu that I haven't thought about yet
        bool isBaseMenuOption = false;

        float x = baseMenuOption.getBoundingBox().left;
        float y = baseMenuOption.getBoundingBox().top + ((menuOptionHeight + spaceBetweenMenuOptions) * i);
        float width = baseMenuOption.getBoundingBox().width;
        float height = baseMenuOption.getBoundingBox().height;
        sf::FloatRect menuOptionBoundingBox = sf::FloatRect(x, y, width, height);

        menuOption.initialize(std::to_string(i), ObjectType::MENU_OPTION, menuOptionBoundingBox, i, displayText, opensToMenu, isBaseMenuOption);
        this->addMenuOption(menuOption);
    }
}