#include "number_buffer.hpp"

CM::Buffer::Buffer(const std::vector<CN::Number>& numerated_buffer,
                   const std::vector<CN::Number>& rounded_buffer)
    : buffer_body_(numerated_buffer), round_buffer_body_(rounded_buffer) {}

const std::vector<CN::Number>& CM::Buffer::GetNumeratedBuffer() const noexcept {
  return buffer_body_;
}

std::vector<CN::Number> CM::Buffer::GetRoundedBuffer() const noexcept {
  std::vector<CN::Number> output(round_buffer_body_.size() - 1);
  for (size_t i = 0; i < round_buffer_body_.size() - 1; ++i) {
    output[i] = round_buffer_body_[i + 1];
  }
  return output;
}

void CM::Buffer::RoundClockWise() {
  CN::Number first = round_buffer_body_[0];
  for (size_t i = 0; i < kRoundedBuffSize - 1; ++i) {
    round_buffer_body_[i + 1] = round_buffer_body_[i];
  }
  round_buffer_body_[kRoundedBuffSize] = first;
  buffer_body_[0] = round_buffer_body_[0];
}

void CM::Buffer::RoundBuffer(CM::Round direction) noexcept {
  if (direction == ClockWise) {
    RoundClockWise();
  } else  {
    for (size_t i = 0; i < kRoundedBuffSize - 1; ++i) {
      RoundClockWise();
    }
  }
}

void CM::Buffer::PutFromZToX(uint32_t index) {
  if (index >= kNumeratedBuffSize) {
    throw std::out_of_range("Walter, fix it!");
  }
  buffer_body_[0] = buffer_body_[index];
  round_buffer_body_[0] = buffer_body_[index];
}

void CM::Buffer::PutFromXToZ(uint32_t index) {
  if (index > kNumeratedBuffSize) {
    throw std::out_of_range("Walter, fix it!");
  }
  buffer_body_[index] = buffer_body_[0];
}

CN::Number& CM::Buffer::GetX0() noexcept { return buffer_body_[0]; }
