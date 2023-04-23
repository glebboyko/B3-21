#include "calc_exec.hpp"
#include "calc_math.hpp"

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

  void Calc::Neutral() {
    curr_func_button_ = ButNull;
    SendSignal(UpdateData);
  }

  void Calc::PArrowUp() {
    CN::Number& x_0 = buffer_.GetX0();
    x_0 = Math::Exp(x_0);
    SendSignal(UpdateData);
    curr_func_button_ = ButNull;

  }

  void Calc::ArrowUp() {
    buffer_.PutFromXToZ(1);
    SendSignal(UpdateData);
    curr_func_button_ = ButNull;
  }

  void Calc::PXArrowY() {
    CN::Number& x_0 = buffer_.GetX0();
    x_0 = Math::Ln(x_0);
    SendSignal(UpdateData);
    curr_func_button_ = ButNull;
  }

  void Calc::XArrowY() {
    CN::Number tmp = buffer_.GetNumeratedBuffer()[1];
    buffer_.PutFromZToX(1);
    buffer_.GetX0() = tmp;
    SendSignal(UpdateData);
    curr_func_button_ = ButNull;
  }

  void Calc::PMultiply() {
    CN::Number& x_0 = buffer_.GetX0();
    x_0 = Math::kPi;
    SendSignal(UpdateData);
    curr_func_button_ = ButNull;
  }

  void Calc::Multiply() {
    CN::Number y = buffer_.GetNumeratedBuffer()[1];
    CN::Number& x = buffer_.GetX0();
    x = x * y;
    SendSignal(UpdateData);
    curr_func_button_ = ButNull;
  }

  void Calc::PDivision() {
    PArrowUp();
  }

  void Calc::Division() {
    CN::Number y = buffer_.GetNumeratedBuffer()[1];
    CN::Number& x = buffer_.GetX0();
    x = x / y;
    SendSignal(UpdateData);
    curr_func_button_ = ButNull;
  }

  void Calc::XExpY() {
    CN::Number y = buffer_.GetNumeratedBuffer()[1];
    CN::Number& x = buffer_.GetX0();
    x = Math::Pow(x, y);
    SendSignal(UpdateData);
    curr_func_button_ = ButNull;
  }

  void Calc::FComma() {
    CN::Number& x = buffer_.GetX0();
    x = CN::Number(1) / x;
    SendSignal(UpdateData);
    curr_func_button_ = ButNull;
  }

  void Calc::Comma() {
    SendSignal(UpdateData);
    curr_func_button_ = ButNull;
  }

  void Calc::BO() {
    curr_func_button_ = ButNull;
  }
  void Calc::FPrefixMinus() {
    CN::Number& x = buffer_.GetX0();
    x = Math::Pow(x, 2);
    SendSignal(UpdateData);
    curr_func_button_ = ButNull;
  }

  void Calc::PrefixMinus() {
    CN::Number& x = buffer_.GetX0();
    x = CN::Number(-1) * x;
    SendSignal(UpdateData);
    curr_func_button_ = ButNull;
  }

  void Calc::FVP() {
    CN::Number& x = buffer_.GetX0();
    x = Math::Root(x);
    SendSignal(UpdateData);
    curr_func_button_ = ButNull;
  }

  void Calc::VP() {

  }
  void Calc::Cx() {

  }

  void Calc::PMinus() {
    CN::Number& x = buffer_.GetX0();
    x = Math::Cos(x);
    SendSignal(UpdateData);
    curr_func_button_ = ButNull;
  }

  void Calc::Minus() {
    CN::Number y = buffer_.GetNumeratedBuffer()[1];
    CN::Number& x = buffer_.GetX0();
    x = x - y;
    SendSignal(UpdateData);
    curr_func_button_ = ButNull;
  }

  void Calc::PPlus() {
    CN::Number& x = buffer_.GetX0();
    x = Math::Sin(x);
    SendSignal(UpdateData);
    curr_func_button_ = ButNull;
  }

  void Calc::Plus() {
    CN::Number y = buffer_.GetNumeratedBuffer()[1];
    CN::Number& x = buffer_.GetX0();
    x = x - y;
    SendSignal(UpdateData);
    curr_func_button_ = ButNull;
  }
};

