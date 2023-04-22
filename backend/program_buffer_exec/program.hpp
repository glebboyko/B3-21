#pragma once

#include <vector>

#include "backend/calc_exec/calc_exec.hpp"

namespace CE {
class Calc;
}

namespace CP {

const uint32_t kNotation = 6;
const uint32_t kProgBufferSize = 60;
const uint32_t kMaxOperationNum = 96;

enum OperationCodes {
  OpTrash = -1,
  OpNeutral = 0,
  OpP0 = 1,
  OpF0 = 2,
  OpPArrowUp = 3,
  OpNum0 = 4,
  OpFArrowUp = 5,
  OpArrowUp = 6,
  OpPNum1 = 11,
  OpFNum1 = 12,
  OpPXArrowY = 13,
  OpNum1 = 14,
  OpFXArrowY = 15,
  OpXArrowY = 16,
  OpPNum2 = 21,
  OpFNum2 = 22,
  OpPMultiply = 23,
  OpFNUm2 = 24,
  OpFMultiply = 25,
  OpMultiply = 26,
  OpPNum3 = 31,
  OpFNum3 = 32,
  OpPDivision = 33,
  OpNum3 = 34,
  OpFDivision = 35,
  OpDivision = 36,
  OpFXExpY = 37,
  OpXExpY = 38,
  OpPXExpY = 39,
  OpPNum4 = 41,
  OpFNum4 = 42,
  OpPComma = 43,
  OpNum4 = 44,
  OpFComma = 45,
  OpComma = 46,
  OpFBO = 47,
  OpBO = 48,
  OpPBO = 49,
  OpPNum5 = 51,
  OpFNum5 = 52,
  OpPPrefixMinus = 53,
  OpNum5 = 54,
  OpFPrefixMinus = 55,
  OpPrefixMinus = 56,
  OpFBbP = 57,
  OpBbP = 58,
  OpPBbP = 59,
  OpPNum6 = 61,
  OpFNum6 = 62,
  OpPBvP = 63,
  OpNum6 = 64,
  OpFBvP = 65,
  OpBvP = 66,
  OpFPP = 67,
  OpPP = 68,
  OpPPP = 69,
  OpPNum7 = 71,
  OpFNum7 = 72,
  OpNum7 = 74,
  OpCx = 76,
  OpFCP = 77,
  OpCP = 78,
  OpPCP = 79,
  OpPNum8 = 81,
  OpFNum8 = 82,
  OpPMinus = 83,
  OpNum8 = 84,
  OpFMinus = 85,
  OpMinus = 86,
  OpPNum9 = 91,
  OpFNum9 = 92,
  OpPPlus = 93,
  OpNum9 = 94,
  OpFPlus = 95,
  OpPlus = 96
};

enum TransferStatus { TsNoCommand, TsTransfer, TsNoTransfer };

enum Direction { DirLeft = -1, DirRight = 1 };

enum ProgramStatus { Continue, Stop, Error };

class Program {
 public:
  Program() = default;
  Program(const Program&) = default;
  Program& operator=(const Program&) = default;

  // для визуализации
  const std::vector<OperationCodes>& GetProgram() const noexcept;
  const uint32_t& GetStep() const noexcept;
  const TransferStatus& GetTransferStatus() const noexcept;

  // интерфейс взаимодействия
  void EnterCode(OperationCodes) noexcept;

  ProgramStatus ExecuteStep(CE::Calc&) noexcept;

  void StepToZero() noexcept;
  void MakeStep(Direction) noexcept;

  // for restore
  Program(const std::vector<OperationCodes>& data, uint32_t step,
          TransferStatus transfer_status);

 private:
  std::vector<OperationCodes> data_ =
      std::vector<OperationCodes>(kProgBufferSize, OpTrash);
  uint32_t step_ = 0;
  mutable TransferStatus transfer_status_ = TsNoCommand;

  void ResetTransferStatus() noexcept;

  // проверочные методы
  bool IsThereEndBefore() const noexcept;
  bool IsEnd() const noexcept;
  bool IsAbleToStepRight() const noexcept;
  std::optional<uint32_t> IsFork(const CE::Calc&) const;
};

}  // namespace CP