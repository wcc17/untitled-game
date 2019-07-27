#ifndef NEWNEW_UICOMPONENT_H
#define NEWNEW_UICOMPONENT_H


#include <SFML/Graphics/Sprite.hpp>
#include <map>
#include "../../asset/TextureManager.h"
#include "../../scene/ObjectType.h"
#include "../../asset/AssetPath.h"

class UIComponent {

public:
    void initialize(std::string name, ObjectType type, sf::Vector2f initialPosition);
    std::string getName();
    ObjectType getType();
    sf::Vector2f getInitialPosition();

private:
    std::string name;
    ObjectType type;
    sf::Vector2f initialPosition;

    /**
     * what kind of menus are needed?
     *
     * Main menu
     *  -> starts the game
     *  -> edit the settings
     *
     * Player menu
     * -> edit party
     * -> manage inventory
     * -> view stats?
     * -> save the game
     *
     * battle menu
     * -> battle actions for each character
     * -> dialogue box to narrate the battle?
     *
     *
     * SelectableComponents will have a list of options for the player to choose from
     * I think all of these will be selectable components in one way or another
     *
     * Main menu will be a single selectable component
     *  -> starts the game starts the game
     *  -> choosing settings will open another selectable component
     *
     *
     * Player menu will be a selectable component
     *  -> choosing party will show the party (another selectable component)
     *  -> choosing inventory will show another selectable component
     *
     */

};


#endif //NEWNEW_UICOMPONENT_H
