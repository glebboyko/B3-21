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

struct TableParameters {
  int32_t init_x;
  int32_t init_y;

  int32_t raw_offset;
  int32_t column_offset;

  uint8_t raw_num;
  uint8_t column_num;
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

struct TextBlockTable {
  TextBlockTable() = default;
  TextBlockTable(TableParameters table_parameters,
                 TextBlock template_text_block);

  std::vector<TextBlock> table;
};

struct NumberList {
  TextBlockTable number;
  TextBlockTable characteristic;
};

const uint8_t kNumOfPrevOperations = 3;
struct VisualisationTemplate {
  TextBlock step = TextBlock(/*Shoislom*/);
  Number main_number = TextBlock(/*Shoislom*/);
  TextBlockTable last_operations = TextBlockTable(/*Shoislom*/);
  TextBlock mode = TextBlock(/*Shoislom*/);
  TextBlock function_button = TextBlock(/*Shoislom*/);
  TextBlockTable program = TextBlockTable(/*Shoislom*/);
  NumberList numerated_buffer = {/*Shoislom*/};
  NumberList rounded_buffer = {/*Shoislom*/};
};

}  // namespace ID