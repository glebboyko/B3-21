#pragma once
#include <iostream>
#include <vector>

#include "backend/number/number.hpp"

namespace CM {

const uint32_t kRoundedBuffSize = 6;
const uint32_t kNumeratedBuffSize = 9;

enum Round { ClockWise, ContrClockWise };

class Buffer {
 public:
  Buffer();
  Buffer(const Buffer&);
  Buffer& operator=(const Buffer&);

  const std::vector<CN::Number>& GetNumeratedBuffer() const noexcept;
  const std::vector<CN::Number>& GetRoundedBuffer() const noexcept;

  void RoundBuffer(Round) noexcept;
  void PutFromZToX(uint32_t);
  void PutFromXToZ(uint32_t);

  CN::Number& GetX0() noexcept;

  // for backup / restore
  Buffer(const std::vector<CN::Number>& numerated_buffer,
         const std::vector<CN::Number>& rounded_buffer);

 private:
  std::vector<int> buffer_body_(kNumeratedBuffSize);
  std::vector<int> round_buffer_body_(kRoundedBuffSize);
};

}  // namespace CM