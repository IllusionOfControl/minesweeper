#ifndef MINESWEEPER_PASSIVECOMPONENT_HPP
#define MINESWEEPER_PASSIVECOMPONENT_HPP

#include "Component.hpp"

namespace sf {
    class Event;
}

// Base class for non-interactive widgets (background, indicators). They are
// drawn but ignore input and selection, so the only thing they must provide is
// an empty handleEvent; select/deselect/isSelected keep Component's defaults.
class PassiveComponent : public Component {
public:
    void handleEvent(const sf::Event &) override {}
};

#endif //MINESWEEPER_PASSIVECOMPONENT_HPP
