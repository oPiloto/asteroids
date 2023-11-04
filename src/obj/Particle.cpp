#include "Particle.hpp"

namespace aste {
    Particle::Particle(sf::Vector2f position, sf::Vector2f velocity, float angle, float acceleration, float life_time, sf::Color color) {
        // Particle shape
        m_shape.setFillColor(color);
        m_shape.setPointCount(6);
        for (int i = 0; i < 6; i++) {
            float x = 10.0f * std::cos(i * 2.f * M_PI / 6.f);
            float y = 10.0f * std::sin(i * 2.f * M_PI / 6.f);
            m_shape.setPoint(i, sf::Vector2f(x, y));
        }
        m_shape.setPosition(position);

        m_position  = position;
        m_life_time = life_time;
        m_angle     = angle;
        m_velocity = velocity + sf::Vector2f(std::cos(angle), std::sin(angle)) * acceleration;
    }

    void Particle::update(const float &delta_time) {
        m_position += m_velocity * delta_time;
        m_shape.setPosition(m_position);
        m_life_time -= delta_time;
    }

    void Particle::set_scale(float scale) { m_shape.setScale(scale, scale); }

    float Particle::get_life_time() { return m_life_time; }

    float Particle::get_acceleration() { return m_acceleration; }

    float Particle::get_angle() { return m_angle; }

    sf::Vector2f Particle::get_position() { return m_position; }

    sf::Vector2f Particle::get_velocity() { return m_velocity; }

    sf::FloatRect Particle::get_global_bounds() {
        return m_shape.getGlobalBounds();
    }

    void Particle::destroy() { m_life_time = 0.f; }
} // namespace aste
