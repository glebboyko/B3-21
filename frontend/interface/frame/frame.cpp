#include "frame.hpp"

enum WxIds { IdMakeBackUp = 1, IdLoadFromBackUp, IdSaveProgram, IdLoadProgram };

IF::CalculatorFrame::GetTemplate() const {
    return visual_template_;
}

IF::CalculatorFrame::CalculatorFrame(const std::string& title, std::shared_ptr<CE::Calc> calc): wxFrame(NULL, CE::ButNum2, title, wxDefaultPosition, wxSize(700, 500)) {
    wxPanel* panel = new wxPanel(this, wxID_ANY);

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

    const wxSize BUTTON_SIZE(70, 70);

    wxButton* button0 = new wxButton(panel, CE::ButNum0, "0", wxPoint(10, 80), BUTTON_SIZE);
    wxButton* button1 = new wxButton(panel, CE::ButNum1, "1", wxPoint(90, 80), BUTTON_SIZE);
    wxButton* button2 = new wxButton(panel, CE::ButNum2, "2", wxPoint(170, 80), BUTTON_SIZE);
    wxButton* button3 = new wxButton(panel, CE::ButNum3, "3", wxPoint(10, 160), BUTTON_SIZE);
    wxButton* button4 = new wxButton(panel, CE::ButNum4, "4", wxPoint(90, 160), BUTTON_SIZE);
    wxButton* button5 = new wxButton(panel, CE::ButNum5, "5", wxPoint(170, 160), BUTTON_SIZE);
    wxButton* button6 = new wxButton(panel, CE::ButNum6, "6", wxPoint(10, 240), BUTTON_SIZE);
    wxButton* button7 = new wxButton(panel, CE::ButNum7, "7", wxPoint(90, 240), BUTTON_SIZE);
    wxButton* button8 = new wxButton(panel, CE::ButNum8, "8", wxPoint(170, 240), BUTTON_SIZE);
    wxButton* button9 = new wxButton(panel, CE::ButNum9, "9", wxPoint(10, 320), BUTTON_SIZE);
    
    wxButton* buttonPlus = new wxButton(panel, CE::ButPlus, "+", wxPoint(250, 80), BUTTON_SIZE);
    wxButton* buttonMin = new wxButton(panel, CE::ButMinus, "-", wxPoint(250, 140), BUTTON_SIZE);
    wxButton* buttonMul = new wxButton(panel, CE::ButMultiply, "*", wxPoint(250, 200), BUTTON_SIZE);
    wxButton* buttonDiv = new wxButton(panel, CE::ButDivision, "/", wxPoint(250, 260), BUTTON_SIZE);
    wxButton* buttonCx = new wxButton(panel, CE::ButCx, "C", wxPoint(250, 320), BUTTON_SIZE);

    wxButton* buttonP = new wxButton(panel, CE::ButP, "P", wxPoint(10, 400), BUTTON_SIZE);
    wxButton* buttonNull = new wxButton(panel, CE::ButNull, "Null", wxPoint(90, 400), BUTTON_SIZE);
    wxButton* buttonArrowUp = new wxButton(panel, CE::ButArrowUp, "ArrowUp", wxPoint(170, 400), BUTTON_SIZE);
    wxButton* buttonXArrowY = new wxButton(panel, CE::ButXArrowY, "XArrowUp", wxPoint(250, 400), BUTTON_SIZE);

    wxButton* buttonCP = new wxButton(panel, CE::ButCP, wxT("С/П"), wxPoint(10, 440), BUTTON_SIZE);
    wxButton* buttonBvP = new wxButton(panel, CE::ButBvP, wxT("ВП"), wxPoint(90, 440), BUTTON_SIZE);
    wxButton* buttonXExpY = new wxButton(panel, CE::ButXExpY, "x^y", wxPoint(170, 440), BUTTON_SIZE);
    wxButton* buttonF = new wxButton(panel, CE::ButF, "F", wxPoint(170, 370), BUTTON_SIZE);
    
    wxButton* buttonComma = new wxButton(panel, CE::ButComma, wxT(","), wxPoint(10, 440), BUTTON_SIZE);
    wxButton* buttonBO = new wxButton(panel, CE::ButBO, wxT("В|О"), wxPoint(90, 440), BUTTON_SIZE);
    wxButton* buttonPrefixMinus = new wxButton(panel, CE::ButPrefixMinus, "/-/", wxPoint(170, 440), BUTTON_SIZE);
    wxButton* buttonBbP = new wxButton(panel, CE::ButBbP, "БП", wxPoint(170, 370), BUTTON_SIZE);

    wxButton* buttonPP = new wxButton(panel, CE::ButPP, wxT("PP"), wxPoint(10, 440), BUTTON_SIZE);
    wxButton* buttonStepLeft = new wxButton(panel, CE::ButStepLeft, wxT("<-"), wxPoint(90, 440), BUTTON_SIZE);
    wxButton* buttonStepRight = new wxButton(panel, CE::ButStepRight, "->", wxPoint(170, 440), BUTTON_SIZE);


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

    buttonCp->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
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

    visual_template_.SetPanel(panel);
    calc_ = calc; 
}