#include <wx/wx.h>

#include <memory>

#include "backend/calc_exec/calc_exec.hpp"
#include "frontend/interface/definition/interface_def.hpp"
#include "frontend/interface/frame/frame.hpp"
#include "frontend/visualization/visualization.hpp"

class Updater : public wxThread {
 public:
  Updater(std::shared_ptr<CE::Calc> calc,
          const ID::VisualisationTemplate& visualisation_template)
      : wxThread(wxTHREAD_DETACHED),
        calc_(calc),
        vis_tem_(visualisation_template) {}

  virtual void* Entry() {
    IV::Updater(calc_, vis_tem_);
    return nullptr;
  }

 private:
  std::shared_ptr<CE::Calc> calc_;
  ID::VisualisationTemplate vis_tem_;
};

class CalculatorApp : public wxApp {
 public:
  virtual bool OnInit() {  // Создание главного окна калькулятора
    std::shared_ptr<CE::Calc> calc(new CE::Calc());

    IF::CalculatorFrame* frame = new IF::CalculatorFrame("Calculator", calc);
    frame->Show(true);

    Updater* updater = new Updater(calc, frame->GetTemplate());
    updater->Run();
    return true;
  }
};

wxIMPLEMENT_APP(CalculatorApp);