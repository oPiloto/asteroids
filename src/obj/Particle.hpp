#pragma once

#include "Entity.hpp"

namespace aste {
    class Particle : public Entity {
    public:
        Particle(sf::Vector2f position, sf::Vector2f velocity, float angle, float acceleration, float life_time, sf::Color color);
        ~Particle() = default;

        void input(sf::RenderWindow &window){};
        void update(const float &delta_time);

        void set_scale(float scale);

        float get_life_time();
        float get_acceleration();
        float get_angle();
        sf::Vector2f get_position();
        sf::Vector2f get_velocity();
        sf::FloatRect get_global_bounds();
        void destroy();

    private:
        float m_life_time;
    };
} // namespace aste
