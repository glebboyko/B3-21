#pragma once

#include <vector>
#include "../Memory/memory.hpp"

namespace CP {

const uint8_t kProgBufferSize = 60;
const uint8_t kMaxOperationNum = 96;

enum OperationCodes { OpNeutral = 0 };

enum Direction { DirLeft, DirRight };

class Program {
 public:
  Program() = default;
  Program(const Program&) = default;
  Program& operator=(const Program&);

  const std::vector<OperationCodes>& GetProgram() const noexcept;
  uint8_t GetStep() const noexcept;

  void MakeStep(Direction);
  void StepToZero() noexcept;

  void ExecuteStep(CM::Buffer&);
  void Execute(CM::Buffer&);
  void EnterCode(OperationCodes);

  // for restore
  Program(const std::vector<OperationCodes>& data, uint8_t step);

 private:
  std::vector<OperationCodes> data_ =
      std::vector<OperationCodes>(kProgBufferSize, OpNeutral);
  uint8_t step_ = 0;
};

}  // namespace CP