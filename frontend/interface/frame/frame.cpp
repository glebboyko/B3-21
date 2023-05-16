#include "frame.hpp"

enum WxIds { IdMakeBackUp = 1, IdLoadFromBackUp, IdSaveProgram, IdLoadProgram };

ID::VisualisationTemplate IF::CalculatorFrame::GetTemplate() const {
  return visual_template_;
}

IF::CalculatorFrame::CalculatorFrame(const std::string& title,
                                     std::shared_ptr<CE::Calc> calc)
    : wxFrame(NULL, CE::ButNum2, title, wxDefaultPosition, wxSize(1361, 800)) {
  wxPanel* panel = new wxPanel(this, wxID_ANY);

  wxInitAllImageHandlers();
  wxImage pict1(wxT("images/interface.png"), wxBITMAP_TYPE_PNG);
  wxBitmap backgroundBitmap(pict1);
  wxStaticBitmap* background = new wxStaticBitmap(this, wxID_ANY, backgroundBitmap, wxDefaultPosition, wxSize(1361, 800));


  wxMenuBar* menu_bar = new wxMenuBar();
  wxMenu* backup_menu = new wxMenu();
  wxMenu* program_menu = new wxMenu();

  backup_menu->Append(IdMakeBackUp, _("&Создать резервную копию"));
  backup_menu->Append(IdLoadFromBackUp, _("&Восстановить из резервной копии"));

  program_menu->Append(IdSaveProgram, _("&Сохранить программу"));
  program_menu->Append(IdLoadProgram, _("&Загрузить программу"));

  menu_bar->Append(backup_menu, _("&Резервная копия"));
  menu_bar->Append(program_menu, _("&Программа"));

  SetMenuBar(menu_bar);
  Bind(wxEVT_MENU, &CalculatorFrame::MakeBackUp, this, IdMakeBackUp);
  Bind(wxEVT_MENU, &CalculatorFrame::LoadFromBackUp, this, IdLoadFromBackUp);
  Bind(wxEVT_MENU, &CalculatorFrame::SaveProgram, this, IdSaveProgram);
  Bind(wxEVT_MENU, &CalculatorFrame::LoadProgram, this, IdLoadProgram);

  const wxSize BUTTON_SIZE(39, 36);

  wxButton* button0 =
      new wxButton(background, CE::ButNum0, "0", wxPoint(151, 655), BUTTON_SIZE);
  wxButton* button1 =
      new wxButton(background, CE::ButNum1, "1", wxPoint(151, 603), BUTTON_SIZE);
  wxButton* button2 =
      new wxButton(background, CE::ButNum2, "2", wxPoint(200, 603), BUTTON_SIZE);
  wxButton* button3 =
      new wxButton(background, CE::ButNum3, "3", wxPoint(250, 603), BUTTON_SIZE);
  wxButton* button4 =
      new wxButton(background, CE::ButNum4, "4", wxPoint(151, 550), BUTTON_SIZE);
  wxButton* button5 =
      new wxButton(background, CE::ButNum5, "5", wxPoint(200, 550), BUTTON_SIZE);
  wxButton* button6 =
      new wxButton(background, CE::ButNum6, "6", wxPoint(250, 550), BUTTON_SIZE);
  wxButton* button7 =
      new wxButton(background, CE::ButNum7, "7", wxPoint(151, 497), BUTTON_SIZE);
  wxButton* button8 =
      new wxButton(background, CE::ButNum8, "8", wxPoint(200, 497), BUTTON_SIZE);
  wxButton* button9 =
      new wxButton(background, CE::ButNum9, "9", wxPoint(250, 497), BUTTON_SIZE);

  wxButton* buttonPlus =
      new wxButton(background, CE::ButPlus, "+", wxPoint(347, 550), BUTTON_SIZE);
  wxButton* buttonMin =
      new wxButton(background, CE::ButMinus, "-", wxPoint(347, 603), BUTTON_SIZE);
  wxButton* buttonMul =
      new wxButton(background, CE::ButMultiply, "*", wxPoint(300, 550), BUTTON_SIZE);
  wxButton* buttonDiv =
      new wxButton(background, CE::ButDivision, "/", wxPoint(300, 603), BUTTON_SIZE);
  wxButton* buttonCx =
      new wxButton(background, CE::ButCx, "Cx", wxPoint(250, 444), BUTTON_SIZE);

  wxButton* buttonP =
      new wxButton(background, CE::ButP, "P", wxPoint(200, 444), BUTTON_SIZE);
  wxButton* buttonNull =
      new wxButton(background, CE::ButNull, "Null", wxPoint(151, 284), BUTTON_SIZE);
  wxButton* buttonArrowUp = new wxButton(background, CE::ButArrowUp, "ArrowUp",
                                         wxPoint(347, 497), BUTTON_SIZE);
  wxButton* buttonXArrowY = new wxButton(background, CE::ButXArrowY, "XArrowY",
                                         wxPoint(300, 497), BUTTON_SIZE);

  wxButton* buttonCP = new wxButton(background, CE::ButCP, wxT("С/П"),
                                    wxPoint(347, 391), BUTTON_SIZE);
  wxButton* buttonBvP = new wxButton(background, CE::ButBvP, wxT("ВП"),
                                     wxPoint(300, 655), BUTTON_SIZE);
  wxButton* buttonXExpY =
      new wxButton(background, CE::ButXExpY, "x^y", wxPoint(250, 444), BUTTON_SIZE);
  wxButton* buttonF =
      new wxButton(background, CE::ButF, "F", wxPoint(347, 655), BUTTON_SIZE);

  wxButton* buttonComma = new wxButton(background, CE::ButComma, wxT(","),
                                       wxPoint(200, 655), BUTTON_SIZE);
  wxButton* buttonBO = new wxButton(background, CE::ButBO, wxT("В/О"),
                                    wxPoint(300, 391), BUTTON_SIZE);
  wxButton* buttonPrefixMinus = new wxButton(background, CE::ButPrefixMinus, "/-/",
                                             wxPoint(250, 655), BUTTON_SIZE);
  wxButton* buttonBbP =
      new wxButton(background, CE::ButBbP, "БП", wxPoint(300, 444), BUTTON_SIZE);

  wxButton* buttonPP =
      new wxButton(background, CE::ButPP, wxT("PP"), wxPoint(347, 444), BUTTON_SIZE);
  wxButton* buttonStepLeft = new wxButton(background, CE::ButStepLeft, wxT("<-"),
                                          wxPoint(250, 391), BUTTON_SIZE);
  wxButton* buttonStepRight = new wxButton(background, CE::ButStepRight, wxT("->"),
                                           wxPoint(200, 391), BUTTON_SIZE);

  button0->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
  button1->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
  button2->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
  button3->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
  button4->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
  button5->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
  button6->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
  button7->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
  button8->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
  button9->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);

  buttonPlus->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
  buttonMin->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
  buttonMul->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
  buttonDiv->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
  buttonCx->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);

  buttonP->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
  buttonNull->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
  buttonArrowUp->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
  buttonXArrowY->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);

  buttonCP->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
  buttonBvP->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
  buttonXExpY->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
  buttonF->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);

  buttonComma->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
  buttonBO->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
  buttonPrefixMinus->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
  buttonBbP->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);

  buttonPP->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
  buttonStepLeft->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
  buttonStepRight->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);

  visual_template_.SetPanel(background);
  calc_ = calc;
}