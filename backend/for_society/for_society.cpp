#include "for_society.hpp"

namespace FS {

uint32_t GetDigit(uint32_t number, uint32_t index) noexcept {
  for (uint32_t i = 0; i < index; ++i) {
    number /= 10;
  }
  return number % 10;
}

template <uint64_t from_not, uint64_t to_not>
uint64_t FromNotToNot(uint64_t number) noexcept {
  uint64_t result = 0;

  for (uint64_t multiply = 1; number != 0; number /= 10, multiply *= from_not) {
    result += multiply * (number % 10);
  }

  number = 1;
  for (; result != 0; result /= to_not) {
    number *= 10;
    number += result % to_not;
  }
  for (; number != 1; number /= 10) {
    result *= 10;
    result += number % 10;
  }

  return result;
}

}