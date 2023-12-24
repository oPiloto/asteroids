#pragma once

#include "states/GameState.hpp"
#include "states/MenuState.hpp"

namespace aste {
    class Game {
    public:
        Game(const char *window_title);
        ~Game();

        void run();

    private:
        void input();
        void update();
        void render();

    private:
        std::shared_ptr<sf::RenderWindow> m_window;
        sf::Event m_event;
        StateStack m_state_stack;
        sf::Clock m_clock;
    };
} // namespace aste
