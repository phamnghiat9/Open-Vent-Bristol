#pragma once

namespace misc {

template <bool X>
struct IntToType
{
  enum {value = X};
};

} // namespace
