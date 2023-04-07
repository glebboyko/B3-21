#pragma once
#include <iostream>
#include <vector>

#include "../Number/number.hpp"

namespace CM {

const uint8_t kRoundedBuffSize = 6;
const uint8_t kNumeratedBuffSize = 9;

enum Round { ClockWise, ContrClockWise };

class Buffer {
 public:
  Buffer();
  Buffer(const Buffer&);
  Buffer& operator=(const Buffer&);

  std::vector<CN::Number> GetNumeratedBuffer() const noexcept;
  std::vector<CN::Number> GetRoundedBuffer() const noexcept;

  void RoundBuffer(Round) noexcept;
  void PutFromZToX(uint8_t);
  void PutFronXToZ(uint8_t);

  CN::Number& GetX0() noexcept;

  // for backup / restore
  Buffer(const std::vector<CN::Number>& numerated_buffer,
         const std::vector<CN::Number>& rounded_buffer);

 private:
};

}  // namespace CM