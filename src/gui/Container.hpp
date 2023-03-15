#ifndef MINESWEEPER_CONTAINER_HPP
#define MINESWEEPER_CONTAINER_HPP

#include <vector>
#include <memory>
#include "Component.hpp"


class Container : public Component {
public:
    typedef std::shared_ptr<Container> Ptr;

public:
    Container();

    void pack(const Component::Ptr& component);

    virtual void handleEvent(const sf::Event &event);

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    std::vector<Component::Ptr> mChildren;
    int mSelectedChild{};
};

#endif //MINESWEEPER_CONTAINER_HPP
