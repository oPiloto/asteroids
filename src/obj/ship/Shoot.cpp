#include "Shoot.hpp"

namespace aste {
    Shoot::Shoot(float shot_scale, sf::Color particle_color) :
        ParticleSystem(shot_scale, particle_color), m_mouse_was_pressed(true) {}

    void Shoot::input(sf::RenderWindow &window) {
        m_mouse_pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

        if (m_mouse_pressed && !m_mouse_was_pressed)
            create_particle(2.f, 400.f);

        m_mouse_was_pressed = m_mouse_pressed;
    }
} // namespace aste
