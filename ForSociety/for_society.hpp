#pragma once
#include <iostream>

namespace FS {

// to convert from decimal to hexadecimal and vice versa
uint8_t ToHexadecimal(uint8_t);
uint8_t ToDecimal(uint8_t);

uint8_t GetDigit(uint8_t number, uint8_t index) noexcept;

}  // namespace for_society