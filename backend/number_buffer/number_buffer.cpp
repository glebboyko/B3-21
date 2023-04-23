#include "number_buffer.hpp"

CM::Buffer::Buffer();

CM::Buffer::Buffer(const CM::Buffer& other) {
  buffer_body_ = other.buffer_body_;
  round_buffer_body_ = other.round_buffer_body_;
}

Buffer &CM::Buffer::operator=(const CM::Buffer& other) {
  buffer_body_ = other.buffer_body_;
  round_buffer_body_ = other.round_buffer_body_;
}

CM::Buffer::Buffer(const std::vector<CN::Number>& numerated_buffer, const std::vector<CN::Number>& rounded_buffer) {
  buffer_body_ = numerated_buffer;
  round_buffer_body_ = rounded_buffer;
}

const std::vector<CN::Number>& CM::Buffer::GetNumeratedBuffer() const noexcept {
  std::vector<int>& ref_to_body = buffer_body_;
  return ref_to_body;
}

const std::vector<CN::Number>& CM::Buffer::GetRoundedBuffer() const noexcept {
  std::vector<int>& ref_to_round = round_buffer_body_;
  return ref_to_round;
}

void CM::Buffer::RoundBuffer(CM::Round) noexcept {
  int first = round_buffer_body_[0];
  for (size_t i = 0; i < kRoundedBuffSize; ++i) {
    round_buffer_body_[i] = round_buffer_body_[i + 1];
     if (i == 5) {
       round_buffer_body_[5] = first;
       break;
     }
   }
  buffer_body_[0] = round_buffer_body_[0];
}

void CM::Buffer::PutFromZToX(uint32_t value) {
  if (value > buffer_body_[8]) {
    throw std::out_of_range;
  }
  buffer_body_[0] = value;
  round_buffer_body_[0] = value;
}

void CM::Buffer::PutFromXToZ(uint32_t index) {
  if (index > buffer_body_[8]) {
    throw std::out_of_range;
  }
  buffer_body_[index] = buffer_body_[0];
}

int& CM::Buffer::GetX0() noexcept {
  int& ref_to_first = buffer_body_[0];
  return ref_to_first;
}