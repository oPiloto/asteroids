#include "ParticleSystem.hpp"

namespace aste {
    ParticleSystem::ParticleSystem(float particle_scale, sf::Color particle_color) :
        m_scale(particle_scale), m_color(particle_color) {
        // Rand seed
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
    }

    ParticleSystem::~ParticleSystem() { m_particles.clear(); }

    void ParticleSystem::update(const float &delta_time) {
        for (auto particle = m_particles.begin(); particle != m_particles.end();) {
            particle->update(delta_time);

            if (particle->get_life_time() <= 0.f)
                particle = m_particles.erase(particle);
            else
                ++particle;
        }
    }

    void ParticleSystem::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        states.transform *= getTransform();
        states.texture = NULL;
        for (const auto particle : m_particles)
            target.draw(particle, states);
    }

    void ParticleSystem::set_position(sf::Vector2f position) {
        m_position = position;
    }

    void ParticleSystem::set_angle(float angle) { m_angle = angle; }

    void ParticleSystem::set_velocity(sf::Vector2f velocity) {
        m_velocity = velocity;
    }

    void ParticleSystem::set_scale(float scale) { m_scale = scale; }

    sf::Vector2f ParticleSystem::get_position() { return m_position; }

    std::vector<Particle> &ParticleSystem::get_particles() {
        return m_particles;
    }

    void ParticleSystem::create_particle(float life_time, float acceleration) {
        Particle particle(m_position, m_velocity, m_angle, acceleration, life_time, m_color);
        particle.set_scale(m_scale);
        m_particles.push_back(particle);
    }

    void ParticleSystem::create_particles(float life_time, float angle_range, bool static_life_time) {
        float angle = m_angle - (angle_range * M_PI / 180.f / 2.f) + (std::rand() % static_cast<int>(angle_range)) * M_PI / 180.f;
        float acceleration = (std::rand() % 50) + 150.f;
        float f_life_time;
        if (static_life_time)
            f_life_time = life_time;
        else
            f_life_time = 0.1 + (static_cast<float>(std::rand() % 100) / 100) * (life_time - 0.1f);

        Particle particle(m_position, m_velocity, angle, acceleration, f_life_time, m_color);
        particle.set_scale(m_scale);
        m_particles.push_back(particle);
    }

    void ParticleSystem::create_particles(float life_time, float angle_range, float acceleration, bool static_life_time) {
        float angle = m_angle - (angle_range * M_PI / 180.f / 2.f) + (std::rand() % static_cast<int>(angle_range)) * M_PI / 180.f;
        float f_life_time;
        if (static_life_time)
            f_life_time = life_time;
        else
            f_life_time = 0.1 + (static_cast<float>(std::rand() % 100) / 100) * (life_time - 0.1f);

        Particle particle(m_position, m_velocity, angle, acceleration, f_life_time, m_color);
        particle.set_scale(m_scale);
        m_particles.push_back(particle);
    }
} // namespace aste
