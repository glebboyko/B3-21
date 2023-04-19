#pragma once
#include <iostream>

namespace FS {

template <uint64_t from_not, uint64_t to_not>
uint64_t FromNotToNot(uint64_t) noexcept;

// extract digit from integer by index
uint8_t GetDigit(uint8_t number, uint8_t index) noexcept;

}  // namespace FS