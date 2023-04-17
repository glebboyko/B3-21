#include "for_society.hpp"

uint8_t GetDigit(uint8_t number, uint8_t index) noexcept {
  for (uint8_t i = 0; i < index; ++i) {
    number /= 10;
  }
  return number % 10;
}

template <uint64_t from_sys, uint64_t to_sys>
uint64_t FromSysToSys(uint64_t number) {
  uint64_t result = 0;

  for (uint64_t multiply = 1; number != 0; number /= 10, multiply *= from_sys) {
    result += multiply * (number % 10);
  }

  number = 1;
  for (; result != 0; result /= to_sys) {
    number *= 10;
    number += result % to_sys;
  }
  for (; number != 1; number /= 10) {
    result *= 10;
    result += number % 10;
  }

  return result;
}