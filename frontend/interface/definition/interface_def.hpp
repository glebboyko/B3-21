#pragma once

#include <wx/stattext.h>
#include <wx/wx.h>

#include <vector>

#include "backend/calc_exec/calc_exec.hpp"

namespace ID {

const uint8_t kDefaultTextSize = 16;

struct WxTextArgs {
  wxPanel* panel = nullptr;
  int id = wxID_ANY;
  char text = ' ';
  wxPoint location = wxPoint(0, 0);
  wxFont font = wxFont(kDefaultTextSize, wxFONTFAMILY_DEFAULT,
                       wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
};

struct TextParameters {
  int32_t init_x;
  int32_t init_y;
  int32_t x_offset;
};

struct TextBlock {
  TextBlock() = default;
  TextBlock(uint8_t size, TextParameters parameters, WxTextArgs other_args);

  std::vector<WxTextArgs> object;
};

struct Number {
  TextBlock number;
  TextBlock characteristic;
};

struct VerticalTextBlockList {
  VerticalTextBlockList() = default;
  VerticalTextBlockList(uint8_t size, int32_t y_offset,
                        TextBlock template_block);

  std::vector<TextBlock> list;
};

struct TextBlockTable {
  TextBlockTable() = default;
  TextBlockTable(uint8_t number_of_columns, int32_t column_y_offset,
                 VerticalTextBlockList template_list);

  std::vector<VerticalTextBlockList> columns;
};

struct VerticalNumberList {
  VerticalTextBlockList number;
  VerticalTextBlockList characteristic;
};

const uint8_t kNumOfPrevOperations = 3;
struct VisualisationTemplate {
  TextBlock step = TextBlock(/*Shoislom*/);
  TextBlock main_number = TextBlock(/*Shoislom*/);
  VerticalTextBlockList last_operations = VerticalTextBlockList(/*Shoislom*/);
  TextBlock mode = TextBlock(/*Shoislom*/);
  TextBlock function_button = TextBlock(/*Shoislom*/);
  TextBlockTable program = TextBlockTable(/*Shoislom*/);
  VerticalNumberList numerated_buffer = {/*Shoislom*/};
  VerticalNumberList rounded_buffer = {/*Shoislom*/};
};

}  // namespace ID