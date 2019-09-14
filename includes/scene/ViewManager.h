#ifndef NEWNEW_VIEWMANAGER_H
#define NEWNEW_VIEWMANAGER_H

#include <SFML/Graphics/View.hpp>
#include "../events/EventBus.h"
#include "../events/event/PlayerPositionChangeEvent.h"
#include <cmath>
#include <memory>

class ViewManager {
public:
    void initialize(std::shared_ptr<EventBus>);
    sf::View& getView();

private:
    void onPlayerPositionChanged(PlayerPositionChangeEvent* event);
    void setViewCenterFromPlayerPosition(sf::FloatRect playerBounds);

    std::shared_ptr<EventBus> eventBus;
    sf::View view;
};


#endif //NEWNEW_VIEWMANAGER_H
