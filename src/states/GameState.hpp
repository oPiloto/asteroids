#pragma once

#include "State.hpp"
#include "obj/asteroid/Asteroid.hpp"
#include "obj/ship/Ship.hpp"
#include "ui/Button.hpp"

namespace aste {
    class GameState : public State {
    public:
        GameState(StateStack &stack, sf::RenderWindow &window);
        ~GameState();

        void input();
        void update(const float &delta_time);
        void render();

    private:
        void return_to_menu();
        void reset_game();

    private:
        bool m_game_over;
        int m_score;
        sf::Text m_score_text;
        sf::Text m_game_over_text;

        // Game over buttons
        std::shared_ptr<Button> m_try_again_button;
        std::shared_ptr<Button> m_back_to_menu_button;

        // Ship
        std::unique_ptr<Ship> m_ship;

        // Asteroids
        Asteroid *m_asteroid;
    };
} // namespace aste
