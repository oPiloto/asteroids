#include "Asteroid.hpp"

namespace aste {
    Asteroid::Asteroid(float asteroid_scale, sf::Color asteroid_color) :
        m_time(0.f), m_destroyed(false) {
        m_asteroid = new ParticleSystem(asteroid_scale, asteroid_color);
        m_small_asteroid = new ParticleSystem(asteroid_scale - asteroid_scale / 3, asteroid_color);
        m_explosion = new ParticleSystem(0.1f, asteroid_color);
    }

    Asteroid::~Asteroid() {
        delete m_asteroid;
        delete m_small_asteroid;
        delete m_explosion;
    }

    void Asteroid::input(sf::RenderWindow &window) {
        m_window_size = static_cast<sf::Vector2f>(window.getSize());

        // Destroy asteroids off screen
        for (auto &asteroid : m_asteroid->get_particles())
            if (asteroid.get_position().x < -100.f ||
                asteroid.get_position().y > m_window_size.y + 100.f)
                asteroid.destroy();

        for (auto &asteroid : m_small_asteroid->get_particles())
            if (asteroid.get_position().x < -100.f ||
                asteroid.get_position().y > m_window_size.y + 100.f)
                asteroid.destroy();
    }

    void Asteroid::update(const float &delta_time) {
        m_asteroid->update(delta_time);
        m_small_asteroid->update(delta_time);
        m_explosion->update(delta_time);
    }

    void Asteroid::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        target.draw(*m_asteroid, states);
        target.draw(*m_small_asteroid, states);
        target.draw(*m_explosion, states);
    }

    void Asteroid::check_collision(std::vector<Particle> &shoots) {
        m_destroyed = false;
        for (auto &shoot : shoots) {
            for (auto &asteroid : m_asteroid->get_particles()) {
                if (shoot.get_global_bounds().intersects(asteroid.get_global_bounds())) {
                    m_destroyed = true;
                    shoot.destroy();
                    asteroid.destroy();

                    // Explosion
                    explosion(shoot);

                    // Create new smaller asteroid
                    create_small_asteroids(asteroid);
                }
            }

            for (auto &asteroid : m_small_asteroid->get_particles()) {
                if (shoot.get_global_bounds().intersects(asteroid.get_global_bounds())) {
                    m_destroyed = true;
                    shoot.destroy();
                    asteroid.destroy();

                    // Explosion
                    explosion(shoot);
                }
            }
        }
    }

    void Asteroid::create_asteroids(const float &delta_time) {
        m_time += delta_time;

        if (m_time > 0.3f) {
            m_time = 0.f;

            switch (std::rand() % 4) {
            case 0:
                // Top -> Bottom
                m_asteroid->set_position(
                    sf::Vector2f(std::rand() % static_cast<int>(m_window_size.x), -100.f));
                m_asteroid->set_angle(M_PI / 2);
                break;

            case 1:
                // Right -> Left
                m_asteroid->set_position(sf::Vector2f(m_window_size.x,
                    std::rand() % static_cast<int>(m_window_size.y)));
                m_asteroid->set_angle(M_PI);
                break;

            case 2:
                // Top -> Left
                m_asteroid->set_position(
                    sf::Vector2f(std::rand() % static_cast<int>(m_window_size.x), -100.f));
                m_asteroid->set_angle(3 * M_PI / 4);
                break;

            case 3:
                // Right -> Bottom
                m_asteroid->set_position(sf::Vector2f(m_window_size.x + 100.f,
                    std::rand() % static_cast<int>(m_window_size.y)));
                m_asteroid->set_angle(3 * M_PI / 4);
                break;
            }

            m_asteroid->create_particles(60.f, 25.f, 30.f + std::rand() % 50, true);
        }
    }

    bool Asteroid::destroyed() { return m_destroyed; }

    std::vector<sf::FloatRect> Asteroid::get_asteroids_bounds() {
        std::vector<sf::FloatRect> bounds;

        for (auto asteroid : m_asteroid->get_particles())
            bounds.push_back(asteroid.get_global_bounds());

        for (auto asteroid : m_small_asteroid->get_particles())
            bounds.push_back(asteroid.get_global_bounds());

        return bounds;
    }

    void Asteroid::create_small_asteroids(Particle &particle) {
        m_small_asteroid->set_position(particle.get_position());
        m_small_asteroid->set_velocity(particle.get_velocity());
        m_small_asteroid->set_angle(particle.get_angle());
        for (std::size_t i = 0; i < 1 + std::rand() % 3; i++)
            m_small_asteroid->create_particles(60.f, 50.f, particle.get_acceleration(), true);
    }

    void Asteroid::explosion(Particle &particle) {
        m_explosion->set_position(particle.get_position());
        m_explosion->set_velocity(-particle.get_velocity());
        m_explosion->set_angle(particle.get_angle());
        for (std::size_t i = 0; i < 10 + std::rand() % 20; i++)
            m_explosion->create_particles(0.2f, 40.f);
    }
} // namespace aste
