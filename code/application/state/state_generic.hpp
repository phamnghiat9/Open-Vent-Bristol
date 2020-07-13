#pragma once

namespace application { namespace state {

class State
{
public:
  virtual void run() = 0;
  virtual void on_entry() = 0;
  virtual void on_exit() = 0;
};

}} // namespace
