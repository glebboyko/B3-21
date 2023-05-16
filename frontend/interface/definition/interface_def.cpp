#include "interface_def.hpp"

namespace ID {

TextBlock::TextBlock(uint8_t size, ID::TextParameters parameters,
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
  table.resize(parameters.init_x * parameters.init_y);

  const int32_t kSymbolOffset =
      template_text_block.object.size() > 1
          ? template_text_block.object[1].location.x -
                template_text_block.object[0].location.x
          : 0;

  for (uint8_t i = 0; i < parameters.column_num; ++i) {
    for (uint8_t j = 0; j < parameters.raw_num; ++j) {
      std::pair<int32_t, int32_t> curr_init = {
          parameters.init_x + (i * parameters.column_offset),
          parameters.init_y + (j * parameters.raw_offset)};
      auto& container = table[i * parameters.raw_num + j];

      container = template_text_block;
      for (int32_t k = 0; i < container.object.size(); ++i) {
        container.object[k].location =
            wxPoint(curr_init.first + (k * kSymbolOffset), curr_init.second);
      }
    }
  }
}

  VisualisationTemplate::VisualisationTemplate() {
    const uint8_t kTableSize = 10;
    const int32_t kXOffset = 10;
    const int32_t kRawOffset = 30;
    const int32_t kNumofOperDigits = 2;
    const int32_t kNumofStep = 2;
    const uint8_t kNumOfPrevOperations = 3;
    const int32_t kNumofCharacteristic = 3;
    const uint8_t kNumofModes = 11;
    const uint8_t kNumofFb = 4;
    const int32_t kNumofNumber = 9;
    WxTextArgs static_text_args;
    static_text_args.font = {};
    
    //---------PROGRAM------------
    {
      TableParameters table_parameters = {547, 142, kRawOffset, 145, 20, 3};
      TextBlock text_block(kNumofOperDigits, {0, 0, kXOffset}, static_text_args);
      program = TextBlockTable(table_parameters, text_block);
    }
    //--------STEP-----------
    {
      TextParameters parameters = {0, 0, kXOffset};
      step = TextBlock(kNumofStep, parameters, static_text_args);
    }
    //----------MAIN_NUMBER---------
    {
      TextParameters parameters = {0, 0, kXOffset};
      TextBlock number(kNumofNumber, parameters, static_text_args);
      TextBlock characteristic(kNumofCharacteristic, parameters, static_text_args);
      main_number = {number, characteristic};
    }
    //-------------LAST_OPERATIONS-------------
    {
      TextParameters text_parameters = {0, 0, kXOffset};
      TableParameters parameters = {0, 0, kRawOffset, 0, 0, 0};
      TextBlock text_block(kNumOfPrevOperations, text_parameters, static_text_args);
      last_operations = TextBlockTable(parameters, text_block);
    }
    //-------------MODE-------------
    {
      TextParameters parameters = {0, 0, kXOffset};
      mode = TextBlock(kNumofFb, parameters, static_text_args);
    }
    //------------FUNCTION_BUTTON------------
    {
      TextParameters parameters = {0, 0, kXOffset};
      function_button = TextBlock(kNumofModes, parameters, static_text_args);
    }
    //--------------NUMERATED_BUFFER------------
    {
      TextParameters text_parameters = {0, 0, kXOffset};
      TableParameters table_parameters_number = {1135, 140, kRawOffset, 0, 8, 1};
      TableParameters table_parameters_characteristic = {1050, 140, kRawOffset, 0, 8, 1};
      TextBlock text_block_number = {kNumofNumber, text_parameters, static_text_args};
      TextBlock text_block_characteristic = {kNumofCharacteristic, text_parameters, static_text_args};
      TextBlockTable number = {table_parameters_number, text_block_number};
      TextBlockTable characteristic = {table_parameters_characteristic, text_block_characteristic};
      numerated_buffer = {number, characteristic};
    }
    //---------------ROUNDED_BUFFER-----------
    {
      TextParameters text_parameters = {0, 0, kXOffset};
      TableParameters table_parameters_number = {1135, 410, kRawOffset, 0, 6, 1};
      TableParameters table_parameters_characteristic = {1050, 410, kRawOffset, 0, 6, 1};
      TextBlock text_block_number = {kNumofNumber, text_parameters, static_text_args};
      TextBlock text_block_characteristic = {kNumofCharacteristic, text_parameters, static_text_args};
      TextBlockTable number = {table_parameters_number, text_block_number};
      TextBlockTable characteristic = {table_parameters_characteristic, text_block_characteristic};
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
