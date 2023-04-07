#include "calc_exec.hpp"

using namespace CE;

const std::vector<OperationCodes>& Calc::GetProgramBuffer() const noexcept {
  return program_;
}

const CM::Buffer& Calc::GetRegisterBuffer() const noexcept { return buffer_; }

Button Calc::GetCurrFuncButton() const noexcept { return curr_func_button_; }

uint8_t Calc::GetStep() const noexcept { return FS::ToHexadecimal(step_); }

Mode Calc::GetMode() const noexcept { return mode_; }

void Calc::PressButton(Button button) {

}