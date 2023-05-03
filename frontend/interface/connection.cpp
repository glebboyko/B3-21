#include "interface_def.hpp"

namespace ID {

void CalculatorFrame::ButtonClick(wxCommandEvent& event) {
  if (event.GetId() == CE::ButNull) {
    calc_->TurnOnOff();
  } else {
    calc_->PressButton(static_cast<CE::Button>(event.GetId()));
  }
}

}  // namespace ID