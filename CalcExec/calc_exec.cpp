#include "calc_exec.hpp"

using namespace CE;

bool IsNum(Button button) noexcept { return FS::GetDigit(button, 2) == 4; }

const CP::Program& Calc::GetProgram() const noexcept { return program_; }

const CM::Buffer& Calc::GetRegisterBuffer() const noexcept { return buffer_; }

Button Calc::GetCurrFuncButton() const noexcept { return curr_func_button_; }

Mode Calc::GetMode() const noexcept { return mode_; }

void Calc::PressButton(Button button) {
  if (button == ButP || button == ButF) {  // change curr task
    PressedFuncButton(button);
  } else if (curr_func_button_ == ButP && button == ButStepRight) {
    ChangeMode(Working);
  } else if (curr_func_button_ == ButP && button == ButStepLeft) {
    ChangeMode(Programming);
  } else if (mode_ == Working) {
    PressedButtonWorking(button);
  } else if (mode_ == Programming) {
    PressedButtonProgramming(button);
  }
}

void Calc::TurnOn() noexcept { mode_ = Working; }

void Calc::TurnOff() noexcept { *this = Calc(); }

void Calc::ChangeMode(Mode new_mode) noexcept {
  curr_func_button_ = ButNull;
  mode_ = new_mode;
}

CP::OperationCodes Calc::GetOperationCode(CE::Button button) const noexcept {
  return static_cast<CP::OperationCodes>(
      (button / 1000) * 10 + FS::GetDigit(button, curr_func_button_));
}

void Calc::PressedButtonWorking(Button button) {
  if (curr_func_button_ != ButNull && IsNum(button)) {
    curr_func_button_ == ButP ? PNum(button) : FNum(button);
  } else if (IsNum(button)) {
    Num(button);
  } else if (button == ButStepRight) {
    program_.ExecuteStep(*this);
  } else if (button == ButStepLeft) {
    program_.MakeStep(CP::DirLeft);
  } else {
    ExecuteCommand(GetOperationCode(button));
  }
}

void Calc::PressedButtonProgramming(Button button) {
  if (button == ButStepRight) {
    program_.MakeStep(CP::DirRight);
  } else if (button == ButStepLeft) {
    program_.MakeStep(CP::DirLeft);
  } else {
    program_.EnterCode(GetOperationCode(button));
    curr_func_button_ = ButNull;
  }
}

void Calc::PressedFuncButton(Button button) noexcept {
  curr_func_button_ = button;
}

void Calc::ExecuteCommand(CP::OperationCodes operation) {
  (this->*method_ptr_[operation])();
}

void Calc::PNum(uint8_t num) { buffer_.PutFronXToZ(num); }

void Calc::FNum(uint8_t num) { buffer_.PutFromZToX(num); }

void Calc::Num(uint8_t digit) { buffer_.GetX0().NumberButton(digit); }

Calc::Calc(const CP::Program& program_buffer, const CM::Buffer& register_buffer,
           CE::Button curr_func_button, CE::Mode mode)
    : program_(program_buffer),
      buffer_(register_buffer),
      curr_func_button_(curr_func_button),
      mode_(mode) {}