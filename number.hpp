#pragma once
#include "for_society.hpp"

namespace number {

template <typename A, typename B, typename C>
struct Trio {
  A first;
  B second;
  C third;
};

class Number {
 public:
  Number() noexcept;
  Number(const Number& other) noexcept;
  Number& operator=(const Number&) noexcept;

  std::string GetNumber() const;

  void SignButton() noexcept;
  void MantissaButton();  // не уверен, может ли мантисса выдать ошибку
  void NumberButton(uint8_t);
  void ClearButton() noexcept;

  // for backup / restore
  Number(uint8_t characteristic, uint8_t mantissa, bool sign) noexcept;
  Trio<uint8_t, uint8_t, bool> GetClass() const noexcept;

 private:
};

}  // namespace number