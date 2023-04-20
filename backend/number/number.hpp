#pragma once
#include <iostream>
#include <string>

namespace CN {

const int kNumOfDigits = 8;
const int kNumOfCharacteristic = 2;

enum EnterMode { Mantissa, Characteristic, AfterDot };

class Number {
 public:
  Number() = default;
  Number(const Number& other) = default;
  Number(int);

  Number& operator=(const Number&) = default;

  // для визуализации (характеристика и мантисса)
  std::tuple<bool, int, std::string> GetNumber() const noexcept;

  // интерфейс взаимодействия
  void SignButton() noexcept;
  void DotButton() noexcept;
  void CharacteristicButton();
  void NumberButton(char);
  void ClearButton() noexcept;
  void ExitEnterMode() noexcept;

  // операторы сравнения
  bool operator<(const Number&) const;
  bool operator<=(const Number&) const;
  bool operator>(const Number&) const;
  bool operator>=(const Number&) const;
  bool operator==(const Number&) const;
  bool operator!=(const Number&) const;

  // арифметические операции
  Number operator+(const Number&) const;
  Number operator-(const Number&) const;
  Number operator*(const Number&) const;
  Number operator/(const Number&) const;

  // for backup / restore
  struct BackUpIng {
    bool sign;
    uint64_t number;
    int characteristic;
    EnterMode mode;
  };

  Number(bool sign, uint64_t number, int characteristic,
         EnterMode mode) noexcept;
  BackUpIng GetClass() const noexcept;

 private:
  bool sign_;
  uint64_t number_ = 0;
  int characteristic_ = 0;
  EnterMode mode_ = Mantissa;

  template <typename T>
  static void AddDigit(T&, char) noexcept;

  std::tuple<bool, int, std::string> FullView() const noexcept;
  std::tuple<bool, int, std::string> PartView() const noexcept;

  static bool IsThereDot(const std::string&) noexcept;
};

}  // namespace CN