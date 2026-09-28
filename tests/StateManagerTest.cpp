#include <catch2/catch_test_macros.hpp>

#include "managers/StateManager.hpp"

namespace {
    // Minimal State implementation; the State interface is SFML-free, so the
    // manager's stack logic can be exercised without a window.
    struct FakeState : State {
        int* initCount = nullptr;
        int* pauseCount = nullptr;
        int* resumeCount = nullptr;

        FakeState(int* inits, int* pauses = nullptr, int* resumes = nullptr)
            : initCount(inits), pauseCount(pauses), resumeCount(resumes) {}

        void init() override { if (initCount) ++(*initCount); }
        void handleInput() override {}
        void update() override {}
        void draw() override {}
        void pause() override { if (pauseCount) ++(*pauseCount); }
        void resume() override { if (resumeCount) ++(*resumeCount); }
    };
}

TEST_CASE("pushing a state makes it active and initializes it once") {
    StateManager manager;
    REQUIRE(manager.isEmpty());
    REQUIRE(manager.getActiveState() == nullptr);

    int init1 = 0;
    manager.registerState(StateID::MainMenu, [&]() {
        return std::make_unique<FakeState>(&init1);
    });

    manager.pushState(StateID::MainMenu);
    manager.processStateChanges();

    REQUIRE_FALSE(manager.isEmpty());
    REQUIRE(manager.getActiveState() != nullptr);
    REQUIRE(init1 == 1);
}

TEST_CASE("changing swaps the active state") {
    StateManager manager;
    int a = 0, b = 0;

    manager.registerState(StateID::MainMenu, [&]() {
        return std::make_unique<FakeState>(&a);
    });
    manager.registerState(StateID::Game, [&]() {
        return std::make_unique<FakeState>(&b);
    });

    manager.pushState(StateID::MainMenu);
    manager.processStateChanges();
    REQUIRE(a == 1);

    manager.changeState(StateID::Game);
    manager.processStateChanges();

    REQUIRE(b == 1);
    REQUIRE_FALSE(manager.isEmpty());
}

TEST_CASE("pushing then popping pauses, initializes, and resumes previous state") {
    StateManager manager;
    int initA = 0, pauseA = 0, resumeA = 0;
    int initB = 0;

    manager.registerState(StateID::MainMenu, [&]() {
        return std::make_unique<FakeState>(&initA, &pauseA, &resumeA);
    });
    manager.registerState(StateID::Game, [&]() {
        return std::make_unique<FakeState>(&initB);
    });

    manager.pushState(StateID::MainMenu);
    manager.processStateChanges();
    REQUIRE(initA == 1);
    REQUIRE(pauseA == 0);

    manager.pushState(StateID::Game);
    manager.processStateChanges();
    REQUIRE(pauseA == 1);
    REQUIRE(initB == 1);

    manager.popState();
    manager.processStateChanges();
    REQUIRE(resumeA == 1);
    REQUIRE_FALSE(manager.isEmpty());
}

TEST_CASE("clearing states empties the state stack") {
    StateManager manager;
    int initA = 0;

    manager.registerState(StateID::MainMenu, [&]() {
        return std::make_unique<FakeState>(&initA);
    });

    manager.pushState(StateID::MainMenu);
    manager.processStateChanges();
    REQUIRE_FALSE(manager.isEmpty());

    manager.clearStates();
    manager.processStateChanges();
    REQUIRE(manager.isEmpty());
    REQUIRE(manager.getActiveState() == nullptr);
}

TEST_CASE("pushing unregistered state throws runtime_error") {
    StateManager manager;
    manager.pushState(StateID::DifficultyMenu);
    REQUIRE_THROWS_AS(manager.processStateChanges(), std::runtime_error);
}
