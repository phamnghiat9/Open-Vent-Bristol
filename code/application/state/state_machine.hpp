#pragma once

#include <iostream>
#include <array>
#include "misc/type_tricks.hpp"
#include "state.hpp"
#include "transition.hpp"

namespace application { namespace state {

template <typename EventType, class StateType, size_t N_Transitions, bool EventIsPriorityBitField>
class StateMachine
{
public:
  StateMachine(
    StateType& starting_state, std::array<Transition<EventType, StateType>, N_Transitions>& transitions);

  void run(EventType event);

private:
  StateType* m_current_state;
  std::array<Transition<EventType, StateType>, N_Transitions>& m_transitions;

  StateType* check_transit(EventType event, ::misc::IntToType<false>);
  StateType* check_transit(EventType event, ::misc::IntToType<true>);

  StateMachine(StateMachine&) = delete;
};

template <typename EventType, class StateType, size_t N_Transitions, bool EventIsPriorityBitField>
StateMachine<EventType, StateType, N_Transitions, EventIsPriorityBitField>::
StateMachine(
  StateType& starting_state, std::array<Transition<EventType, StateType>, N_Transitions>& transitions) :
    m_current_state(&starting_state),
    m_transitions(transitions)
{
  m_current_state->on_entry();
}

template <typename EventType, class StateType, size_t N_Transitions, bool EventIsPriorityBitField>
void StateMachine<EventType, StateType, N_Transitions, EventIsPriorityBitField>::run(EventType event)
{
  StateType* transit_state = check_transit(event, ::misc::IntToType<EventIsPriorityBitField>());

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

// Implmentation of check_transit for enum/integer or non-priority bit field Event types
template <typename EventType, class StateType, size_t N_Transitions, bool EventIsPriorityBitField>
StateType* StateMachine<EventType, StateType, N_Transitions, EventIsPriorityBitField>::
  check_transit(EventType event, ::misc::IntToType<false>)
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

// Implmentation of check_transit for priority bit-field Event types
template <typename EventType, class StateType, size_t N_Transitions, bool EventIsPriorityBitField>
StateType* StateMachine<EventType, StateType, N_Transitions, EventIsPriorityBitField>::
  check_transit(EventType event, ::misc::IntToType<true>)
{
  if (static_cast<size_t>(event) != 0u)
  {
    // Prioritise events in low bit positions.  Handle precisely one event.  It is up to the caller or state entry to
    // clear other events if necessary.
    size_t bit_position = 1u;
    while (!(bit_position & event))
    {
      bit_position <<= 1u;
    }

    for (Transition<EventType, StateType>& transition : m_transitions)
    {
      if ((transition.event == bit_position) && (&(transition.start_state) == m_current_state))
      {
        return &(transition.result_state);
      }
    }
  }

  std::cout << "No transition\n";
  return m_current_state;
}

}} // namespace
