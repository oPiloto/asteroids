#pragma once

#include "GameState.hpp"
#include "State.hpp"
#include "ui/Button.hpp"

namespace aste {
    class MenuState : public State {
    public:
        MenuState(StateStack &stack, std::shared_ptr<sf::RenderWindow> window);
        ~MenuState() = default;

        void input();
        void update(const float &delta_time);
        void render();

    private:
        void go_to_game();
        void exit_game();

    private:
        sf::Text m_text;
        std::shared_ptr<Button> m_start_button;
        std::shared_ptr<Button> m_exit_button;
    };
} // namespace aste
