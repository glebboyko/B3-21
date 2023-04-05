#pragma once
#include <iostream>
#include <string>

namespace for_society {

enum Mode { Working, Programming, ExecutingProg, TurnedOff};

enum Button {
  ButNull,
  ButStepLeft,
  ButStepRight,
  ButBO,
  ButCP,
  ButCx,
  ButP,
  ButXy,
  ButBP,
  ButPP,
  ButNum0,
  ButNum1,
  ButNum2,
  ButNum3,
  ButNum4,
  ButNum5,
  ButNum6,
  ButNum7,
  ButNum8,
  ButNum9,
  ButXArrowY,
  ButArrowUp,
  ButMultiply,
  ButPlus,
  ButDivision,
  ButMinus,
  ButComma,
  ButPrefixMinus,
  ButVP,
  ButF
};

enum OperationCodes { OpNeutral = 0 };

}  // namespace for_society