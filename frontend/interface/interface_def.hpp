#include <wx/wx.h>
#include <wx/stattext.h>
#include "backend/for_society/for_society.hpp"
#include "backend/calc_exec/calc_exec.hpp"
#include <vector>

void PrintCalc(const CE::Calc& calc) {
  std::cout << "Program:\n";
  for (int i = 0; i < CP::kProgBufferSize; ++i) {
    printf("%3d ", FS::FromNotToNot<10, 6>(i));
  }
  printf("\n");
  for (int i = 0; i < CP::kProgBufferSize; ++i) {
    printf("%3d ", calc.GetProgram().GetProgram()[i]);
  }
  std::cout << "\nSteps: "
            << FS::FromNotToNot<10, 6>(calc.GetProgram().GetStep());
  std::cout << "\nTransfer status: ";
  switch (calc.GetProgram().GetTransferStatus()) {
    case CP::TsTransfer:
      std::cout << "condition is not met - transfer\n";
      break;
    case CP::TsNoTransfer:
      std::cout << "condition is met - no transfer\n";
      break;
    case CP::TsUnconditionalTransfer:
      std::cout << "transfer\n";
    default:
      std::cout << "no command\n";
  }

  std::cout << "\nNumber buffer:\n";
  std::cout << "Numerated buffer:\n";
  for (int i = 0; i < CM::kNumeratedBuffSize; ++i) {
    auto [sign, characteristic, num] =
        calc.GetRegisterBuffer().GetNumeratedBuffer()[i].GetNumber();
    printf("%d. %d %c%s\n", i, characteristic, (sign ? '-' : ' '), num.c_str());
  }
  std::cout << "Rounded buffer\n";
  for (int i = 0; i < CM::kRoundedBuffSize - 1; ++i) {
    auto [sign, characteristic, num] =
        calc.GetRegisterBuffer().GetRoundedBuffer()[i].GetNumber();
    printf("%d. %d %c%s\n", i, characteristic, (sign ? '-' : ' '), num.c_str());
  }

  std::cout << "\nFunction Button: ";
  switch (calc.GetCurrFuncButton()) {
    case CE::ButP:
      std::cout << "P\n";
      break;
    case CE::ButF:
      std::cout << "F\n";
      break;
    default:
      std::cout << "NULL\n";
  }

  std::cout << "\nMode: ";
  switch (calc.GetMode()) {
    case CE::Working:
      std::cout << "working\n";
      break;
    case CE::Programming:
      std::cout << "programming\n";
      break;
    case CE::ExecutingProg:
      std::cout << "executing program\n";
      break;
    default:
      std::cout << "turned off\n";
  }
}

class CalculatorFrame: public wxFrame {
 public:
  CalculatorFrame(const std::string& title, CE::Calc* calc)
      : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(700, 500)), calc_(calc) {    // Создание панели для размещения элементов управления
    PrintCalc(*calc_);

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

    wxButton* button_on_off = new wxButton(panel, CE::ButNull, "Switch", wxPoint(10, 400), wxSize(70, 30));
    /*wxButton* buttonSin = new wxButton(panel, wxID_ANY, "sin", wxPoint(10, 400), wxSize(70, 30));
    wxButton* buttonCos = new wxButton(panel, wxID_ANY, "cos", wxPoint(90, 400), wxSize(70, 30));
    wxButton* buttonExp = new wxButton(panel, wxID_ANY, "exp", wxPoint(170, 400), wxSize(70, 30));
    wxButton* buttonInvert = new wxButton(panel, wxID_ANY, "1/x", wxPoint(250, 400), wxSize(50, 30));

    wxButton* buttonAbs = new wxButton(panel, wxID_ANY, wxT("С/П"), wxPoint(10, 440), wxSize(70, 30));
    wxButton* buttonRoot = new wxButton(panel, wxID_ANY, wxT("ВП(√x)"), wxPoint(90, 440), wxSize(70, 30));
    wxButton* buttonPower = new wxButton(panel, wxID_ANY, "x^y", wxPoint(170, 440), wxSize(70, 30));
    wxButton* buttonEqual = new wxButton(panel, wxID_ANY, "=", wxPoint(250, 440), wxSize(50, 30));

    wxButton* buttonLarger = new wxButton(panel, wxID_ANY, wxT("В/О(x>=0)"), wxPoint(10, 370), wxSize(70, 30));
    wxButton* buttonSquare = new wxButton(panel, wxID_ANY, "/-/(x^2)", wxPoint(90, 370), wxSize(70, 30));*/
    wxButton* buttonP = new wxButton(panel, CE::ButP, "P", wxPoint(170, 370), wxSize(70, 30));
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
    buttonAdd->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
    buttonSub->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
    buttonMul->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
    buttonDiv->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
    buttonClear->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
    button_on_off->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
    /*buttonCos->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
    buttonExp->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
    buttonInvert->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
    buttonAbs->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
    buttonRoot->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
    buttonPower->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
    buttonEqual->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
    buttonLarger->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
    buttonSquare->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);*/
    buttonP->Bind(wxEVT_BUTTON, &CalculatorFrame::ButtonClick, this);
  }
 private:

  CE::Calc* calc_;
  // Обработчики событий для кнопок
  void ButtonClick(wxCommandEvent& event) {
    if (event.GetId() == CE::ButNull) {
      calc_->TurnOnOff();
    }
    else {
      calc_->PressButton(static_cast<CE::Button>(event.GetId()));
    }
    PrintCalc(*calc_);
  }
  void OnButton0Click(wxCommandEvent& event) {}
  void OnButton1Click(wxCommandEvent& event) {
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
 /* wxBoxSizer* mainSizer;
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
  wxButton* buttonF;*/
};

class CalculatorApp : public wxApp {
 public:
  virtual bool OnInit() {  // Создание главного окна калькулятора
    CE::Calc* calc = new CE::Calc();

    CalculatorFrame* frame = new CalculatorFrame("Calculator", calc);
    frame->Show(true);
    return true;
  }
};