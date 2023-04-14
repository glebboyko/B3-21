#include "for_society.hpp"

uint8_t GetDigit(uint8_t number, uint8_t index) noexcept {
  for (uint8_t i = 0; i < index; ++i) {
    number /= 10;
  }
  return number % 10;
}