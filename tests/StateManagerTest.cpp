#include <catch2/catch_test_macros.hpp>

#include "managers/StateManager.hpp"

namespace {
    // Minimal State implementation; the State interface is SFML-free, so the
    // manager's stack logic can be exercised without a window.
    struct FakeState : State {
        int *initCount;
        explicit FakeState(int *counter) : initCount(counter) {}
        void init() override { ++(*initCount); }
        void handleInput() override {}
        void update() override {}
        void draw() override {}
    };
}

TEST_CASE("adding a state makes it active and initializes it once") {
    StateManager manager;
    REQUIRE(manager.isEmpty());

    int init1 = 0;
    auto *s1 = new FakeState(&init1);
    manager.addState(StateRef(s1));
    manager.processStateChanges();

    REQUIRE_FALSE(manager.isEmpty());
    REQUIRE(manager.getActiveState().get() == s1);
    REQUIRE(init1 == 1);
}

TEST_CASE("replacing swaps the active state") {
    StateManager manager;
    int a = 0, b = 0;
    auto *s1 = new FakeState(&a);
    auto *s2 = new FakeState(&b);

    manager.addState(StateRef(s1));
    manager.processStateChanges();

    manager.addState(StateRef(s2), true); // replacing
    manager.processStateChanges();

    REQUIRE(manager.getActiveState().get() == s2);
    REQUIRE(b == 1);
}

TEST_CASE("pushing then removing restores the previous state") {
    StateManager manager;
    int a = 0, b = 0;
    auto *s1 = new FakeState(&a);
    auto *s2 = new FakeState(&b);

    manager.addState(StateRef(s1));
    manager.processStateChanges();

    manager.addState(StateRef(s2), false); // push, keep previous
    manager.processStateChanges();
    REQUIRE(manager.getActiveState().get() == s2);

    manager.removeState();
    manager.processStateChanges();
    REQUIRE(manager.getActiveState().get() == s1);
}
