#ifndef NEWNEW_VIEWMANAGER_H
#define NEWNEW_VIEWMANAGER_H

#include <SFML/Graphics/View.hpp>
#include "../events/EventBus.h"
#include "../events/event/PlayerPositionChangeEvent.h"
#include <cmath>

class ViewManager {
public:
    void initialize(std::shared_ptr<EventBus>);
    sf::View getView(); //TODO: does this have to be a pointer? Should it be a shared_ptr? View being a pointer is evidence that View needs to be moved to ViewManager and handled in GameManager

private:
    void onPlayerPositionChanged(PlayerPositionChangeEvent* event);
    void setViewCenterFromPlayerPosition(sf::FloatRect playerBounds);

    std::shared_ptr<EventBus> eventBus;
    sf::View view;
};


#endif //NEWNEW_VIEWMANAGER_H
