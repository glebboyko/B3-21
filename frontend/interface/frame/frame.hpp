#pragma once

#include <wx/stattext.h>
#include <wx/wx.h>

#include <memory>
#include <vector>

#include "backend/calc_exec/calc_exec.hpp"
#include "frontend/interface/definition/interface_def.hpp"

namespace IF {

class CalculatorFrame : public wxFrame {
 public:
  CalculatorFrame(const std::string& title, std::shared_ptr<CE::Calc> calc);
  ~CalculatorFrame() = default;

  ID::VisualisationTemplate GetTemplate() const;

 private:
  std::shared_ptr<CE::Calc> calc_;
  ID::VisualisationTemplate visual_template_;

  // Обработчики событий для кнопок
  void ButtonClick(wxCommandEvent& event);

  void MakeBackUp(wxCommandEvent& event);
  void LoadFromBackUp(wxCommandEvent& event);

  void SaveProgram(wxCommandEvent& event);
  void LoadProgram(wxCommandEvent& event);
};

}  // namespace IF