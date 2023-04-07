#pragma once
#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "backup.hpp"
#include "calc_exec.hpp"
#include "memory.hpp"
#include "number.hpp"

namespace for_society {

// to convert from decimal to hexadecimal and vice versa
uint8_t ToHexadecimal(uint8_t);
uint8_t ToDecimal(uint8_t);

}  // namespace for_society