#pragma once

#include "includes.hpp"

namespace aste {
    class State;

    class StateStack {
    public:
        void push_state(std::shared_ptr<State> state);
        void pop_state();
        bool empty();
        State *top_state();

    private:
        std::stack<std::shared_ptr<State>> m_states;
    };

    class State {
    public:
        State(StateStack &stack, std::shared_ptr<sf::RenderWindow> window);
        virtual ~State() = default;

        virtual void input()                         = 0;
        virtual void update(const float &delta_time) = 0;
        virtual void render()                        = 0;

    protected:
        std::shared_ptr<sf::RenderWindow> m_window;
        std::shared_ptr<sf::Event> m_event;
        StateStack &m_stack;
    };
} // namespace aste
