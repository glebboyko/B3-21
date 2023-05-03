#pragma once

#include <wx/stattext.h>
#include <wx/wx.h>

#include <memory>
#include <vector>

#include "backend/calc_exec/calc_exec.hpp"
#include "backend/for_society/for_society.hpp"

namespace ID {

class CalculatorFrame : public wxFrame {
 public:
  CalculatorFrame(const std::string& title, std::shared_ptr<CE::Calc> calc);
  ~CalculatorFrame() = default;

 private:
  std::shared_ptr<CE::Calc> calc_;
  // Обработчики событий для кнопок
  void ButtonClick(wxCommandEvent& event);
};

}  // namespace ID