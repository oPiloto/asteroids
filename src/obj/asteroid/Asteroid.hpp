#pragma once

#include "obj/ParticleSystem.hpp"

namespace aste {
    class Asteroid : public Entity {
    public:
        Asteroid(float asteroid_scale, sf::Color asteroid_color = sf::Color::White);
        ~Asteroid() = default;

        void input(sf::RenderWindow &window);
        void update(const float &delta_time);

    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    public:
        void check_collision(std::vector<Particle> &shoots);

        void create_asteroids(const float &delta_time);
        bool destroyed();

        std::vector<sf::FloatRect> get_asteroids_bounds();

    private:
        void create_small_asteroids(Particle particle);
        void explosion(Particle particle);

    private:
        std::shared_ptr<ParticleSystem> m_asteroid;
        std::shared_ptr<ParticleSystem> m_small_asteroid;
        std::shared_ptr<ParticleSystem> m_explosion;

        sf::Vector2f m_window_size;
        bool m_destroyed;
        float m_time;
        bool m_collided_with_shoot;
    };
} // namespace aste
