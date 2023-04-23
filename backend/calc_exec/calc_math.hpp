#include "backend/number/number.hpp"

namespace Math {

  const CN::Number kPi = static_cast<float>(3.14159265359);

  CN::Number Pow(CN::Number num, CN::Number power) {
    auto res = num;
    for (CN::Number i = 0; i < power; i = i + CN::Number(1)) {
      res *= res;
    }
    return res;
  }

  CN::Number Factorial(CN::Number n) {
      if (n == 0 || n == 1) {
          return CN::Number(1);
      }
      CN::Number result = 1;
      for (CN::Number i = 2; i <= n; i = i + CN::Number(1)) {
          result *= i;
      }
      return result;
  }

  CN::Number Exp(CN::Number x) {
      CN::Number result = 1;
      CN::Number term;
      int i = 1;
      CN::Number epsilon = static_cast<float>(1e-6);

      do {
          term = Pow(x, i) / Factorial(i);
          result += term;
          ++i;
      } while (term > epsilon);

      return result;
  }

  CN::Number Sin(CN::Number x) {
    CN::Number result = x;
    CN::Number term;
    int i = 3;
      CN::Number epsilon = static_cast<float>(1e-6);
    do {
        term = (Pow(CN::Number(-1), i) * (Pow(x, i) / Factorial(i)));
        result += term;
        i += 2;
    } while (term > epsilon);
    return result;
  }

  CN::Number Cos(CN::Number x) {
    CN::Number result = 1;
    CN::Number term;
    int i = 2;
    CN::Number epsilon = static_cast<float>(1e-6);
    do {
        term = (Pow(CN::Number(-1), i + 1) * (Pow(x, i) / Factorial(i)));
        result += term;
        i += 2;
    } while (term > epsilon);

    return result;
  }

  CN::Number LnLimited(CN::Number x) {
    CN::Number ln2 = static_cast<float>(0.693147181);
    if (x != 1) {
      CN::Number epsilon = static_cast<float>(1e-6);
      CN::Number result = 0;
      CN::Number prev_result;
      CN::Number x_power = x;
      int i = 1;

      do {
          prev_result = result;
          CN::Number term = CN::Number(i % 2 == 1 ? 1 : -1) * Pow(x, i) / i;
          result += term;
          ++i;
      } while (((result - prev_result) < 0 ? CN::Number(-1) * (result - prev_result) : result - prev_result) >= epsilon);

      return result;
      }
    return ln2;
  }

  CN::Number Ln(CN::Number x) {
    CN::Number result;
    if (x <= 1 && x > -1) {
      return LnLimited(x);
    }
    CN::Number y = x / 2;
    int count = 1;
    while (y >= 2) {
      y = y / 2;
      ++count;
    }
    return LnLimited(y - 1) + (CN::Number(count) * LnLimited(1));
  }

  CN::Number Root(CN::Number x) {
      CN::Number epsilon = static_cast<float>(1e-6);
      CN::Number y = x;
      CN::Number y_next;
      do {
          y_next = y - (y * y - x) / (CN::Number(2) * y);
          if (((y - y_next) < 0 ? CN::Number(-1) * (y - y_next) : (y - y_next)) < epsilon) {
              break;
          }
          y = y_next;
      } while (true);
      return y_next;
  }
};