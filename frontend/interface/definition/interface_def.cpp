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
    const int32_t kRawOffset = 10;
  
    WxTextArgs static_text_args;
    static_text_args.font = {};
    
    //---------PROGRAM------------
    {
      TableParameters table_parameters = {0, 0, kRawOffset, 100, 20, 3};
      TextBlock text_block(kTableSize, {0, 0, kXOffset}, static_text_args);
      program = TextBlockTable(table_parameters, text_block);
    }
    //--------STEP-----------
    {
      TextParameters parameters = {0, 0, kXOffset};
      step = TextBlock(kTableSize, parameters, static_text_args);
    }
    //----------MAIN_NUMBER---------
    {
      TextParameters parameters = {0, 0, kXOffset};
      TextBlock number(kTableSize, parameters, static_text_args);
      TextBlock characteristic(kTableSize, parameters, static_text_args);
      main_number = {number, characteristic};
    }
    //-------------LAST_OPERATIONS-------------
    {
      TextParameters text_parameters = {/* Shoislom */};
      TableParameters parameters = {0, 0, kRawOffset, 0, 0, 0};
      TextBlock text_block(kTableSize, text_parameters, static_text_args);
      last_operations = TextBlockTable(parameters, text_block);
    }
    //-------------MODE-------------
    {
      TextParameters parameters = {0, 0, kXOffset};
      mode = TextBlock(kTableSize, parameters, static_text_args);
    }
    //------------FUNCTION_BUTTON------------
    {
      TextParameters parameters = {0, 0, kXOffset};
      function_button = TextBlock(kTableSize, parameters, static_text_args);
    }
    //--------------NUMERATED_BUFFER------------
    {
      TextParameters text_parameters = {/* Shoislom */};
      TableParameters parameters = {0, 0, kXOffset};
      TextBlock text_block = {kTableSize, text_parameters, static_text_args};
      TextBlockTable number = {parameters, text_block};
      TextBlockTable characteristic = {parameters, text_block};
      numerated_buffer = {number, characteristic};
    }
    //---------------ROUNDED_BUFFER-----------
    {
      TextParameters text_parameters = {/* Shoislom */};
      TableParameters parameters = {0, 0, kXOffset};
      TextBlock text_block = {kTableSize, text_parameters, static_text_args};
      TextBlockTable number = {parameters, text_block};
      TextBlockTable characteristic = {parameters, text_block};
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