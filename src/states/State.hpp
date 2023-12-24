#pragma once

#include "includes.hpp"

namespace aste {
    class StateStack;

    class State {
    public:
        State(StateStack &stack, sf::RenderWindow &window);
        virtual ~State() = default;

        virtual void input()                         = 0;
        virtual void update(const float &delta_time) = 0;
        virtual void render()                        = 0;

    protected:
        sf::RenderWindow &m_window;
        StateStack &m_stack;
    };

    class StateStack {
    public:
        ~StateStack();

        void push_state(State *state);
        void pop_state();
        bool empty();
        State *top_state();

    private:
        std::stack<State *> m_states;
    };
} // namespace aste
