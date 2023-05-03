#include <memory>
#include <thread>

#include "frontend/interface/interface_def.hpp"
#include "frontend/visualization/visualization.hpp"

class CalculatorApp : public wxApp {
 public:
  virtual bool OnInit() {  // Создание главного окна калькулятора
    std::shared_ptr<CE::Calc> calc(new CE::Calc());

    ID::CalculatorFrame* frame = new ID::CalculatorFrame("Calculator", calc);
    frame->Show(true);

    std::thread updater = std::thread(IV::Updater, calc);
    updater.detach();
    return true;
  }
};

wxIMPLEMENT_APP(CalculatorApp);