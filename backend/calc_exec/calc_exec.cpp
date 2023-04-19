#include "calc_exec.hpp"

using namespace CE;

bool IsNum(Button button) noexcept { return FS::GetDigit(button, 2) == 4; }

Calc::Calc() { number_of_class_objects += 1; }

Calc::Calc(const CE::Calc& other)
    : program_(other.program_),
      buffer_(other.buffer_),
      curr_func_button_(other.curr_func_button_),
      mode_(other.mode_) {
  number_of_class_objects += 1;
}

Calc::~Calc() {
  if (exec_prog_thread_.has_value()) {
    mode_ = Working;
    exec_prog_thread_.value().join();
  }
  update_signal_.Send(GoodBie, MessageFromCalc);
  update_signal_.DeleteQueue();
}

Calc& Calc::operator=(const CE::Calc& other) {
  if (exec_prog_thread_.has_value()) {
    mode_ = Working;
    exec_prog_thread_.value().join();
    exec_prog_thread_ = {};
  }

  program_ = other.program_;
  buffer_ = other.buffer_;
  curr_func_button_ = other.curr_func_button_;
  mode_ = other.mode_;

  SendSignal(UpdateData);
  return *this;
}

const CP::Program& Calc::GetProgram() const noexcept { return program_; }

const CM::Buffer& Calc::GetRegisterBuffer() const noexcept { return buffer_; }

const Button& Calc::GetCurrFuncButton() const noexcept {
  return curr_func_button_;
}

const Mode& Calc::GetMode() const noexcept { return mode_; }

MQ::MessageQueue Calc::GetDataUpdateMarker() const noexcept {
  return update_signal_;
}

void Calc::PressButton(Button button) {
  if (curr_func_button_ != ButNull && button == ButCx) {
    return;
  }

  if (mode_ == ExecutingProg) {
    PressedButtonExecutingProg(button);
  } else if (button == ButP || button == ButF) {  // change curr task
    PressedFuncButton(button);
  } else if (curr_func_button_ == ButP && button == ButStepRight) {
    ChangeMode(Working);
  } else if (curr_func_button_ == ButP && button == ButStepLeft) {
    ChangeMode(Programming);
  } else if (mode_ == Working && curr_func_button_ == ButNull &&
             button == ButCP) {
    if (exec_prog_thread_.has_value()) {
      exec_prog_thread_.value().join();
    }

    ChangeMode(ExecutingProg);
    exec_prog_thread_ = std::thread(&Calc::ExecutingProgram, *this);
  } else if (mode_ == Working) {
    PressedButtonWorking(button);
  } else if (mode_ == Programming) {
    PressedButtonProgramming(button);
  }
}

void Calc::TurnOnOff() noexcept {
  if (mode_ == TurnedOff) {
    mode_ = Working;
    SendSignal(UpdateData);
  } else {
    *this = Calc();
  }
}

void Calc::ChangeMode(Mode new_mode) noexcept {
  curr_func_button_ = ButNull;
  mode_ = new_mode;
  SendSignal(UpdateData);
}

CP::OperationCodes Calc::GetOperationCode(CE::Button button) const noexcept {
  return static_cast<CP::OperationCodes>(
      (button / 1000) * 10 + FS::GetDigit(button, curr_func_button_));
}

void Calc::PressedButtonWorking(Button button) {
  if (curr_func_button_ != ButNull && IsNum(button)) {
    curr_func_button_ == ButP ? PNum(button) : FNum(button);
  } else if (IsNum(button)) {
    Num(button);
    SendSignal(UpdateData);
  } else if (button == ButStepRight) {
    program_.ExecuteStep(*this);
    SendSignal(UpdateData);
  } else if (button == ButStepLeft) {
    program_.MakeStep(CP::DirLeft);
    SendSignal(UpdateData);
  } else {
    ExecuteCommand(GetOperationCode(button));
  }
}

void Calc::PressedButtonProgramming(Button button) {
  if (button == ButStepRight) {
    program_.MakeStep(CP::DirRight);
  } else if (button == ButStepLeft) {
    program_.MakeStep(CP::DirLeft);
  } else {
    program_.EnterCode(GetOperationCode(button));
    curr_func_button_ = ButNull;
  }
  SendSignal(UpdateData);
}

void Calc::PressedButtonExecutingProg(CE::Button button) {
  if (button == ButStepLeft) {
    ChangeMode(Working);
  }
}

void Calc::PressedFuncButton(Button button) noexcept {
  curr_func_button_ = button;
  SendSignal(UpdateData);
}

void Calc::ExecuteCommand(CP::OperationCodes operation) {
  (this->*method_ptr_[operation])();
}

void Calc::ExecutingProgram() {
  while (mode_ == ExecutingProg) {
    std::this_thread::sleep_for(kWait);
    try {
      CP::OperationCodes executing_result = program_.ExecuteStep(*this);
      if (executing_result == CP::OpCP) {
        break;
      }
    } catch (...) {
      SendSignal(Error);
      break;
    }
  }
  ChangeMode(Working);
}

void Calc::SendSignal(MessageToVisualize message) {
  update_signal_.Send(message, MessageFromCalc);
  update_signal_.Receive(MessageToCalc, MQ::Wait);
}

void Calc::PNum(uint8_t num) {
  if (num > CM::kNumeratedBuffSize) {
    SendSignal(Error);
    return;
  }
  buffer_.PutFronXToZ(num);
  SendSignal(UpdateData);
}

void Calc::FNum(uint8_t num) {
  if (num > CM::kNumeratedBuffSize) {
    SendSignal(Error);
    return;
  }
  buffer_.PutFromZToX(num);
  SendSignal(UpdateData);
}

void Calc::Num(uint8_t digit) {
  buffer_.GetX0().NumberButton(digit);
  SendSignal(UpdateData);
}

Calc::Calc(const CP::Program& program_buffer, const CM::Buffer& register_buffer,
           CE::Button curr_func_button, CE::Mode mode)
    : program_(program_buffer),
      buffer_(register_buffer),
      curr_func_button_(curr_func_button),
      mode_(mode) {
  number_of_class_objects += 1;
}