#pragma once
#include <iostream>
#include <string>

namespace CN {

const int kNumOfDigits = 8;

enum EnterMode { Mantissa, Characteristic };

class Number {
 public:
  Number() = default;
  Number(const Number& other) = default;
  Number(int);

  Number& operator=(const Number&) = default;

  // для визуализации (характеристика и мантисса)
  std::pair<int, std::string> GetNumber() const noexcept;

  // интерфейс взаимодействия
  void SignButton() noexcept;
  void CharacteristicButton();  // не уверен, может ли мантисса выдать ошибку
  void NumberButton(char);
  void ClearButton() noexcept;

  // for backup / restore
  struct BackUpIng {
    int64_t number;
    int characteristic;
    EnterMode mode;
  };

  Number(int64_t number, int characteristic) noexcept;
  BackUpIng GetClass() const noexcept;

  bool operator<(const Number&) const;
  bool operator<=(const Number&) const;
  bool operator>(const Number&) const;
  bool operator>=(const Number&) const;
  bool operator==(const Number&) const;
  bool operator!=(const Number&) const;

  Number operator+(const Number&) const;
  Number operator-(const Number&) const;
  Number operator*(const Number&) const;
  Number operator/(const Number&) const;

 private:
  int64_t number_ = 0;
  int characteristic_ = 0;
  EnterMode mode_ = Mantissa;

  template <typename T>
  static void AddNumber(T&, char) noexcept;

  std::pair<int, std::string> FullView() const noexcept;
  std::pair<int, std::string> PartView() const noexcept;
};

}  // namespace CN