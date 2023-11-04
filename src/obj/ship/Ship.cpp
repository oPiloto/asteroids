#include "Ship.hpp"

namespace aste {
    Ship::Ship() {
        // Ship
        m_shape.setPointCount(6);
        m_shape.setScale(0.25, 0.25);
        m_shape.setPoint(0, sf::Vector2f(0, -60));
        m_shape.setPoint(1, sf::Vector2f(40, 60));
        m_shape.setPoint(2, sf::Vector2f(10, 40));
        m_shape.setPoint(3, sf::Vector2f(0, 40));
        m_shape.setPoint(4, sf::Vector2f(-10, 40));
        m_shape.setPoint(5, sf::Vector2f(-40, 60));

        m_velocity     = {0.f, 0.f};
        m_acceleration = 700.f;

        m_thruster = std::make_unique<Thruster>(0.15f);
        m_shoot    = std::make_unique<Shoot>(0.2f);
    }

    void Ship::input(sf::RenderWindow &window) {
        m_mouse_pos = sf::Mouse::getPosition(window);
        follow_mouse(window);
        m_thruster->input(window);
        m_shoot->input(window);
    }

    void Ship::update(const float &delta_time) {
        // Boost
        m_angle = (m_shape.getRotation() - 90.f) * M_PI / 180.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            sf::Vector2f direction(std::cos(m_angle), std::sin(m_angle));

            m_velocity += direction * (m_acceleration * delta_time);
        }

        // m_velocity *= 1.f - 1.f * delta_time; // Deceleration
        m_position += m_velocity * delta_time;
        m_shape.setPosition(m_position);

        // Thruster
        m_thruster->set_position(m_shape.getTransform().transformPoint(m_shape.getPoint(3)));
        m_thruster->set_angle(m_angle + M_PI);
        m_thruster->set_velocity(m_velocity);
        m_thruster->update(delta_time);

        // Shoot
        m_shoot->set_position(m_shape.getTransform().transformPoint(m_shape.getPoint(0)));
        m_shoot->set_angle(m_angle);
        m_shoot->set_velocity(m_velocity);
        m_shoot->update(delta_time);
    }

    void Ship::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        target.draw(m_shape, states);
        target.draw(*m_thruster, states);
        target.draw(*m_shoot, states);
    }

    sf::Vector2f Ship::size() {
        return sf::Vector2f(m_shape.getScale().x * m_shape.getPoint(1).x,
            m_shape.getScale().y * m_shape.getPoint(1).y);
    }

    void Ship::set_position(sf::Vector2f position) { m_position = position; }

    sf::Vector2f Ship::get_position() { return m_position; }

    sf::FloatRect Ship::get_bounds() { return m_shape.getGlobalBounds(); }

    std::vector<Particle> &Ship::shoots() { return m_shoot->get_particles(); }

    void Ship::follow_mouse(sf::RenderWindow &window) {
        sf::Vector2f deltas = {static_cast<sf::Vector2f>(m_mouse_pos) - m_shape.getPosition()};
        float deg = std::atan2(deltas.y, deltas.x) * (180.f / M_PI);

        m_shape.setRotation(deg + 90.f);
    }
} // namespace aste
