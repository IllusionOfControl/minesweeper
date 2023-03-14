#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "Container.hpp"

Container::Container()
        : mChildren(), mSelectedChild(-1) {
}

void Container::pack(Component::Ptr component) {
    mChildren.push_back(component);
}

bool Container::isSelectable() const {
    return false;
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

bool Container::hasSelection() const {
    return mSelectedChild >= 0;
}

void Container::select(std::size_t index) {
    if (mChildren[index]->isSelectable()) {
        if (hasSelection())
            mChildren[mSelectedChild]->deselect();

        mChildren[index]->select();
        mSelectedChild = index;
    }
}

void Container::selectNext() {
    if (!hasSelection())
        return;

    // Search next component that is selectable, wrap around if necessary
    int next = mSelectedChild;
    do
        next = (next + 1) % mChildren.size();
    while (!mChildren[next]->isSelectable());

    // Select that component
    select(next);
}

void Container::selectPrevious() {
    if (!hasSelection())
        return;

    // Search previous component that is selectable, wrap around if necessary
    int prev = mSelectedChild;
    do
        prev = (prev + mChildren.size() - 1) % mChildren.size();
    while (!mChildren[prev]->isSelectable());

    // Select that component
    select(prev);
}
