#pragma once

namespace application { namespace state {

template <typename EventType, class StateType>
struct Transition
{
  const EventType event;
  StateType& start_state;
  StateType& result_state;

  constexpr Transition(EventType param_event, StateType& param_start_state, StateType& param_result_state) :
    event(param_event),
    start_state(param_start_state),
    result_state(param_result_state)
  {}
};

}} // namespace
