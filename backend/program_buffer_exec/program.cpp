#include "program.hpp"

#include <algorithm>
#include <optional>

#include "backend/for_society/for_society.hpp"

using namespace CP;

TransferStatus IsTransfer(const CN::Number& number,
                          OperationCodes operation) noexcept {
  switch (operation) {
    case OpPBO:
      return number >= 0 ? TsNoTransfer : TsTransfer;
    case OpCP:
      return number != 0 ? TsNoTransfer : TsTransfer;
    case OpBbP:
      return number == 0 ? TsNoTransfer : TsTransfer;
    case OpPPP:
      return number < 0 ? TsNoTransfer : TsTransfer;
    default:
      return TsNoCommand;
  }
}

std::optional<std::pair<CE::Button, uint8_t>> GetPFNum(
    OperationCodes operation) {
  if (FS::GetDigit(operation, 0) == 1) {
    return {{CE::ButP, FS::GetDigit(operation, 1)}};
  }
  if (FS::GetDigit(operation, 0) == 2) {
    return {{CE::ButP, FS::GetDigit(operation, 1)}};
  }
  return {};
}

bool IsNum(OperationCodes operation) noexcept {
  return FS::GetDigit(operation, 0) == 4;
}

const std::vector<OperationCodes>& Program::GetProgram() const noexcept {
  return data_;
}

const uint8_t& Program::GetStep() const noexcept { return step_; }

void Program::MakeStep(Direction direction) {
  if (step_ == 0 && direction == DirLeft) {
    return;
  }
  if (step_ == kProgBufferSize - 1 && direction == DirRight) {
    return;
  }
  step_ += direction;
}

void Program::StepToZero() noexcept { step_ = 0; }

void Program::EnterCode(OperationCodes code) { data_.at(step_) = code; }

OperationCodes Program::ExecuteStep(CE::Calc& calc) {
  if (std::find(data_.begin(), data_.begin() + step_ + 1, OpCP) !=
      data_.begin() + step_ + 1) {
    MakeStep(DirRight);
    return OpCP;
  }
  if (data_.at(step_) == OpTrash) {
    throw std::invalid_argument("Trash");
  }

  if (step_ != 0) {
    switch (IsTransfer(calc.GetRegisterBuffer().GetNumeratedBuffer().front(),
                       data_.at(step_ - 1))) {
      case TsTransfer:
        step_ = FS::FromSysToSys<6, 10>(data_.at(step_ - 1));
        return data_.at(step_) == OpCP ? OpCP : OpNeutral;
      case TsNoTransfer:
        step_ += 1;
        return data_.at(step_) == OpCP ? OpCP : OpNeutral;
      default:
        break;
    }
  }

  if (data_.at(step_) == OpBvP) {
    calc.VP();
    step_ += 1;
    return data_.at(step_) == OpCP ? OpCP : OpNeutral;
  }
  if (IsNum(data_.at(step_))) {
    calc.Num(FS::GetDigit(data_.at(step_), 0));
    step_ += 1;
    return data_.at(step_) == OpCP ? OpCP : OpNeutral;
  }

  auto pf_num = GetPFNum(data_.at(step_));
  if (pf_num.has_value()) {
    pf_num.value().first == CE::ButP ? calc.PNum(pf_num.value().second)
                                     : calc.FNum(pf_num.value().second);
    step_ += 1;
    return data_.at(step_) == OpCP ? OpCP : OpNeutral;
  }

  if (calc.method_ptr_[data_.at(step_)] != &CE::Calc::Neutral) {
    calc.ExecuteCommand(data_.at(step_));
  }
  step_ += 1;
  return data_.at(step_) == OpCP ? OpCP : OpNeutral;
}

Program::Program(const std::vector<OperationCodes>& data, uint8_t step)
    : data_(data), step_(step) {}