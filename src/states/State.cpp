#include "State.hpp"

namespace aste {
    State::State(StateStack &stack, sf::RenderWindow &window) :
        m_stack(stack), m_window(window) {}

    StateStack::~StateStack() {
        while (!m_states.empty()) {
            delete m_states.top();
            m_states.pop();
        }
    }

    void StateStack::push_state(State *state) { m_states.push(state); }

    void StateStack::pop_state() {
        if (!m_states.empty()) {
            delete m_states.top();
            m_states.pop();
        }
    }

    bool StateStack::empty() { return m_states.empty(); }

    State *StateStack::top_state() {
        return m_states.empty() ? nullptr : m_states.top();
    }
} // namespace aste
