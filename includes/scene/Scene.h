#ifndef NEWNEW_SCENE_H
#define NEWNEW_SCENE_H


#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <cmath>
#include "../map/TileMap.h"
#include "../util/Logger.h"
#include "../asset/TextureManager.h"
#include "../map/SceneMap.h"
#include "../collisions/Collidable.h"
#include "../map/MapLoader.h"
#include "../ui/manager/UIManager.h"
#include "../events/EventBus.h"
#include "../events/event/ControllerMenuEvent.h"
#include "../events/event/ControllerCancelEvent.h"
#include "../events/event/ControllerMoveEvent.h"
#include "../events/event/ControllerMenuMoveEvent.h"
#include "../events/event/PauseGameEvent.h"
#include "../events/event/UnPauseGameEvent.h"

class Scene : public sf::Drawable, public sf::Transformable {
public:
    virtual void initialize(
            std::shared_ptr<EventBus> eventBus,
            std::string sceneName,
            std::string previousSceneName,
            TextureManager& textureManager,
            sf::Font* font,
            sf::Vector2u windowSize,
            sf::Vector2f defaultWindowSize);
    virtual void update(sf::Time elapsedTime, bool isPaused, sf::RenderTexture& renderTexture, sf::View& view) {};
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {};
    virtual void release(TextureManager& textureManager) {};
    virtual std::string getSceneName();
    virtual void openDialogue(std::string dialogueTextAssetName) {};
    virtual void closeDialogue() {};
    virtual void handleControllerMenuButtonPressed() {};
    virtual void handleControllerActionButtonPressed() {};
    virtual void handleControllerCancelButtonPressed() {};
    virtual void handleControllerMenuMoveButtonPressed(MoveDirection direction) {};

protected:
    std::string sceneName;
    sf::Texture* texture;
    std::shared_ptr<EventBus> eventBus;

private:
    static Logger logger;
};


#endif //NEWNEW_SCENE_H
