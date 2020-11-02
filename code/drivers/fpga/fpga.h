#ifndef FPGA_H
#define FPGA_H

#include "fpga_register.h"
#include "misc/result.h"
#include <stdint.h>
#include <stddef.h>

/**
 * Read a register from the FPGA
 *
 * @param register    See enum fpga_register
 * @return Result_t
 */
Result_t fpga_read_register(enum fpga_register register);

/**
 * Write a register in the FPGA
 *
 * @param register    See enum fpga_register
 * @return Result_t
 */
Result_t fpga_write_register(enum fpga_register register);

/**
 * Write a register in the FPGA, with or without a mask
 *
 * @param register    See enum fpga_register
 * @param mask        Mask applied to write (lsb first)
 *                    Use UINT32_MAX to apply to all bits
 * @return Result_t
 */
Result_t fpga_modify_register(enum fpga_register register, uint32_t mask);

/**
 * Read a register from the FPGA into a buffer
 *
 * @param register    See enum fpga_register
 * @param length      Number of bytes to read, normally sizeof(buffer)
 * @param buffer      Destination buffer for read
 * @return Result_t
 */
Error_t fpga_read_buffer(enum fpga_register register, size_t length, uint8_t* const buffer);

/**
 * Write a register in the FPGA from a buffer
 *
 * @param register    See enum fpga_register
 * @param length      Number of bytes to write, normally sizeof(buffer)
 * @param buffer      Source buffer for write
 * @return Result_t
 */
Error_t fpga_write_buffer(enum fpga_register register, size_t length, const uint8_t* const buffer);

#endif /* FPGA_H */
