#include "visualization.hpp"

namespace IV {
void Updater(std::shared_ptr<CE::Calc> calc,
             ID::VisualisationTemplate visualisation_template) {
  Visualization visualisator(calc, visualisation_template);
  auto queue_checker = calc->GetDataUpdateMarker();
  while (true) {
    auto received_msg = queue_checker.Receive(1, MQ::Wait);
    if (received_msg.value() == CE::Error) {
      wxMessageBox("Aaaaaaaaa", "Fatal Crash", wxOK | wxICON_ERROR);
    } else if (received_msg.value() == CE::UpdateData) {
      visualisator.UpdateData();
    } else {
      break;
    }
  }
}

}  // namespace IV