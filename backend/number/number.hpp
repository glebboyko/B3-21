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
  Number(const Number&) noexcept;
  Number(Number&&) noexcept;
  Number(int) noexcept;
  Number(float) noexcept;

  Number& operator=(const Number&) noexcept;
  Number& operator=(Number&&) noexcept;

  // для визуализации (знак, характеристика и мантисса)
  std::tuple<bool, int, std::string> GetNumber() const noexcept;

  // интерфейс взаимодействия
  void SignButton() noexcept;
  void DotButton() noexcept;
  void CharacteristicButton() noexcept;
  void NumberButton(char) noexcept;
  void ClearButton() noexcept;

  // операторы сравнения
  bool operator<(Number) const noexcept;
  bool operator<=(Number) const noexcept;
  bool operator>(Number) const noexcept;
  bool operator>=(Number) const noexcept;
  bool operator==(Number) const noexcept;
  bool operator!=(Number) const noexcept;

  // арифметические операции
  Number operator-() const noexcept;
  Number operator+(const Number&) const;
  Number operator-(const Number&) const;
  Number operator*(const Number&) const;
  Number operator/(const Number&) const;

  Number& operator+=(const Number&);
  Number& operator-=(const Number&);
  Number& operator*=(Number);
  Number& operator/=(Number);

  // for backup / restore
  struct BackUpIng {
    bool sign;
    uint64_t number;
    int characteristic;
    int new_characteristic;
    EnterMode mode;
  };

  Number(bool sign, uint64_t number, int characteristic, int new_characteristic,
         EnterMode mode) noexcept;
  BackUpIng GetClass() const noexcept;

 private:
  bool sign_ = false;
  uint64_t number_ = 0;
  int characteristic_ = 0;
  int new_characteristic_ = 0;
  EnterMode mode_ = Mantissa;

 public:
  void ExitEnterMode() noexcept;

 private:
  void RepairNumber() noexcept;

  template <typename T>
  static void AddDigit(T&, char) noexcept;

  std::tuple<bool, int, std::string> FullView() const noexcept;
  std::tuple<bool, int, std::string> PartView() const noexcept;

  static Number Abs(Number) noexcept;
  static void ToEqualDigits(Number& abs_max, Number& abs_min) noexcept;
  static void ToEqualDigits(uint64_t&, uint64_t&) noexcept;

  // проверочные методы
  static bool IsThereDot(const std::string&) noexcept;
  bool IsFullView() const noexcept;
};

}  // namespace CN