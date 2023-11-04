#pragma once

#include "Shoot.hpp"
#include "Thruster.hpp"
#include "obj/Entity.hpp"

namespace aste {
    class Ship : public Entity {
    public:
        Ship();
        ~Ship() = default;

        void input(sf::RenderWindow &window);
        void update(const float &delta_time);

    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    public:
        sf::Vector2f size();
        void set_position(sf::Vector2f position);
        sf::Vector2f get_position();
        sf::FloatRect get_bounds();

        std::vector<Particle> &shoots();

    private:
        void follow_mouse(sf::RenderWindow &window);

    private:
        sf::Vector2i m_mouse_pos;
        std::unique_ptr<Thruster> m_thruster;
        std::unique_ptr<Shoot> m_shoot;
    };
} // namespace aste