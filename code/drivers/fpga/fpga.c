#include "fpga.h"
#include "spi/spi.h"

Result_t fpga_read_register(enum fpga_register register)
{
  Result_t result = { .err = ERR_NONE, .val.u32_val = 0 };
  result.err = ERR_NOT_IMPL;
  return result;
}

Result_t fpga_write_register(enum fpga_register register)
{
  Result_t result = { .err = ERR_NONE, .val.u32_val = 0 };
  result.err = ERR_NOT_IMPL;
  return result;
}

Result_t fpga_modify_register(enum fpga_register register, uint32_t mask)
{
  Result_t result = { .err = ERR_NONE, .val.u32_val = 0 };
  result.err = ERR_NOT_IMPL;
  return result;
}

Error_t fpga_read_buffer(enum fpga_register register, size_t length, uint8_t* const buffer)
{
  Error_t err = ERR_NONE;
  return err;
}

Error_t fpga_write_buffer(enum fpga_register register, size_t length, const uint8_t* const buffer)
{
  Error_t err = ERR_NONE;
  return err;
}
