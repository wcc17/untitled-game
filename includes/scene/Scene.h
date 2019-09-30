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

class Scene : public sf::Drawable, public sf::Transformable {
public:
    virtual void initialize(std::string sceneName, TextureManager& textureManager) {};
    virtual void update() {};
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {};
    virtual void release(TextureManager& textureManager) {};
    virtual std::string getSceneName();

protected:
    std::string sceneName;
    sf::Texture* texture;

private:
    static Logger logger;
};


#endif //NEWNEW_SCENE_H
