#include "Game.hpp"

namespace aste {
    Game::Game(const char *window_title) {
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;
        m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1000, 950), window_title, sf::Style::Close, settings);
        m_window->setFramerateLimit(120);

        m_state_stack.push_state(std::make_unique<MenuState>(m_state_stack, m_window));
    }

    Game::~Game() {
        while (!m_state_stack.empty())
            m_state_stack.pop_state();
    }

    void Game::input() {
        while (m_window->pollEvent(m_event)) {
            if (m_event.type == sf::Event::Closed) {
                m_window->close();
            }
        }

        if (!m_state_stack.empty())
            m_state_stack.top_state()->input();
    }

    void Game::update() {
        m_delta_time = m_dt_clock.restart().asSeconds();

        if (!m_state_stack.empty())
            m_state_stack.top_state()->update(m_delta_time);
    }

    void Game::render() {
        m_window->clear();

        if (!m_state_stack.empty())
            m_state_stack.top_state()->render();

        m_window->display();
    }

    void Game::run() {
        while (m_window->isOpen()) {
            input();
            update();
            render();
        }
    }
} // namespace aste
