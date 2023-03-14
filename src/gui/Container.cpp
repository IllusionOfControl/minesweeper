#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "Container.hpp"

Container::Container()
        : mChildren() {
}

void Container::pack(Component::Ptr component) {
    mChildren.push_back(component);
}

void Container::handleEvent(const sf::Event &event) {
    std::for_each(mChildren.begin(), mChildren.end(), [&](const auto &child) {
        child->handleEvent(event);
    });
}

void Container::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();

    std::for_each(mChildren.begin(), mChildren.end(), [&](const auto &child) {
        target.draw(*child, states);
    });
}
