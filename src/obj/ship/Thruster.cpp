#include "Thruster.hpp"

namespace aste {
    Thruster::Thruster(float particle_scale, sf::Color particle_color) :
        ParticleSystem(particle_scale, particle_color), m_time(0.f), m_power(false) {}

    void Thruster::input(sf::RenderWindow &window) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            m_power = true;
        else
            m_power = false;
    }

    void Thruster::update(const float &delta_time) {
        for (auto particle = m_particles.begin(); particle != m_particles.end();) {
            particle->update(delta_time);

            if (particle->get_life_time() <= 0.f)
                particle = m_particles.erase(particle);
            else
                ++particle;
        }

        m_time += delta_time;
        if (m_power && m_time > 0.01f) {
            m_time = 0.f;
            create_particles(0.3f, 30.f);
        }
    }
} // namespace aste
