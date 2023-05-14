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
  TextBlock step = TextBlock(0, {0, 0, 0}, {nullptr, wxID_ANY, ' ', {}, {}});
  Number main_number = Number({CN::kNumOfDigits + 1, {0, 0, 0}, {nullptr, wxID_ANY, ' ', {}, {}}}, {CN::kNumOfCharacteristic + 1, {0, 0, 0}, {nullptr, wxID_ANY, ' ', {}, {}}});
  TextBlockTable last_operations = TextBlockTable({0, 0, 0, 0, 0, 0}, {CN::kNumOfCharacteristic, {0, 0, 0}, {nullptr, wxID_ANY, ' ', {}, {}}});
  TextBlock mode = TextBlock(kNumofModes, {0, 0, 0}, {nullptr, wxID_ANY, ' ', {}, {}});
  TextBlock function_button = TextBlock(kNumofFb, {0, 0, 0}, {nullptr, wxID_ANY, ' ', {}, {}});
  TextBlockTable program = TextBlockTable({0, 0, 0, 0, 0, 0}, {CN::kNumOfCharacteristic, {0, 0, 0}, {nullptr, wxID_ANY, ' ', {}, {}}});
  NumberList numerated_buffer = {{0, 0, 0, 0, 0, 0}, {CN::kNumOfDigits, {0, 0, 0}, {nullptr, wxID_ANY, ' ', {}, {}}}, {0, 0, 0, 0, 0, 0}, {CN::kNumOfCharacteristic, {0, 0, 0}, {nullptr, wxID_ANY, ' ', {}, {}}}};
  NumberList rounded_buffer = {{0, 0, 0, 0, 0, 0}, {CN::kNumOfDigits, {0, 0, 0}, {nullptr, wxID_ANY, ' ', {}, {}}}, {0, 0, 0, 0, 0, 0}, {CN::kNumOfCharacteristic, {0, 0, 0}, {nullptr, wxID_ANY, ' ', {}, {}}}};};

}  // namespace ID