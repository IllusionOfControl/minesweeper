#ifndef MINESWEEPER_COMPONENT_HPP
#define MINESWEEPER_COMPONENT_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <memory>


namespace sf {
    class Event;
}

class Component : public sf::Drawable, public sf::Transformable {
public:
    typedef std::shared_ptr<Component> Ptr;


public:
    Component();

    virtual ~Component();

    virtual bool isSelected() const;

    virtual void select();

    virtual void deselect();

    virtual void handleEvent(const sf::Event &event) = 0;


private:
    bool mIsSelected;
};

#endif //MINESWEEPER_COMPONENT_HPP
