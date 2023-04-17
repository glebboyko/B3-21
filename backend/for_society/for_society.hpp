#pragma once
#include <iostream>

namespace FS {

template <uint64_t, uint64_t>
uint64_t FromSysToSys(uint64_t);

// extract digit from integer by index
uint8_t GetDigit(uint8_t number, uint8_t index) noexcept;

}  // namespace FS