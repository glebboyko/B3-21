#pragma once

#include <wx/stattext.h>
#include <wx/wx.h>

#include <vector>

#include "backend/calc_exec/calc_exec.hpp"

namespace ID {

const uint8_t kDefaultTextSize = 13;

struct WxTextArgs {
  wxPanel* panel = nullptr;
  int id = wxID_ANY;
  char text = ' ';
  wxPoint location = wxPoint(0, 0);
  std::pair<wxFont, wxFont> font = {
      wxFont(kDefaultTextSize, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
             wxFONTWEIGHT_BOLD),
      wxFont(kDefaultTextSize, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
             wxFONTWEIGHT_BOLD)};
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

  void SetPanel(wxPanel*);

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

  void SetPanel(wxPanel*);

  std::vector<TextBlock> table;
};

struct NumberList {
  TextBlockTable number;
  TextBlockTable characteristic;
};


struct VisualisationTemplate {
  TextBlock step;
  Number main_number;
  TextBlockTable last_operations;
  TextBlock mode;
  TextBlock function_button;
  TextBlockTable program;
  NumberList numerated_buffer;
  NumberList rounded_buffer;

  VisualisationTemplate();
  void SetPanel(wxPanel*);
};
  
}  // namespace ID

