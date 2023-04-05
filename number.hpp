#pragma once
#include "for_society.hpp"

class Number {
 public:
  Number() = default;
  Number(uint8_t number, uint8_t mantissa, bool sign) noexcept;
  Number(const Number& other) noexcept;

  Number& operator=(const Number&) noexcept;

  std::string GetNumber() const noexcept;

  void SignButton() noexcept;
  void MantissaButton();
  void NumberButton(uint8_t);
  void ClearButton();

 private:
  uint8_t number_ = 0;
  uint8_t mantissa_ = UINT8_MAX;
  bool sign_ = false;

};