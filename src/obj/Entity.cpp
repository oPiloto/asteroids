#include "Entity.hpp"

namespace aste {
    Entity::~Entity() { m_shape.setPointCount(0); }

    void Entity::back_to_screen(sf::RenderWindow &window) {
        if (m_position.x > window.getSize().x)
            m_position.x = 0.f;
        else if (m_position.x < 0.f)
            m_position.x = window.getSize().x;
        else if (m_position.y > window.getSize().y)
            m_position.y = 0.f;
        else if (m_position.y < 0.f)
            m_position.y = window.getSize().y;
    }

    void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        target.draw(m_shape, states);
    }
} // namespace aste
