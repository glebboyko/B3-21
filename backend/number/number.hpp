#pragma once
#include <iostream>
#include <string>

namespace CN {

template <typename A, typename B, typename C>
struct Trio {
  A first;
  B second;
  C third;
};

const int kNumOfDigits = 8;

class Number {
 public:
  Number() noexcept;
  Number(const Number& other) noexcept;
  Number& operator=(const Number&) noexcept;

  operator int() const noexcept;

  std::string GetNumber() const;

  void SignButton() noexcept;
  void CharacteristicButton();  // не уверен, может ли мантисса выдать ошибку
  void NumberButton(uint8_t);
  void ClearButton() noexcept;

  // for backup / restore
  Number(uint8_t characteristic, uint8_t mantissa, bool sign) noexcept;
  Trio<uint8_t, uint8_t, bool> GetClass() const noexcept;

  friend bool operator<(const Number&, const Number&);
  friend bool operator<=(const Number&, const Number&);
  friend bool operator>(const Number&, const Number&);
  friend bool operator>=(const Number&, const Number&);
  friend bool operator==(const Number&, const Number&);
  friend bool operator!=(const Number&, const Number&);

  friend Number operator+(const Number&, const Number&);
  friend Number operator-(const Number&, const Number&);
  friend Number operator*(const Number&, const Number&);
  friend Number operator/(const Number&, const Number&);

 private:
  uint8_t number_ = 0;
  uint8_t mantissa_ = UINT8_MAX;
  bool sign_ = false;
};

bool operator<(const Number&, const Number&);
bool operator<=(const Number&, const Number&);
bool operator>(const Number&, const Number&);
bool operator>=(const Number&, const Number&);
bool operator==(const Number&, const Number&);
bool operator!=(const Number&, const Number&);

Number operator+(const Number&, const Number&);
Number operator-(const Number&, const Number&);
Number operator*(const Number&, const Number&);
Number operator/(const Number&, const Number&);

}  // namespace CN