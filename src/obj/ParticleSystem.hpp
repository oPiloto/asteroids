#pragma once

#include "Particle.hpp"

namespace aste {
    class ParticleSystem : public Entity {
    public:
        ParticleSystem(float particle_scale, sf::Color particle_color);
        virtual ~ParticleSystem();

        virtual void input(sf::RenderWindow &window){};
        void update(const float &delta_time);

    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    public:
        void set_position(sf::Vector2f position);
        void set_angle(float angle);
        /** Velocity to add to the particle.
            The ship or asteroids are moving at speed,
            so the particles have to follow them
        **/
        void set_velocity(sf::Vector2f velocity);
        void set_scale(float scale);

        sf::Vector2f get_position();
        std::vector<Particle> &get_particles();

        virtual void create_particle(float life_time, float acceleration);
        virtual void create_particles(float life_time, float angle_range, bool static_life_time = false);
        virtual void create_particles(float life_time, float angle_range, float acceleration, bool static_life_time = false);

    protected:
        std::vector<Particle> m_particles;
        float m_scale;
        sf::Color m_color;
    };
} // namespace aste
