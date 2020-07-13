#include "StateMachine.hpp"
#include <array>
#include <iostream>

using namespace application::state;

enum class Event
{
  NONE,
  ENTER_0,
  ENTER_1,
  ENTER_2_FROM_0,
  ENTER_2_FROM_1
};

class State_0 : public State
{
  virtual void run()
  {
    std::cout << "State 0 run\n";
  }
  virtual void on_entry()
  {
    std::cout << "State 0 enter\n";
  }
  virtual void on_exit()
  {
    std::cout << "State 0 exit\n";
  }
};

class State_1 : public State
{
  virtual void run()
  {
    std::cout << "State 1 run\n";
  }
  virtual void on_entry()
  {
    std::cout << "State 1 enter\n";
  }
  virtual void on_exit()
  {
    std::cout << "State 1 exit\n";
  }
};

class State_2 : public State
{
  virtual void run()
  {
    std::cout << "State 2 run\n";
  }
  virtual void on_entry()
  {
    std::cout << "State 2 enter\n";
  }
  virtual void on_exit()
  {
    std::cout << "State 2 exit\n";
  }
};

State_0 state_0;
State_1 state_1;
State_2 state_2;

using TopStateTransition = Transition<Event, State>;
std::array<TopStateTransition, 5u> state_transitions =
{
  TopStateTransition{Event::ENTER_0, state_2, state_0},
  TopStateTransition{Event::ENTER_0, state_1, state_0},
  TopStateTransition{Event::ENTER_1, state_0, state_1},
  TopStateTransition{Event::ENTER_2_FROM_0, state_0, state_2},
  TopStateTransition{Event::ENTER_2_FROM_1, state_1, state_2}
};

using TopStateMachineType = StateMachine<Event, State, state_transitions.max_size()>;
TopStateMachineType top_state_machine(state_0, state_transitions);

int main()
{
  std::cout << "1\n";
  top_state_machine.run(Event::NONE);
  std::cout << "2\n";
  top_state_machine.run(Event::ENTER_0);
  std::cout << "3\n";
  top_state_machine.run(Event::ENTER_1);        // state_1
  std::cout << "4\n";
  top_state_machine.run(Event::ENTER_2_FROM_1); // state_2
  std::cout << "5\n";
  top_state_machine.run(Event::ENTER_1);
  std::cout << "6\n";
  top_state_machine.run(Event::ENTER_0);        // state_0
  std::cout << "7\n";
  top_state_machine.run(Event::ENTER_2_FROM_1);
  std::cout << "8\n";
  top_state_machine.run(Event::ENTER_2_FROM_0); // state_2

  return 0;
}
