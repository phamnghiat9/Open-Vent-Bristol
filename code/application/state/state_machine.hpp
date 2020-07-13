#pragma once

#include <iostream>
#include <array>
#include "state.hpp"
#include "transition.hpp"

namespace application { namespace state {

template <typename EventType, class StateType, size_t N_Transitions>
class StateMachine
{
public:
  StateMachine(
    StateType& starting_state, std::array<Transition<EventType, StateType>, N_Transitions>& transitions);

  void run(EventType event);

private:
  StateType* m_current_state;
  std::array<Transition<EventType, StateType>, N_Transitions>& m_transitions;

  StateType* check_transit(EventType event);

  StateMachine(StateMachine&) = delete;
};

template <typename EventType, class StateType, size_t N_Transitions>
StateMachine<EventType, StateType, N_Transitions>::
StateMachine(
  StateType& starting_state, std::array<Transition<EventType, StateType>, N_Transitions>& transitions) :
    m_current_state(&starting_state),
    m_transitions(transitions)
{
  m_current_state->on_entry();
}

template <typename EventType, class StateType, size_t N_Transitions>
void StateMachine<EventType, StateType, N_Transitions>::run(EventType event)
{
  StateType* transit_state = check_transit(event);

  if (transit_state != m_current_state)
  {
    m_current_state->on_exit();
    m_current_state = transit_state;
    m_current_state->on_entry();
  }
  else
  {
    m_current_state->run();
  }
}

template <typename EventType, class StateType, size_t N_Transitions>
StateType* StateMachine<EventType, StateType, N_Transitions>::check_transit(EventType event)
{
  if (static_cast<size_t>(event) != 0u)
  {
    for (Transition<EventType, StateType>& transition : m_transitions)
    {
      if ((transition.event == event) && (&(transition.start_state) == m_current_state))
      {
        return &(transition.result_state);
      }
    }
  }

  std::cout << "No transition\n";
  return m_current_state;
}

}} // namespace
