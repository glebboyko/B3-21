#include "interface_def.hpp"

namespace ID {

TextBlock::TextBlock(uint32_t size, ID::TextParameters parameters,
                     ID::WxTextArgs other_args) {
  object.resize(size);
  for (int32_t i = 0; i < size; ++i) {
    object[i].location = {parameters.init_x + (i * parameters.x_offset),
                          parameters.init_y};
    object[i].panel = other_args.panel;
    object[i].id = other_args.id;
    object[i].text = other_args.text;
    object[i].font = other_args.font;
  }
}

TextBlockTable::TextBlockTable(ID::TableParameters parameters,
                               ID::TextBlock template_text_block) {
  table.resize(parameters.column_num * parameters.raw_num);

  const int32_t kSymbolOffset =
      template_text_block.object.size() > 1
          ? template_text_block.object[1].location.x -
                template_text_block.object[0].location.x
          : 0;

  for (uint32_t i = 0; i < parameters.column_num; ++i) {
    for (uint32_t j = 0; j < parameters.raw_num; ++j) {
      std::pair<int32_t, int32_t> curr_init = {
          parameters.init_x + (i * parameters.column_offset),
          parameters.init_y + (j * parameters.raw_offset)};
      auto& container = table[i * parameters.raw_num + j];

      container = template_text_block;
      for (int32_t k = 0; k < container.object.size(); ++k) {
        container.object[k].location =
            wxPoint(curr_init.first + (k * kSymbolOffset), curr_init.second);
      }
    }
  }
}

VisualisationTemplate::VisualisationTemplate() {
  const int32_t kTableSymbolOffset = 9;
  const int32_t kRawOffset = 30;
  const int32_t kNumofOperDigits = 2;
  const int32_t kNumofStepDigits = 2;
  const uint32_t kNumOfPrevOperations = 3;
  const int32_t kNumofCharacteristic = CN::kNumOfCharacteristic + 1;
  const uint32_t kNumofModes = 11;
  const uint32_t kNumofFb = 4;
  const int32_t kNumofNumber = CN::kNumOfDigits + 1;
  WxTextArgs static_text_args;

  //---------PROGRAM------------
  {
    TableParameters table_parameters = {574, 143, kRawOffset, 145, 20, 3};
    TextBlock text_block(kNumofOperDigits, {0, 0, kTableSymbolOffset},
                         static_text_args);
    program = TextBlockTable(table_parameters, text_block);
  }
  //--------STEP-----------
  {
    TextParameters parameters = {136, 176, 8};
    const int kSymbolSize = 10;
    WxTextArgs step_args;
    step_args.font.first = wxFont(kSymbolSize, wxFONTFAMILY_DEFAULT,
                                  wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    step = TextBlock(kNumofStepDigits, parameters, step_args);
  }
  //----------MAIN_NUMBER---------
  {
    TextParameters num_parameters = {170, 194, 21};
    TextParameters char_parameters = {130, 204, 10};

    WxTextArgs num_text_args;
    num_text_args.font.first =
        wxFont(26, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    WxTextArgs char_text_args;
    char_text_args.font.first =
        wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

    TextBlock number(kNumofNumber, num_parameters, num_text_args);
    TextBlock characteristic(kNumofCharacteristic, char_parameters,
                             char_text_args);
    main_number = {number, characteristic};
  }
  //-------------LAST_OPERATIONS-------------
  {
    TextParameters text_parameters = {0, 0, 10};

    WxTextArgs lo_text_args;
    lo_text_args.font.first =
        wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

    TextBlock text_block(kNumofOperDigits, text_parameters, lo_text_args);

    const int kLORawOffset = 13;
    TableParameters parameters = {
        360, 178, kLORawOffset, 0, kNumOfPrevOperations, 1};

    last_operations = TextBlockTable(parameters, text_block);
  }
  //-------------MODE-------------
  {
    TextParameters parameters = {544, 108, 10};
    WxTextArgs mode_text_args;
    mode_text_args.font.first =
        wxFont(13, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    mode = TextBlock(kNumofFb, parameters, mode_text_args);
  }
  //------------FUNCTION_BUTTON------------
  {
    TextParameters parameters = {648, 79, 10};
    WxTextArgs fb_text_args;
    fb_text_args.font.first =
        wxFont(13, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    function_button = TextBlock(kNumofModes, parameters, fb_text_args);
  }
  //--------------NUMERATED_BUFFER------------
  {
    TextParameters text_parameters = {0, 0, kTableSymbolOffset};
    TableParameters table_parameters_number = {1135, 140, kRawOffset, 0, 8, 1};
    TableParameters table_parameters_characteristic = {1050, 140, kRawOffset,
                                                       0,    8,   1};
    TextBlock text_block_number = {kNumofNumber, text_parameters,
                                   static_text_args};
    TextBlock text_block_characteristic = {kNumofCharacteristic,
                                           text_parameters, static_text_args};
    TextBlockTable number =
        TextBlockTable(table_parameters_number, text_block_number);
    TextBlockTable characteristic = TextBlockTable(
        table_parameters_characteristic, text_block_characteristic);
    numerated_buffer = {number, characteristic};
  }
  //---------------ROUNDED_BUFFER-----------
  {
    TextParameters text_parameters = {0, 0, kTableSymbolOffset};
    TableParameters table_parameters_number = {1135, 410, kRawOffset, 0, 6, 1};
    TableParameters table_parameters_characteristic = {1050, 410, kRawOffset,
                                                       0,    6,   1};
    TextBlock text_block_number = {kNumofNumber, text_parameters,
                                   static_text_args};
    TextBlock text_block_characteristic = {kNumofCharacteristic,
                                           text_parameters, static_text_args};
    TextBlockTable number =
        TextBlockTable(table_parameters_number, text_block_number);
    TextBlockTable characteristic = TextBlockTable(
        table_parameters_characteristic, text_block_characteristic);
    rounded_buffer = {number, characteristic};
  }
}
void TextBlock::SetPanel(wxPanel* panel) {
  for (auto& elem : object) {
    elem.panel = panel;
  }
}

void TextBlockTable::SetPanel(wxPanel* panel) {
  for (auto& elem : table) {
    elem.SetPanel(panel);
  }
}
void VisualisationTemplate::SetPanel(wxPanel* panel) {
  step.SetPanel(panel);

  main_number.number.SetPanel(panel);
  main_number.characteristic.SetPanel(panel);

  last_operations.SetPanel(panel);
  mode.SetPanel(panel);
  function_button.SetPanel(panel);
  program.SetPanel(panel);

  numerated_buffer.number.SetPanel(panel);
  numerated_buffer.characteristic.SetPanel(panel);

  rounded_buffer.number.SetPanel(panel);
  rounded_buffer.characteristic.SetPanel(panel);
}
};  // namespace ID
