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

};  // namespace ID