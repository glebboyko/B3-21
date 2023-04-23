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

const uint32_t kOperationQuantity = 96;
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

  static uint32_t number_of_class_objects;

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

  static std::optional<std::pair<CE::Button, uint32_t>> IsPFNum(
      CP::OperationCodes) noexcept;
  static std::optional<uint32_t> IsNum(Button) noexcept;
  static std::optional<uint32_t> IsNum(CP::OperationCodes) noexcept;

  // элементарные функции
  void PNum(uint32_t);
  void FNum(uint32_t);
  void Num(uint32_t);

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
    /* 0  */ &Calc::Neutral,   &Calc::Neutral,      &Calc::Neutral,
    /* 3  */ &Calc::PArrowUp,  &Calc::Neutral,      &Calc::Neutral,
    /* 6  */ &Calc::ArrowUp,   &Calc::Neutral,      &Calc::Neutral,
    /* 9  */ &Calc::Neutral,   &Calc::Neutral,      &Calc::Neutral,
    /* 12 */ &Calc::Neutral,   &Calc::PXArrowY,     &Calc::Neutral,
    /* 15 */ &Calc::Neutral,   &Calc::XArrowY,      &Calc::Neutral,
    /* 18 */ &Calc::Neutral,   &Calc::Neutral,      &Calc::Neutral,
    /* 21 */ &Calc::Neutral,   &Calc::Neutral,      &Calc::PMultiply,
    /* 24 */ &Calc::Neutral,   &Calc::Neutral,      &Calc::Multiply,
    /* 27 */ &Calc::Neutral,   &Calc::Neutral,      &Calc::Neutral,
    /* 30 */ &Calc::Neutral,   &Calc::Neutral,      &Calc::Neutral,
    /* 33 */ &Calc::PDivision, &Calc::Neutral,      &Calc::Neutral,
    /* 36 */ &Calc::Division,  &Calc::Neutral,      &Calc::XExpY,
    /* 39 */ &Calc::Neutral,   &Calc::Neutral,      &Calc::Neutral,
    /* 42 */ &Calc::Neutral,   &Calc::Neutral,      &Calc::Neutral,
    /* 45 */ &Calc::FComma,    &Calc::Comma,        &Calc::Neutral,
    /* 48 */ &Calc::BO,        &Calc::Neutral,      &Calc::Neutral,
    /* 51 */ &Calc::Neutral,   &Calc::Neutral,      &Calc::Neutral,
    /* 54 */ &Calc::Neutral,   &Calc::FPrefixMinus, &Calc::PrefixMinus,
    /* 57 */ &Calc::Neutral,   &Calc::Neutral,      &Calc::Neutral,
    /* 60 */ &Calc::Neutral,   &Calc::Neutral,      &Calc::Neutral,
    /* 63 */ &Calc::Neutral,   &Calc::Neutral,      &Calc::FVP,
    /* 66 */ &Calc::VP,        &Calc::Neutral,      &Calc::Neutral,
    /* 69 */ &Calc::Neutral,   &Calc::Neutral,      &Calc::Neutral,
    /* 72 */ &Calc::Neutral,   &Calc::Neutral,      &Calc::Neutral,
    /* 75 */ &Calc::Neutral,   &Calc::Cx,           &Calc::Neutral,
    /* 78 */ &Calc::CP,        &Calc::Neutral,      &Calc::Neutral,
    /* 81 */ &Calc::Neutral,   &Calc::Neutral,      &Calc::PMinus,
    /* 84 */ &Calc::Neutral,   &Calc::Neutral,      &Calc::Minus,
    /* 87 */ &Calc::Neutral,   &Calc::Neutral,      &Calc::Neutral,
    /* 90 */ &Calc::Neutral,   &Calc::Neutral,      &Calc::Neutral,
    /* 93 */ &Calc::PPlus,     &Calc::Neutral,      &Calc::Neutral,
    /* 96 */ &Calc::Plus};

  friend class CP::Program;
};

uint32_t Calc::number_of_class_objects = 0;

}  // namespace CE
