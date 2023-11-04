#pragma once

#include "obj/ParticleSystem.hpp"

namespace aste {
    class Thruster : public ParticleSystem {
    public:
        Thruster(float particle_scale, sf::Color particle_color = sf::Color::White);
        ~Thruster() = default;

        void input(sf::RenderWindow &window) override;
        void update(const float &delta_time) override;

    private:
        bool m_power;
        float m_time;
    };
} // namespace aste
