#pragma once

#include <wx/stattext.h>
#include <wx/wx.h>

#include <string>
#include <vector>

#include "backend/calc_exec/calc_exec.hpp"

namespace ID {

const uint32_t kDefaultTextSize = 13;

struct TableParameters {
  int32_t init_x;
  int32_t init_y;

  int32_t raw_offset;
  int32_t column_offset;

  uint32_t raw_num;
  uint32_t column_num;
};

struct TextBlock {
  wxPanel* panel = nullptr;
  int id = wxID_ANY;
  std::string text;
  wxPoint location = wxPoint(0, 0);
  std::pair<wxFont, wxFont> font = {
      wxFont(kDefaultTextSize, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
             wxFONTWEIGHT_BOLD),
      wxFont(kDefaultTextSize, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
             wxFONTWEIGHT_BOLD)};
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
