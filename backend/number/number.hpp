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
  Number(const Number&);
  Number(Number&&);
  Number(int);
  Number(float);

  Number& operator=(const Number&);
  Number& operator=(Number&&);

  // для визуализации (знак, характеристика и мантисса)
  std::tuple<bool, int, std::string> GetNumber() const noexcept;

  // интерфейс взаимодействия
  void SignButton() noexcept;
  void DotButton() noexcept;
  void CharacteristicButton();
  void NumberButton(char);
  void ClearButton() noexcept;

  // операторы сравнения
  bool operator<(Number) const;
  bool operator<=(Number) const;
  bool operator>(Number) const;
  bool operator>=(Number) const;
  bool operator==(Number) const;
  bool operator!=(Number) const;

  // арифметические операции
  Number operator-() const;
  Number operator+(const Number&) const;
  Number operator-(const Number&) const;
  Number operator*(const Number&) const;
  Number operator/(const Number&) const;
  Number operator%(const Number&) const;

  Number& operator+=(const Number&);
  Number& operator-=(const Number&);
  Number& operator*=(Number);
  Number& operator/=(Number);
  Number& operator%=(Number);

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
  static void ToEqualDigits(Number& abs_max, Number& abs_min);
  static void ToEqualDigits(uint64_t&, uint64_t&);

  // проверочные методы
  static bool IsThereDot(const std::string&) noexcept;
  bool IsFullView() const noexcept;
  static void IsOverflow(Number&);
};

}  // namespace CN