#include "Button.hpp"

namespace aste {
    Button::Button(sf::Vector2f position, sf::Vector2f dimentions, std::string text, unsigned int text_size) {
        m_mouse_was_pressed = false;
        m_use_shadow        = true;
        m_position          = position;
        m_state             = ButtonState::NORMAL;

        m_rectangle.setPosition(position);
        m_rectangle.setSize(dimentions);

        m_shadow.setPosition({position.x + 5.f, position.y + 5.f});
        m_shadow.setSize(dimentions);

        m_text.setString(text);
        m_text.setCharacterSize(text_size);
        m_text.setPosition({position.x + 30.f, position.y + (dimentions.y / 2) - (text_size / 2)});
        m_text.setFont(Fonts::MartianMono());

        // Colors
        button_colors(sf::Color::White, sf::Color(130, 130, 130), sf::Color(100, 100, 100));
        shadow_colors(sf::Color(70, 70, 70), sf::Color(50, 50, 50), sf::Color(30, 30, 30));
        text_colors(sf::Color::Black, sf::Color::Black, sf::Color(30, 30, 30));
    }

    void Button::update(sf::RenderWindow &window) {
        // window.mapPixelToCoords if you want to resize the window
        sf::Vector2f mouse_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        bool mouse_pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

        if (m_rectangle.getGlobalBounds().contains(mouse_pos)) {
            m_state = ButtonState::HOVERED;

            if (mouse_pressed && !m_mouse_was_pressed)
                m_state = ButtonState::PRESSED;
        } else
            m_state = ButtonState::NORMAL;

        m_mouse_was_pressed = mouse_pressed;

        switch (m_state) {
        case ButtonState::NORMAL:
            m_rectangle.setFillColor(m_button_color.normal);
            m_shadow.setFillColor(m_shadow_color.normal);
            m_text.setFillColor(m_text_color.normal);
            break;

        case ButtonState::HOVERED:
            m_rectangle.setFillColor(m_button_color.hover);
            m_shadow.setFillColor(m_shadow_color.hover);
            m_text.setFillColor(m_text_color.hover);
            break;

        case ButtonState::PRESSED:
            m_rectangle.setFillColor(m_button_color.active);
            m_shadow.setFillColor(m_shadow_color.active);
            m_text.setFillColor(m_text_color.active);
            break;
        }
    }

    void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        if (m_use_shadow)
            target.draw(m_shadow, states);
        target.draw(m_rectangle, states);
        target.draw(m_text, states);
    }

    Button::ButtonState Button::state() { return m_state; }

    void Button::use_shadow(bool use) { m_use_shadow = use; }

    void Button::button_colors(sf::Color normal, sf::Color hover, sf::Color active) {
        m_button_color.normal = normal;
        m_button_color.hover  = hover;
        m_button_color.active = active;
    }

    void Button::shadow_colors(sf::Color normal, sf::Color hover, sf::Color active) {
        m_shadow_color.normal = normal;
        m_shadow_color.hover  = hover;
        m_shadow_color.active = active;
    }

    void Button::text_colors(sf::Color normal, sf::Color hover, sf::Color active) {
        m_text_color.normal = normal;
        m_text_color.hover  = hover;
        m_text_color.active = active;
    }
} // namespace aste
