#include "State.hpp"

namespace aste {
    void StateStack::push_state(std::shared_ptr<State> state) {
        m_states.push(state);
    }

    void StateStack::pop_state() {
        if (!m_states.empty())
            m_states.pop();
    }

    bool StateStack::empty() { return m_states.empty(); }

    State *StateStack::top_state() {
        return m_states.empty() ? nullptr : m_states.top().get();
    }

    State::State(StateStack &stack, std::shared_ptr<sf::RenderWindow> window) :
        m_stack(stack), m_window(window) {}
} // namespace aste
