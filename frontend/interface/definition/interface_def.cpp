#include "interface_def.hpp"

namespace ID {

TextBlockTable::TextBlockTable(ID::TableParameters parameters,
                               ID::TextBlock template_text_block) {
  table.resize(parameters.column_num * parameters.raw_num);

  for (int32_t i = 0; i < parameters.column_num; ++i) {
    for (int32_t j = 0; j < parameters.raw_num; ++j) {
      table[i * parameters.raw_num + j].location = {
          parameters.init_x + (i * parameters.column_offset),
          parameters.init_y + (j * parameters.raw_offset)};
    }
  }
}

VisualisationTemplate::VisualisationTemplate() {
  const int32_t kRawOffset = 30;
  const uint32_t kNumOfPrevOperations = 3;

  //--------STEP-----------
  {
    step.location = {136, 176};
    step.font.first = wxFont(
        10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
  }

  //----------MAIN_NUMBER---------
  {
    main_number.number.location = {170, 194};
    main_number.number.font.first =
        wxFont(26, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

    main_number.characteristic.location = {130, 204};
    main_number.characteristic.font.first =
        wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
  };

  //-------------LAST_OPERATIONS-------------
  {
    TextBlock text_block;
    text_block.font.first =
        wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

    const int kLORawOffset = 13;
    TableParameters parameters = {
        360, 178, kLORawOffset, 0, kNumOfPrevOperations, 1};

    last_operations = TextBlockTable(parameters, text_block);
  }

  //-------------MODE-------------
  {
    mode.location = {544, 108};
    mode.font.first =
        wxFont(13, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
  };

  //------------FUNCTION_BUTTON------------
  { function_button.location = {648, 79}; }

  //---------PROGRAM------------
  {
    TableParameters table_parameters = {574, 143, kRawOffset, 145, 20, 3};
    program = TextBlockTable(table_parameters, TextBlock());
  }
  //--------------NUMERATED_BUFFER------------
  {
    TableParameters table_parameters_number = {1135, 140, kRawOffset, 0, 8, 1};
    numerated_buffer.number =
        TextBlockTable(table_parameters_number, TextBlock());

    TableParameters table_parameters_characteristic = {1050, 140, kRawOffset,
                                                       0,    8,   1};
    numerated_buffer.characteristic =
        TextBlockTable(table_parameters_characteristic, TextBlock());
  }
  //---------------ROUNDED_BUFFER-----------
  {
    TableParameters table_parameters_number = {1135, 410, kRawOffset, 0, 6, 1};
    rounded_buffer.number =
        TextBlockTable(table_parameters_number, TextBlock());

    TableParameters table_parameters_characteristic = {1050, 410, kRawOffset,
                                                       0,    6,   1};
    rounded_buffer.characteristic =
        TextBlockTable(table_parameters_characteristic, TextBlock());
  }
}

void TextBlockTable::SetPanel(wxWindow* panel) {
  for (auto& elem : table) {
    elem.panel = panel;
  }
}
void VisualisationTemplate::SetPanel(wxWindow* panel) {
  step.panel = panel;

  main_number.number.panel = panel;
  main_number.characteristic.panel = panel;

  last_operations.SetPanel(panel);
  mode.panel = panel;
  function_button.panel = panel;
  program.SetPanel(panel);

  numerated_buffer.number.SetPanel(panel);
  numerated_buffer.characteristic.SetPanel(panel);

  rounded_buffer.number.SetPanel(panel);
  rounded_buffer.characteristic.SetPanel(panel);
}
};  // namespace ID
