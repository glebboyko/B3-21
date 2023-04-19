#include "calc_exec.hpp"

using namespace CE;

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
      CP::ProgramStatus executing_result = program_.ExecuteStep(*this);

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