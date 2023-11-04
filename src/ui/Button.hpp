#pragma once

#include "Fonts.hpp"
#include "includes.hpp"

namespace aste {
    class Button : public sf::Drawable {
    public:
        enum ButtonState {
            NORMAL,
            HOVERED,
            PRESSED,
        };

    public:
        Button(sf::Vector2f position, sf::Vector2f dimentions, std::string text, unsigned int text_size);
        virtual ~Button() = default;

        void update(sf::RenderWindow &window);

        ButtonState state();
        void use_shadow(bool use);

        void button_colors(sf::Color normal, sf::Color hover, sf::Color active);
        void shadow_colors(sf::Color normal, sf::Color hover, sf::Color active);
        void text_colors(sf::Color normal, sf::Color hover, sf::Color active);

    private:
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    private:
        struct ButtonColors {
            sf::Color normal;
            sf::Color hover;
            sf::Color active;
        };

        ButtonState m_state;
        bool m_use_shadow;
        sf::Vector2f m_position;
        bool m_mouse_was_pressed;

        sf::RectangleShape m_rectangle;
        sf::RectangleShape m_shadow;
        sf::Text m_text;

        ButtonColors m_button_color;
        ButtonColors m_shadow_color;
        ButtonColors m_text_color;
    };
} // namespace aste
