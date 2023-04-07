#pragma once

#include "for_society.hpp"

namespace buff {

const uint8_t kRoundedBuffSize = 6;
const uint8_t kNumeratedBuffSize = 9;

enum Round { clock_wise, contr_clock_wise };

class Buffer {
 public:
  Buffer();
  Buffer(const Buffer&);
  Buffer& operator=(const Buffer&);

  std::vector<number::Number> GetNumeratedBuffer() const noexcept;
  std::vector<number::Number> GetRoundedBuffer() const noexcept;

  void RoundBuffer(Round) noexcept;
  void PutFromZToX(uint8_t);
  void PutFronXToZ(uint8_t);

  number::Number& GetX0() noexcept;

  // for backup / restore
  Buffer(const std::vector<number::Number>& numerated_buffer,
         const std::vector<number::Number>& rounded_buffer);

 private:
};

}  // namespace buff