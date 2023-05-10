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
  const auto& program_buf = calc->GetProgram();
  const auto& num_buf = calc->GetRegisterBuffer().GetNumeratedBuffer();
  auto rounded_buf = calc->GetRegisterBuffer().GetRoundedBuffer();

  step_.Update(std::to_string(program_buf.GetStep()));

  {
    const auto& [characteristic, number] = num_buf[0].GetNumber();
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
    auto func_but = calc->GetCurrFuncButton();
    function_button_.Update(
        func_but == CE::ButP ? "P" : (func_but == CE::ButF ? "F" : "NULL"));
  }

  {
    auto mode = calc->GetMode();
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
      const auto& [characteristic, number] = num_buf[i].GetNumber();
      numerated_buffer_.second[i].Update(std::to_string(characteristic));
      numerated_buffer_.first[i].Update(number);
    }
  }

  {
    for (int i = 0; i < rounded_buffer_.first.size(); ++i) {
      const auto& [characteristic, number] = num_buf[i].GetNumber();
      rounded_buffer_.second[i].Update(std::to_string(characteristic));
      rounded_buffer_.first[i].Update(number);
    }
  }
}

TextBlock::TextBlock(const ID::TextBlock& raw) {
  curr_text_.resize(raw.object.size());
  for (int i = 0; i < raw.object.size(); ++i) {
    curr_text_[i] =
        new wxStaticText(raw.object[i].panel, raw.object[i].id,
                         raw.object[i].text, raw.object[i].location);
    curr_text_[i]->SetFont(raw.object[i].font);
  }
  pre_upd_ = raw;
}
TextBlock::TextBlock(IV::TextBlock&& outer) {
  pre_upd_ = outer.pre_upd_;
  curr_text_ = outer.curr_text_;

  outer.curr_text_.clear();
}

TextBlock& TextBlock::operator=(IV::TextBlock&& outer) {
  for (auto elem : curr_text_) {
    delete elem;
  }
  curr_text_ = outer.curr_text_;
  outer.curr_text_.clear();
}

TextBlock::~TextBlock() {
  for (auto elem : curr_text_) {
    delete elem;
  }
}
void TextBlock::Update(const std::string& str) {
  int i = 0;
  for (i = 0; i < str.size(); ++i) {
    if (pre_upd_.object[i].text == str[i]) {
      continue;
    }
    delete curr_text_[i];
    pre_upd_.object[i].text = str[i];
    curr_text_[i] =
        new wxStaticText(pre_upd_.object[i].panel, pre_upd_.object[i].id,
                         pre_upd_.object[i].text, pre_upd_.object[i].location);
    curr_text_[i]->SetFont(pre_upd_.object[i].font);
  }

  for (; i < curr_text_.size(); ++i) {
    delete curr_text_[i];
    pre_upd_.object[i].text = ' ';
  }
}
}  // namespace IV