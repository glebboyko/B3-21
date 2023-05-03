#include <wx/wx.h>
#include <wx/stattext.h>
#include "backend/for_society/for_society.hpp"

class CalculatorFrame: public wxFrame {
 public:
  CalculatorFrame(const std::string& title)
      : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(700, 500)) {    // Создание панели для размещения элементов управления
    wxPanel* panel = new wxPanel(this, wxID_ANY);

    // Создание ячеек для отображения чисел
    for (int i = 0; i < 8; i++) {
      wxStaticText* text = new wxStaticText(panel, i, "0", wxPoint(i * 50, 50));
      text->SetFont(wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    }

    wxButton* button0 = new wxButton(panel, CE::ButNum0, "0", wxPoint(10, 80), wxSize(70, 70));
    wxButton* button1 = new wxButton(panel, CE::ButNum1, "1", wxPoint(90, 80), wxSize(70, 70));
    wxButton* button2 = new wxButton(panel, CE::ButNum2, "2", wxPoint(170, 80), wxSize(70, 70));
    wxButton* button3 = new wxButton(panel, CE::ButNum3, "3", wxPoint(10, 160), wxSize(70, 70));
    wxButton* button4 = new wxButton(panel, CE::ButNum4, "4", wxPoint(90, 160), wxSize(70, 70));
    wxButton* button5 = new wxButton(panel, CE::ButNum5, "5", wxPoint(170, 160), wxSize(70, 70));
    wxButton* button6 = new wxButton(panel, CE::ButNum6, "6", wxPoint(10, 240), wxSize(70, 70));
    wxButton* button7 = new wxButton(panel, CE::ButNum7, "7", wxPoint(90, 240), wxSize(70, 70));
    wxButton* button8 = new wxButton(panel, CE::ButNum8, "8", wxPoint(170, 240), wxSize(70, 70));
    wxButton* button9 = new wxButton(panel, CE::ButNum9, "9", wxPoint(10, 320), wxSize(70, 70));
    wxButton* buttonAdd = new wxButton(panel, CE::ButPlus, "+ (sin)", wxPoint(250, 80), wxSize(50, 50));
    wxButton* buttonSub = new wxButton(panel, CE::ButMinus, "- (cos)", wxPoint(250, 140), wxSize(50, 50));
    wxButton* buttonMul = new wxButton(panel, CE::ButMultiply, "* (pi)", wxPoint(250, 200), wxSize(50, 50));
    wxButton* buttonDiv = new wxButton(panel, CE::ButDivision, "/ (exp(x))", wxPoint(250, 260), wxSize(50, 50));
    wxButton* buttonClear = new wxButton(panel, CE::ButCx, "C", wxPoint(250, 320), wxSize(50, 50));

    wxButton* buttonSin = new wxButton(panel, wxID_ANY, "sin", wxPoint(10, 400), wxSize(70, 30));
    wxButton* buttonCos = new wxButton(panel, wxID_ANY, "cos", wxPoint(90, 400), wxSize(70, 30));
    wxButton* buttonExp = new wxButton(panel, wxID_ANY, "exp", wxPoint(170, 400), wxSize(70, 30));
    wxButton* buttonInvert = new wxButton(panel, wxID_ANY, "1/x", wxPoint(250, 400), wxSize(50, 30));

    wxButton* buttonAbs = new wxButton(panel, wxID_ANY, wxT("С/П"), wxPoint(10, 440), wxSize(70, 30));
    wxButton* buttonRoot = new wxButton(panel, wxID_ANY, wxT("ВП(√x)"), wxPoint(90, 440), wxSize(70, 30));
    wxButton* buttonPower = new wxButton(panel, wxID_ANY, "x^y", wxPoint(170, 440), wxSize(70, 30));
    wxButton* buttonEqual = new wxButton(panel, wxID_ANY, "=", wxPoint(250, 440), wxSize(50, 30));

    wxButton* buttonLarger = new wxButton(panel, wxID_ANY, wxT("В/О(x>=0)"), wxPoint(10, 370), wxSize(70, 30));
    wxButton* buttonSquare = new wxButton(panel, wxID_ANY, "/-/(x^2)", wxPoint(90, 370), wxSize(70, 30));
    wxButton* buttonF = new wxButton(panel, wxID_ANY, "F", wxPoint(170, 370), wxSize(70, 30));
    button0->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButton0Click, this);
    button1->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButton1Click, this);
    button2->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButton2Click, this);
    button3->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButton3Click, this);
    button4->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButton4Click, this);
    button5->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButton5Click, this);
    button6->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButton6Click, this);
    button7->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButton7Click, this);
    button8->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButton8Click, this);
    button9->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButton9Click, this);
    buttonAdd->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonAddClick, this);
    buttonSub->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonSubClick, this);
    buttonMul->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonMulClick, this);
    buttonDiv->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonDivClick, this);
    buttonClear->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonClearClick, this);
    buttonSin->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonSinClick, this);
    buttonCos->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonCosClick, this);
    buttonExp->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonExpClick, this);
    buttonInvert->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonInvertClick, this);
    buttonAbs->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonAbsClick, this);
    buttonRoot->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonRootClick, this);
    buttonPower->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonPowerClick, this);
    buttonEqual->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonEqualClick, this);
    buttonLarger->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonLargerClick, this);
    buttonSquare->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonSquareClick, this);
    buttonF->Bind(wxEVT_BUTTON, &CalculatorFrame::OnButtonFClick, this);
  }
 private:
  // Обработчики событий для кнопок
  void OnButton0Click(wxCommandEvent& event) {
    // TODO: Обработчик нажатия на кнопку

  }
  void OnButton1Click(wxCommandEvent& event) {
    // TODO: Обработчик нажатия на кнопку 1
  }

  void OnButton2Click(wxCommandEvent& event) {
  }

  void OnButton3Click(wxCommandEvent& event) {
  }

  void OnButton4Click(wxCommandEvent& event) {
  }

  void OnButton5Click(wxCommandEvent& event) {
  }

  void OnButton6Click(wxCommandEvent& event) {
  }

  void OnButton7Click(wxCommandEvent& event) {
  }

  void OnButton8Click(wxCommandEvent& event) {
  }

  void OnButton9Click(wxCommandEvent& event) {
  }

  void OnButtonAddClick(wxCommandEvent& event) {
  }

  void OnButtonSubClick(wxCommandEvent& event) {
  }

  void OnButtonMulClick(wxCommandEvent& event) {
  }
  void OnButtonDivClick(wxCommandEvent& event) {
  }
  void OnButtonClearClick(wxCommandEvent& event) {
  }

  void OnButtonSinClick(wxCommandEvent& event) {
  }
  void OnButtonCosClick(wxCommandEvent& event) {
  }
  void OnButtonExpClick(wxCommandEvent& event) {
  }
  void OnButtonInvertClick(wxCommandEvent& event) {
  }
  void OnButtonAbsClick(wxCommandEvent& event) {
  }
  void OnButtonRootClick(wxCommandEvent& event) {
  }
  void OnButtonPowerClick(wxCommandEvent& event) {
  }
  void OnButtonEqualClick(wxCommandEvent& event) {
  }
  void OnButtonLargerClick(wxCommandEvent& event) {
  }
  void OnButtonSquareClick(wxCommandEvent& event) {
  }
  void OnButtonFClick(wxCommandEvent& event) {
  }
  //// Объявление компонентов пользовательского интерфейса
  wxBoxSizer* mainSizer;
  wxGridSizer* gridSizer;
  wxStaticText* label0;
  wxStaticText* label1;
  wxStaticText* label2;
  wxStaticText* label3;
  wxStaticText* label4;
  wxStaticText* label5;
  wxStaticText* label6;
  wxStaticText* label7;
  wxButton* button0;
  wxButton* button1;
  wxButton* button2;
  wxButton* button3;
  wxButton* button4;
  wxButton* button5;
  wxButton* button6;
  wxButton* button7;
  wxButton* button8;
  wxButton* button9;
  wxButton* buttonAdd;
  wxButton* buttonSub;
  wxButton* buttonMul;
  wxButton* buttonDiv;
  wxButton* buttonClear;
  wxButton* buttonSin;
  wxButton* buttonCos;
  wxButton* buttonExp;
  wxButton* buttonInvert;
  wxButton* buttonAbs;
  wxButton* buttonRoot;
  wxButton* buttonPower;
  wxButton* buttonEqual;
  wxButton* buttonLarger;
  wxButton* buttonSquare;
  wxButton* buttonF;
};

class CalculatorApp : public wxApp {
 public:
  virtual bool OnInit() {  // Создание главного окна калькулятора
    CalculatorFrame* frame = new CalculatorFrame("Calculator");
    frame->Show(true);
    return true;
  }
};