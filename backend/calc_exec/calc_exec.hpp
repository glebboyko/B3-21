#pragma once
#include <unistd.h>

#include <iostream>
#include <optional>
#include <thread>
#include <vector>

#include "backend/for_society/for_society.hpp"
#include "backend/message_queue/message_queue.hpp"
#include "backend/number_buffer/number_buffer.hpp"
#include "backend/program_buffer_exec/program.hpp"

namespace CP {
class Program;
}

namespace CE {

const std::chrono::milliseconds kWait = std::chrono::milliseconds(250);

const char kMessageQueueFile[] = "message_queue_file";

enum MessageToVisualize {
  UpdateData,
  Error,
  GoodBie
};

const uint8_t kOperationQuantity = 96;
enum Mode { Working, Programming, ExecutingProg, TurnedOff };
enum Button {
  ButP = 0,
  ButF = 1,
  ButNull = 2,

  ButNum0 = 421,
  ButArrowUp = 653,
  ButNum1 = 1421,
  ButXArrowY = 1653,
  ButNum2 = 2421,
  ButMultiply = 2653,
  ButNum3 = 3421,
  ButDivision = 3653,
  ButXExpY = 3879,
  ButNum4 = 4421,
  ButComma = 4653,
  ButBO = 4879,
  ButNum5 = 5421,
  ButPrefixMinus = 5653,
  ButBbP = 5879,
  ButNum6 = 6421,
  ButBvP = 6653,
  ButPP = 6879,
  ButNum7 = 7421,
  ButCx = 7666,
  ButCP = 7879,
  ButNum8 = 8421,
  ButMinus = 8653,
  ButNum9 = 9421,
  ButPlus = 9653,

  ButStepLeft,
  ButStepRight
};

class Calc {
 public:
  Calc();
  Calc(const Calc&);
  ~Calc();
  Calc& operator=(const Calc&);

  // для визуализации
  const CP::Program& GetProgram() const noexcept;
  const CM::Buffer& GetRegisterBuffer() const noexcept;
  const Button& GetCurrFuncButton() const noexcept;
  const Mode& GetMode() const noexcept;
  MQ::MessageQueue GetDataUpdateMarker() const noexcept;

  // интерфейс взаимодействия
  void PressButton(Button);
  void TurnOnOff() noexcept;

  // for restore
  Calc(const CP::Program& program_buffer, const CM::Buffer& register_buffer,
       Button curr_func_button, Mode mode);

 private:
  CP::Program program_;
  CM::Buffer buffer_ = CM::Buffer();

  Button curr_func_button_ = ButNull;
  Mode mode_ = TurnedOff;

  MQ::MessageQueue update_signal_ =
      MQ::MessageQueue(ftok(kMessageQueueFile, number_of_class_objects));
  std::optional<std::thread> exec_prog_thread_ = {};

  static uint8_t number_of_class_objects;

  void ChangeMode(Mode);

  void PressedButtonWorking(Button);
  void PressedButtonProgramming(Button);
  void PressedButtonExecutingProg(Button);

  void PressedFuncButton(Button);

  void ExecuteCommand(CP::OperationCodes);

  void SendSignal(MessageToVisualize);

  // проверочные методы
  CP::OperationCodes GetOperationCode(Button) const noexcept;
  std::optional<Mode> IsChangingModeCommand(Button) const noexcept;

  static std::optional<std::pair<CE::Button, uint8_t>> IsPFNum(
      CP::OperationCodes) noexcept;
  static std::optional<uint8_t> IsNum(Button) noexcept;
  static std::optional<uint8_t> IsNum(CP::OperationCodes) noexcept;

  // элементарные функции
  void PNum(uint8_t);
  void FNum(uint8_t);
  void Num(uint8_t);

  void Neutral();

  /* 03 */ void PArrowUp();
  /* 06 */ void ArrowUp();
  /* 13 */ void PXArrowY();
  /* 16 */ void XArrowY();
  /* 23 */ void PMultiply();
  /* 26 */ void Multiply();
  /* 33 */ void PDivision();
  /* 36 */ void Division();
  /* 38 */ void XExpY();
  /* 45 */ void FComma();
  /* 46 */ void Comma();
  /* 48 */ void BO();
  /* 55 */ void FPrefixMinus();
  /* 56 */ void PrefixMinus();
  /* 65 */ void FVP();
  /* 66 */ void VP();
  /* 76 */ void Cx();
  /* 78 */ void CP();
  /* 83 */ void PMinus();
  /* 86 */ void Minus();
  /* 93 */ void PPlus();
  /* 96 */ void Plus();

  typedef void (Calc::*MethodPtr)();

  MethodPtr method_ptr_[kOperationQuantity + 1] = {
      &Calc::Neutral,   &Calc::Neutral,      &Calc::Neutral,
      &Calc::PArrowUp,  &Calc::Neutral,      &Calc::Neutral,
      &Calc::ArrowUp,   &Calc::Neutral,      &Calc::Neutral,
      &Calc::Neutral,   &Calc::Neutral,      &Calc::Neutral,
      &Calc::Neutral,   &Calc::PXArrowY,     &Calc::Neutral,
      &Calc::Neutral,   &Calc::XArrowY,      &Calc::Neutral,
      &Calc::Neutral,   &Calc::Neutral,      &Calc::Neutral,
      &Calc::Neutral,   &Calc::Neutral,      &Calc::PMultiply,
      &Calc::Neutral,   &Calc::Neutral,      &Calc::Multiply,
      &Calc::Neutral,   &Calc::Neutral,      &Calc::Neutral,
      &Calc::Neutral,   &Calc::Neutral,      &Calc::Neutral,
      &Calc::PDivision, &Calc::Neutral,      &Calc::Neutral,
      &Calc::Division,  &Calc::Neutral,      &Calc::XExpY,
      &Calc::Neutral,   &Calc::Neutral,      &Calc::Neutral,
      &Calc::Neutral,   &Calc::Neutral,      &Calc::Neutral,
      &Calc::FComma,    &Calc::Comma,        &Calc::Neutral,
      &Calc::BO,        &Calc::Neutral,      &Calc::Neutral,
      &Calc::Neutral,   &Calc::Neutral,      &Calc::Neutral,
      &Calc::Neutral,   &Calc::FPrefixMinus, &Calc::PrefixMinus,
      &Calc::Neutral,   &Calc::Neutral,      &Calc::Neutral,
      &Calc::Neutral,   &Calc::Neutral,      &Calc::Neutral,
      &Calc::Neutral,   &Calc::Neutral,      &Calc::FVP,
      &Calc::VP,        &Calc::Neutral,      &Calc::Neutral,
      &Calc::Neutral,   &Calc::Neutral,      &Calc::Neutral,
      &Calc::Neutral,   &Calc::Neutral,      &Calc::Neutral,
      &Calc::Neutral,   &Calc::Cx,           &Calc::Neutral,
      &Calc::CP,        &Calc::Neutral,      &Calc::Neutral,
      &Calc::Neutral,   &Calc::Neutral,      &Calc::PMinus,
      &Calc::Neutral,   &Calc::Neutral,      &Calc::Minus,
      &Calc::Neutral,   &Calc::Neutral,      &Calc::Neutral,
      &Calc::Neutral,   &Calc::Neutral,      &Calc::Neutral,
      &Calc::PPlus,     &Calc::Neutral,      &Calc::Neutral,
      &Calc::Plus};

  friend class CP::Program;
};

uint8_t Calc::number_of_class_objects = 0;

}  // namespace CE
