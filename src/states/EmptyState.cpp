#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "EmptyState.hpp"
#include "GameContext.hpp"


void EmptyState::init() {}

void EmptyState::handleInput() {
    while (const std::optional<sf::Event> event = getContext().window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) { getContext().window.close(); }
    }
}

void EmptyState::update() {}

void EmptyState::draw() {
    getContext().window.clear(sf::Color(30, 30, 30));
    getContext().window.display();
}
