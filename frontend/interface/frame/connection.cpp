#include "backend/backup/backup.hpp"
#include "frame.hpp"

namespace IF {
void CalculatorFrame::ButtonClick(wxCommandEvent& event) {
  if (event.GetId() == CE::ButNull) {
    calc_->TurnOnOff();
  } else {
    calc_->PressButton(static_cast<CE::Button>(event.GetId()));
  }
}

void CalculatorFrame::MakeBackUp(wxCommandEvent& event) {
  wxFileDialog file_dialog(this, _("Make backup"), "", "",
                           "CALC files (*.calc_)|*.calc_",
                           wxFD_SAVE | wxFD_FILE_MUST_EXIST);
  if (file_dialog.ShowModal() != wxID_CANCEL) {
    BU::MakeBackup(*calc_, file_dialog.GetPath().ToStdString());
  }
}

void CalculatorFrame::LoadFromBackUp(wxCommandEvent& event) {
  wxFileDialog file_dialog(this, _("Load from backup"), "", "",
                           "CALC files (*.calc_)|*.calc_",
                           wxFD_OPEN | wxFD_FILE_MUST_EXIST);
  if (file_dialog.ShowModal() != wxID_CANCEL) {
    *calc_ = BU::RestoreFromBackup(file_dialog.GetPath().ToStdString());
  }
}

void CalculatorFrame::SaveProgram(wxCommandEvent& event) {
  wxFileDialog file_dialog(this, _("Load from backup"), "", "",
                           "PROG files (*.prog)|*.prog",
                           wxFD_SAVE | wxFD_FILE_MUST_EXIST);
  if (file_dialog.ShowModal() != wxID_CANCEL) {
    BU::SaveProgram(calc_->GetProgram().GetProgram(),
                    file_dialog.GetPath().ToStdString());
  }
}

void CalculatorFrame::LoadProgram(wxCommandEvent& event) {
  wxFileDialog file_dialog(this, _("Load from backup"), "", "",
                           "PROG files (*.prog)|*.prog",
                           wxFD_OPEN | wxFD_FILE_MUST_EXIST);
  if (file_dialog.ShowModal() != wxID_CANCEL) {
    calc_->SetProgram(BU::LoadProgram(file_dialog.GetPath().ToStdString()));
  }
}

}  // namespace IF