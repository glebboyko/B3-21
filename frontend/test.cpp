#include <wx/wx.h>

class MyFrame : public wxFrame
{
 public:
  MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
 private:
  wxTextCtrl* m_textCtrl;
};

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
  // Создаем кнопки от 0 до 9
  wxButton* button0 = new wxButton(this, wxID_ANY, wxT("0"), wxPoint(50, 300), wxSize(50, 50));
  wxButton* button1 = new wxButton(this, wxID_ANY, wxT("1"), wxPoint(50, 200), wxSize(50, 50));
  wxButton* button2 = new wxButton(this, wxID_ANY, wxT("2"), wxPoint(125, 200), wxSize(50, 50));
  wxButton* button3 = new wxButton(this, wxID_ANY, wxT("3"), wxPoint(200, 200), wxSize(50, 50));
  wxButton* button4 = new wxButton(this, wxID_ANY, wxT("4"), wxPoint(50, 125), wxSize(50, 50));
  wxButton* button5 = new wxButton(this, wxID_ANY, wxT("5"), wxPoint(125, 125), wxSize(50, 50));
  wxButton* button6 = new wxButton(this, wxID_ANY, wxT("6"), wxPoint(200, 125), wxSize(50, 50));
  wxButton* button7 = new wxButton(this, wxID_ANY, wxT("7"), wxPoint(50, 50), wxSize(50, 50));
  wxButton* button8 = new wxButton(this, wxID_ANY, wxT("8"), wxPoint(125, 50), wxSize(50, 50));
  wxButton* button9 = new wxButton(this, wxID_ANY, wxT("9"), wxPoint(200, 50), wxSize(50, 50));

  // Создаем кнопки операций
  wxButton* buttonPlus = new wxButton(this, wxID_ANY, wxT("+"), wxPoint(275, 300), wxSize(50, 50));
  wxButton* buttonMinus = new wxButton(this, wxID_ANY, wxT("-"), wxPoint(275, 200), wxSize(50, 50));
  wxButton* buttonMultiply = new wxButton(this, wxID_ANY, wxT("*"), wxPoint(275, 125), wxSize(50, 50));
  wxButton* buttonDivide = new wxButton(this, wxID_ANY, wxT("/"), wxPoint(275, 50), wxSize(50, 50));
  wxButton* buttonEquals = new wxButton(this, wxID_ANY, wxT("="), wxPoint(200, 300), wxSize(50, 50));
  m_textCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxPoint(50, 25), wxSize(200, 25));
}

class MyApp : public wxApp
{
 public:
  virtual bool OnInit();
};

bool MyApp::OnInit()
{
  MyFrame* frame = new MyFrame(wxT("calculator"), wxPoint(50, 50), wxSize(400, 400));
  frame->Show(true);
  return true;
}

IMPLEMENT_APP(MyApp);
