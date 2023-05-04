#pragma once

#include <wx/stattext.h>
#include <wx/wx.h>

#include <memory>
#include <vector>

#include "backend/calc_exec/calc_exec.hpp"
#include "backend/for_society/for_society.hpp"

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
  TextBlock(uint8_t size, TextParameters parameters, WxTextArgs other_args) {
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

  std::vector<WxTextArgs> object;
};

struct Number {
  TextBlock number;
  TextBlock characteristic;
};

struct VerticalTextBlockList {
  VerticalTextBlockList() = default;
  VerticalTextBlockList(uint8_t size, int32_t y_offset,
                        TextBlock template_block) {
    list.resize(size);
    for (uint8_t i = 0; i < size; ++i) {
      list[i] = template_block;
      for (auto atom : list[i].object) {
        atom.location.y += i * y_offset;
      }
    }
  }
  std::vector<TextBlock> list;
};

const uint8_t kNumOfPrevOperations = 3;
struct InterfaceObjects {
  TextBlock step = TextBlock(/*Shoislom*/);
  TextBlock main_number = TextBlock(/*Shoislom*/);
  std::vector<TextBlock> last_operations = {/*Shoislom*/};
  TextBlock mode = TextBlock(/*Shoislom*/);
  TextBlock function_button = TextBlock(/*Shoislom*/);
  VerticalTextBlockList program = VerticalTextBlockList(/*Shoislom*/);
  VerticalTextBlockList numerated_buffer = VerticalTextBlockList(/*Shoislom*/);
  VerticalTextBlockList rounded_buffer = VerticalTextBlockList(/*Shoislom*/);
};

class CalculatorFrame : public wxFrame {
 public:
  CalculatorFrame(const std::string& title, std::shared_ptr<CE::Calc> calc);
  ~CalculatorFrame() = default;

 private:
  std::shared_ptr<CE::Calc> calc_;
  // Обработчики событий для кнопок
  void ButtonClick(wxCommandEvent& event);
};

}  // namespace ID