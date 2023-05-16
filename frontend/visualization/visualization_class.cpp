#include "visualization.hpp"

namespace IV {
Visualization::Visualization(std::shared_ptr<CE::Calc> calc,
                             const ID::VisualisationTemplate& vis_temp) {
  step_ = TextBlock(vis_temp.step);
  calc_ = calc;

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
  const auto& program_buf = calc_->GetProgram();
  const auto& num_buf = calc_->GetRegisterBuffer().GetNumeratedBuffer();
  auto rounded_buf = calc_->GetRegisterBuffer().GetRoundedBuffer();

  step_.Update(std::to_string(program_buf.GetStep()));

  if (step_mem_ != -1) {
    if (step_mem_ != program_buf.GetStep()) {
      program_[step_mem_].SwitchFont();
      step_mem_ = program_buf.GetStep();
      program_[step_mem_].SwitchFont();
    }
  } else {
    step_mem_ = program_buf.GetStep();
    program_[step_mem_].SwitchFont();
  }

  {
    const auto& [characteristic, number] = num_buf[0].GetMainNumber();
    main_number_.first.Update(number);
    main_number_.second.Update(std::to_string(characteristic));
  }

  for (size_t i = 0; i < last_operations_.size(); ++i) {
    if (static_cast<int32_t>(program_buf.GetStep()) - static_cast<int32_t>(i) <
        0) {
      last_operations_[i].Update("");
    } else {
      last_operations_[i].Update(
          std::to_string(program_buf.GetProgram()[program_buf.GetStep() - i]));
    }
  }

  {
    auto func_but = calc_->GetCurrFuncButton();
    function_button_.Update(
        func_but == CE::ButP ? "P" : (func_but == CE::ButF ? "F" : "NULL"));
  }

  {
    auto mode = calc_->GetMode();
    mode_.Update(
        mode == CE::Working
            ? "Working"
            : (mode == CE::Programming
                   ? "Programming"
                   : (mode == CE::ExecutingProg ? "Executing" : "TurnedOff")));
  }

  for (size_t i = 0; i < program_.size(); ++i) {
    program_[i].Update(
        std::to_string(program_buf.GetProgram()[program_buf.GetStep() - i]));
  }

  {
    for (int i = 0; i < numerated_buffer_.first.size(); ++i) {
      const auto& [characteristic, number] = num_buf[i].GetStaticNumber();
      numerated_buffer_.second[i].Update(std::to_string(characteristic));
      numerated_buffer_.first[i].Update(number);
    }
  }

  {
    for (int i = 0; i < rounded_buffer_.first.size(); ++i) {
      const auto& [characteristic, number] = num_buf[i].GetStaticNumber();
      rounded_buffer_.second[i].Update(std::to_string(characteristic));
      rounded_buffer_.first[i].Update(number);
    }
  }
}

TextBlock::TextBlock(const ID::TextBlock& raw) {
  curr_text_ = new wxStaticText(raw.panel, raw.id, raw.text, raw.location);
  curr_text_->SetFont(raw.font.first);
  pre_upd_ = raw;
}
TextBlock::TextBlock(IV::TextBlock&& outer) {
  pre_upd_ = outer.pre_upd_;
  curr_text_ = outer.curr_text_;
  curr_font_ = outer.curr_font_;

  outer.curr_text_ = nullptr;
}

TextBlock& TextBlock::operator=(IV::TextBlock&& outer) {
  delete curr_text_;
  curr_text_ = outer.curr_text_;
  outer.curr_text_ = nullptr;
  curr_font_ = outer.curr_font_;
  pre_upd_ = outer.pre_upd_;
  return *this;
}

TextBlock::~TextBlock() { delete curr_text_; }
void TextBlock::Update(const std::string& str) {
  if (pre_upd_.text != str) {
    pre_upd_.text = str;
    delete curr_text_;
    curr_text_ = new wxStaticText(pre_upd_.panel, pre_upd_.id, pre_upd_.text,
                                  pre_upd_.location);
    curr_text_->SetFont(curr_font_ ? pre_upd_.font.second
                                   : pre_upd_.font.first);
  }
}

void TextBlock::SwitchFont() {
  curr_font_ = !(curr_font_);
  curr_text_->SetFont(curr_font_ ? pre_upd_.font.second : pre_upd_.font.first);
}

}  // namespace IV