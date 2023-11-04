#pragma once

#include "obj/ParticleSystem.hpp"

namespace aste {
    class Shoot : public ParticleSystem {
    public:
        Shoot(float shot_scale, sf::Color particle_color = sf::Color::Red);
        ~Shoot() = default;

        void input(sf::RenderWindow &window) override;

    private:
        bool m_mouse_pressed;
        bool m_mouse_was_pressed;
    };
} // namespace aste
