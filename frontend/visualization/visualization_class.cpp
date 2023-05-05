#include "visualization.hpp"

namespace IV {
Visualization::Visualization(std::shared_ptr<CE::Calc> calc,
                             const ID::VisualisationTemplate& vis_temp) {
  step_ = TextBlock(vis_temp.step);

  main_number_.first = TextBlock(vis_temp.main_number.number);
  main_number_.second = TextBlock(vis_temp.main_number.characteristic);

  last_operations_.resize(vis_temp.last_operations.table.size());
  for (size_t i = 0; i < last_operations_.size(); ++i) {
    last_operations_[i] = TextBlock(vis_temp.last_operations.table[i]);
  }

  mode_ = TextBlock(vis_temp.mode);

  function_button_ = TextBlock(vis_temp.function_button);

  program_.resize(vis_temp.program.table.size());
  for (size_t i = 0; i < program_.size(); ++i) {
    program_[i] = TextBlock(vis_temp.program.table[i]);
  }

  numerated_buffer_.first.resize(vis_temp.numerated_buffer.number.table.size());
  for (size_t i = 0; i < numerated_buffer_.first.size(); ++i) {
    numerated_buffer_.first[i] =
        TextBlock(vis_temp.numerated_buffer.number.table[i]);
  }
  numerated_buffer_.second.resize(
      vis_temp.numerated_buffer.characteristic.table.size());
  for (size_t i = 0; i < numerated_buffer_.second.size(); ++i) {
    numerated_buffer_.second[i] =
        TextBlock(vis_temp.numerated_buffer.characteristic.table[i]);
  }

  rounded_buffer_.first.resize(vis_temp.rounded_buffer.number.table.size());
  for (size_t i = 0; i < rounded_buffer_.first.size(); ++i) {
    rounded_buffer_.first[i] =
        TextBlock(vis_temp.rounded_buffer.number.table[i]);
  }
  rounded_buffer_.second.resize(
      vis_temp.rounded_buffer.characteristic.table.size());
  for (size_t i = 0; i < rounded_buffer_.second.size(); ++i) {
    rounded_buffer_.second[i] =
        TextBlock(vis_temp.rounded_buffer.characteristic.table[i]);
  }
}

void Visualization::UpdateData() {
  const auto& program_buf = new_data_->GetProgram();
  const auto& num_buf = new_data_->GetRegisterBuffer().GetNumeratedBuffer();
  auto rounded_buf = new_data_->GetRegisterBuffer().GetRoundedBuffer();

  step_.Update(std::to_string(program_buf.GetStep()));

  {
    const auto& [sign, characteristic, number] = num_buf[0].GetNumber();

  }
}
}  // namespace IV