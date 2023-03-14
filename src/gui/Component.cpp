#include "Component.hpp"

Component::Component()
        : mIsSelected(false)
        , mIsActive(false) {
}

Component::~Component() = default;

bool Component::isSelected() const {
    return mIsSelected;
}

void Component::select() {
    mIsSelected = true;
}

void Component::deselect() {
    mIsSelected = false;
}
