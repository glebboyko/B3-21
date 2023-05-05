#include <memory>
#include <thread>

#include "backend/calc_exec/calc_exec.hpp"
#include "frontend/interface/definition/interface_def.hpp"
#include "frontend/interface/frame/frame.hpp"
#include "frontend/visualization/visualization.hpp"

class CalculatorApp : public wxApp {
 public:
  virtual bool OnInit() {  // Создание главного окна калькулятора
    std::shared_ptr<CE::Calc> calc(new CE::Calc());

    IF::CalculatorFrame* frame = new IF::CalculatorFrame("Calculator", calc);
    frame->Show(true);

    std::thread updater = std::thread(IV::Updater, calc, frame->GetTemplate());
    updater.detach();
    return true;
  }
};

wxIMPLEMENT_APP(CalculatorApp);