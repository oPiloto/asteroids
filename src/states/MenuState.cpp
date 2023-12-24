#include "MenuState.hpp"

namespace aste {
    MenuState::MenuState(StateStack &stack, sf::RenderWindow &window) :
        State(stack, window) {
        m_text.setString("Asteroids");
        m_text.setCharacterSize(50);
        m_text.setFont(Fonts::Exo2());
        m_text.setPosition((m_window.getSize().x - m_text.getLocalBounds().width) / 2,
            m_window.getSize().y / 12 * 2);

        m_start_button = std::make_shared<Button>(
            sf::Vector2f((m_window.getSize().x - 250) / 2, m_window.getSize().y / 12 * 5),
            sf::Vector2f(250.f, 50.f),
            "Start",
            18);
        m_exit_button = std::make_shared<Button>(
            sf::Vector2f((m_window.getSize().x - 250) / 2, m_window.getSize().y / 12 * 6),
            sf::Vector2f(250.f, 50.f),
            "Exit",
            18);
    }

    void MenuState::input() {
        if (m_start_button->state() == Button::PRESSED)
            go_to_game();

        if (m_exit_button->state() == Button::PRESSED)
            exit_game();
    }

    void MenuState::update(const float &delta_time) {
        m_start_button->update(m_window);
        m_exit_button->update(m_window);
    }

    void MenuState::render() {
        m_window.draw(m_text);
        m_window.draw(*m_start_button);
        m_window.draw(*m_exit_button);
    }

    void MenuState::go_to_game() {
        m_stack.push_state(new GameState(m_stack, m_window));
    }

    void MenuState::exit_game() { m_window.close(); }
} // namespace aste
