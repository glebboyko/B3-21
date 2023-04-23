#include "calc_exec.hpp"

namespace CE {

void Calc::CP() {
  // подготовка
  if (exec_prog_thread_.has_value()) {
    exec_prog_thread_.value().join();
  }
  ChangeMode(ExecutingProg);

  // распараллеливание
  exec_prog_thread_ = std::thread([this]() {
    // исполняем, пока можно
    while (mode_ == ExecutingProg) {
      // здоровый сон
      std::this_thread::sleep_for(kWait);

      // выполняем команду
      CP::ProgramStatus executing_result = program_->ExecuteStep(*this);

      // проверяем результат выполнения
      if (executing_result == CP::Stop) {
        break;
      }
      if (executing_result == CP::Error) {
        SendSignal(Error);
        break;
      }

      // обновляем визуализацию
      SendSignal(UpdateData);
    }

    ChangeMode(Working);
  });
}

void Calc::Neutral() {}
void Calc::PArrowUp() {}
void Calc::ArrowUp() {}
void Calc::PXArrowY() {}
void Calc::XArrowY() {}
void Calc::PMultiply() {}
void Calc::Multiply() {}
void Calc::PDivision() {}
void Calc::Division() {}
void Calc::XExpY() {}
void Calc::FComma() {}
void Calc::Comma() {}
void Calc::BO() {}
void Calc::FPrefixMinus() {}
void Calc::PrefixMinus() {}
void Calc::FVP() {}
void Calc::VP() {}
void Calc::Cx() {}
void Calc::PMinus() {}
void Calc::Minus() {}
void Calc::PPlus() {}
void Calc::Plus() {}

}