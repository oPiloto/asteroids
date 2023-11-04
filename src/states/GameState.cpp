#include "GameState.hpp"

namespace aste {
    GameState::GameState(StateStack &stack, std::shared_ptr<sf::RenderWindow> window) :
        State(stack, window), m_game_over(false), m_score(0) {
        // Score
        m_score_text.setCharacterSize(20.f);
        m_score_text.setPosition({20.f, 20.f});
        m_score_text.setFillColor(sf::Color::Green);
        m_score_text.setFont(Fonts::MartianMono());

        // Game over text
        m_game_over_text.setString("Game Over");
        m_game_over_text.setCharacterSize(30.f);
        m_game_over_text.setFont(Fonts::Exo2());
        m_game_over_text.setPosition(sf::Vector2f(
            (m_window->getSize().x - m_game_over_text.getLocalBounds().width) / 2,
            m_window->getSize().y / 12 * 4));
        m_game_over_text.setFillColor(sf::Color::White);

        // Game over buttons
        m_try_again_button = std::make_shared<Button>(
            sf::Vector2f((m_window->getSize().x - 250) / 2, m_window->getSize().y / 12 * 5),
            sf::Vector2f(250.f, 50.f),
            "Try again",
            18);
        m_back_to_menu_button = std::make_shared<Button>(
            sf::Vector2f((m_window->getSize().x - 250) / 2, m_window->getSize().y / 12 * 6),
            sf::Vector2f(250.f, 50.f),
            "Back to menu",
            18);

        // Ship
        m_ship = std::make_unique<Ship>();
        m_ship->set_position(
            sf::Vector2f(m_window->getSize().x / 2 - m_ship->size().x / 2,
                m_window->getSize().y / 2 - m_ship->size().y / 2));

        // Asteroids
        m_asteroid = std::make_unique<Asteroid>(3.f);
    }

    void GameState::input() {
        if (!m_game_over) {
            m_ship->input(*m_window);
            m_ship->back_to_screen(*m_window);
            m_asteroid->input(*m_window);
        } else {
            if (m_try_again_button->state() == Button::PRESSED) {
                m_game_over = false;
                reset_game();
            }

            if (m_back_to_menu_button->state() == Button::PRESSED) {
                m_game_over = false;
                return_to_menu();
            }
        }
    }

    void GameState::update(const float &delta_time) {
        m_score_text.setString("Score: " + std::to_string(m_score));

        for (auto asteroid : m_asteroid->get_asteroids_bounds())
            if (asteroid.intersects(m_ship->get_bounds()))
                m_game_over = true;

        if (!m_game_over) {
            m_ship->update(delta_time);
            m_asteroid->update(delta_time);
            m_asteroid->create_asteroids(delta_time);
            m_asteroid->check_collision(m_ship->shoots());
            if (m_asteroid->destroyed())
                m_score++;
        }

        // Game over buttons
        m_try_again_button->update(*m_window);
        m_back_to_menu_button->update(*m_window);
    }

    void GameState::render() {
        m_window->draw(*m_ship);
        m_window->draw(*m_asteroid);

        if (m_game_over) {
            m_window->draw(m_game_over_text);

            m_window->draw(*m_try_again_button);
            m_window->draw(*m_back_to_menu_button);
        }

        m_window->draw(m_score_text);
    }

    void GameState::return_to_menu() { m_stack.pop_state(); }

    void GameState::reset_game() {
        // Socre
        m_score = 0;

        // Ship
        m_ship = std::make_unique<Ship>();
        m_ship->set_position(
            sf::Vector2f(m_window->getSize().x / 2 - m_ship->size().x / 2,
                m_window->getSize().y / 2 - m_ship->size().y / 2));

        // Asteroids
        m_asteroid = std::make_unique<Asteroid>(3.f);
    }
} // namespace aste
