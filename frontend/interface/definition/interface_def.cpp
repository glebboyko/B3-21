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

VerticalTextBlockList::VerticalTextBlockList(uint8_t size, int32_t y_offset,
                                             ID::TextBlock template_block) {
  list.resize(size);
  for (uint8_t i = 0; i < size; ++i) {
    list[i] = template_block;
    for (auto& atom : list[i].object) {
      atom.location.y += i * y_offset;
    }
  }
}

TextBlockTable::TextBlockTable(uint8_t number_of_columns,
                               int32_t column_y_offset,
                               ID::VerticalTextBlockList template_list) {
  columns.resize(number_of_columns);
  for (uint8_t i = 0; i < number_of_columns; ++i) {
    columns[i] = template_list;
    for (auto& block : columns[i].list) {
      for (auto& atom : block.object) {
        atom.location.y += i * column_y_offset;
      }
    }
  }
}

};  // namespace ID