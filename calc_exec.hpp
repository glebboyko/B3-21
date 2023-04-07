#pragma once
#include "for_society.hpp"

namespace calc_exec {

const uint8_t kProgBufferSize = 60;

enum Mode { Working, Programming, ExecutingProg, TurnedOff };
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

class Calc {
 public:
  Calc();
  Calc(const Calc&);
  ~Calc();
  Calc& operator=(const Calc&);

  const std::vector<OperationCodes>& GetProgramBuffer() const;
  const buff::Buffer GetRegisterBuffer() const;
  Button GetCurrFuncButton() const;
  int GetStep() const;
  Mode GetMode() const noexcept;

  void PressButton(Button);
  void TurnOn();
  void TurnOff();

  // for backup / restore
  Calc(const std::vector<OperationCodes>& program_buffer,
       const buff::Buffer& register_buffer, Button curr_func_button,
       uint8_t step, Mode mode);

 private:
  std::vector<OperationCodes> program_ =
      std::vector<OperationCodes>(kProgBufferSize, OpNeutral);
  buff::Buffer buffer_;

  Button curr_func_button_ = ButNull;
  uint8_t step_ = 0;
  Mode mode_ = TurnedOff;

  void ChangeMode(Button);
  void PressedFuncButton(Button);
  void PressedStepButton(Button);
  void PressedMantissaButton();

  void WorkingWithBuffer(Button);
  void WorkingWithXY(Button);
  void WorkingWithLongBuffer(Button);

  void WorkingWithProgram(Button);
};

std::iterator_traits<std::vector<int>::iterator>::iterator_category
}  // namespace calc_exec