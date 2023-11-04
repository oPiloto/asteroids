#pragma once

#include "includes.hpp"

namespace aste {
    class Entity : public sf::Drawable, public sf::Transformable {
    public:
        Entity() = default;
        virtual ~Entity();

        virtual void input(sf::RenderWindow &window) = 0;
        virtual void update(const float &delta_time) = 0;
        void back_to_screen(sf::RenderWindow &window);

    protected:
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    protected:
        sf::ConvexShape m_shape;
        sf::Vector2f m_position;
        sf::Vector2f m_velocity;
        float m_acceleration;
        float m_angle;
    };
} // namespace aste
