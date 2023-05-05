#include "Window.h"

enum IDTable
{
	btnNum1 = 10001,
	btnNum2,
	btnNum3,
	btnNum4,
	btnNum5,
	btnNum6,
	btnNum7,
	btnNum8,
	btnNum9,
	btnNum0,
	btnEquals,
	btnAdd,
	btnSubtract,
	btnMultiply,
	btnDivide,
	btnMod,
	btnSIN,
	btnCOS,
	btnTAN,
	btnDecimal,
	btnNegative,
	btnBackspace,
	btnClear,
	mainTextBox
};

wxBEGIN_EVENT_TABLE(Window, wxFrame)
EVT_BUTTON(IDTable::btnNum1, Window::OnButtonClick)
EVT_BUTTON(IDTable::btnNum2, Window::OnButtonClick)
EVT_BUTTON(IDTable::btnNum3, Window::OnButtonClick)
EVT_BUTTON(IDTable::btnNum4, Window::OnButtonClick)
EVT_BUTTON(IDTable::btnNum5, Window::OnButtonClick)
EVT_BUTTON(IDTable::btnNum6, Window::OnButtonClick)
EVT_BUTTON(IDTable::btnNum7, Window::OnButtonClick)
EVT_BUTTON(IDTable::btnNum8, Window::OnButtonClick)
EVT_BUTTON(IDTable::btnNum9, Window::OnButtonClick)
EVT_BUTTON(IDTable::btnNum0, Window::OnButtonClick)
EVT_BUTTON(IDTable::btnEquals, Window::OnButtonClick)
EVT_BUTTON(IDTable::btnAdd, Window::OnButtonClick)
EVT_BUTTON(IDTable::btnSubtract, Window::OnButtonClick)
EVT_BUTTON(IDTable::btnMultiply, Window::OnButtonClick)
EVT_BUTTON(IDTable::btnDivide, Window::OnButtonClick)
EVT_BUTTON(IDTable::btnMod, Window::OnButtonClick)
EVT_BUTTON(IDTable::btnSIN, Window::OnButtonClick)
EVT_BUTTON(IDTable::btnCOS, Window::OnButtonClick)
EVT_BUTTON(IDTable::btnTAN, Window::OnButtonClick)
EVT_BUTTON(IDTable::btnDecimal, Window::OnButtonClick)
EVT_BUTTON(IDTable::btnNegative, Window::OnButtonClick)
EVT_BUTTON(IDTable::btnBackspace, Window::OnButtonClick)
EVT_BUTTON(IDTable::btnClear, Window::OnButtonClick)
wxEND_EVENT_TABLE()


Window::Window() : wxFrame(nullptr, wxID_ANY, "Main Window", wxPoint(50, 50), wxSize(300, 700))
{
	wxSize normalButtonSize = wxSize(60, 70);

	mainBox = new wxBoxSizer(wxVERTICAL);
	textBoxRow = new wxBoxSizer(wxHORIZONTAL);
	row1 = new wxBoxSizer(wxHORIZONTAL);
	row2 = new wxBoxSizer(wxHORIZONTAL);
	row3 = new wxBoxSizer(wxHORIZONTAL);
	row4 = new wxBoxSizer(wxHORIZONTAL);
	row5 = new wxBoxSizer(wxHORIZONTAL);
	row6 = new wxBoxSizer(wxHORIZONTAL);

	// The text are not the same size as the other elements
	mainTextBox = new wxTextCtrl(this, IDTable::mainTextBox, "", wxPoint(100, 100), wxSize(GetSize().x - 30, 128));

	btnEquals = new wxButton(this, IDTable::btnEquals, "=", wxPoint(350, 380), normalButtonSize);
	btnNum1 = new wxButton(this, IDTable::btnNum1, "1", wxDefaultPosition, normalButtonSize);
	btnNum2 = new wxButton(this, IDTable::btnNum2, "2", wxDefaultPosition, normalButtonSize);
	btnNum3 = new wxButton(this, IDTable::btnNum3, "3", wxDefaultPosition, normalButtonSize);
	btnNum4 = new wxButton(this, IDTable::btnNum4, "4", wxDefaultPosition, normalButtonSize);
	btnNum5 = new wxButton(this, IDTable::btnNum5, "5", wxDefaultPosition, normalButtonSize);
	btnNum6 = new wxButton(this, IDTable::btnNum6, "6", wxDefaultPosition, normalButtonSize);
	btnNum7 = new wxButton(this, IDTable::btnNum7, "7", wxDefaultPosition, normalButtonSize);
	btnNum8 = new wxButton(this, IDTable::btnNum8, "8", wxDefaultPosition, normalButtonSize);
	btnNum9 = new wxButton(this, IDTable::btnNum9, "9", wxDefaultPosition, normalButtonSize);
	btnNum0 = new wxButton(this, IDTable::btnNum0, "0", wxDefaultPosition, normalButtonSize);
	btnAdd = new wxButton(this, IDTable::btnAdd, "+", wxDefaultPosition, normalButtonSize);
	btnSubtract = new wxButton(this, IDTable::btnSubtract, "-", wxDefaultPosition, normalButtonSize);
	btnMultiply = new wxButton(this, IDTable::btnMultiply, "*", wxDefaultPosition, normalButtonSize);
	btnDivide = new wxButton(this, IDTable::btnDivide, "/", wxDefaultPosition, normalButtonSize);
	btnMod = new wxButton(this, IDTable::btnMod, "%", wxDefaultPosition, normalButtonSize);
	btnSIN = new wxButton(this, IDTable::btnSIN, "SiN", wxDefaultPosition, normalButtonSize);
	btnCOS = new wxButton(this, IDTable::btnCOS, "COS", wxDefaultPosition, normalButtonSize);
	btnTAN = new wxButton(this, IDTable::btnTAN, "TAN", wxDefaultPosition, normalButtonSize);
	btnDecimal = new wxButton(this, IDTable::btnDecimal, ".", wxDefaultPosition, normalButtonSize);
	btnNegative = new wxButton(this, IDTable::btnNegative, "neg", wxDefaultPosition, normalButtonSize);
	btnBackspace = new wxButton(this, IDTable::btnBackspace, "<-", wxDefaultPosition, normalButtonSize);
	btnClear = new wxButton(this, IDTable::btnClear, "C", wxDefaultPosition, normalButtonSize);

	int spacerSize = GetSize().x / 25;

	mainBox->AddSpacer(spacerSize);

	textBoxRow->AddSpacer(spacerSize);
	textBoxRow->Add(mainTextBox);
	mainBox->Add(textBoxRow);

	row1->AddSpacer(10);
	row1->Add(btnSIN);
	row1->AddSpacer(spacerSize);
	row1->Add(btnCOS);
	row1->AddSpacer(spacerSize);
	row1->Add(btnTAN);
	row1->AddSpacer(spacerSize);
	row1->Add(btnMultiply);
	row1->AddSpacer(10);
	mainBox->AddSpacer(10);
	mainBox->Add(row1);

	row2->AddSpacer(10);
	row2->Add(btnDecimal);
	row2->AddSpacer(spacerSize);
	row2->Add(btnNegative);
	row2->AddSpacer(spacerSize);
	row2->Add(btnMod);
	row2->AddSpacer(spacerSize);
	row2->Add(btnDivide);
	row2->AddSpacer(10);
	mainBox->AddSpacer(10);
	mainBox->Add(row2);

	row3->AddSpacer(10);
	row3->Add(btnNum7);
	row3->AddSpacer(spacerSize);
	row3->Add(btnNum8);
	row3->AddSpacer(spacerSize);
	row3->Add(btnNum9);
	row3->AddSpacer(spacerSize);
	row3->Add(btnSubtract);
	row3->AddSpacer(10);
	mainBox->AddSpacer(10);
	mainBox->Add(row3);

	row4->AddSpacer(10);
	row4->Add(btnNum4);
	row4->AddSpacer(spacerSize);
	row4->Add(btnNum5);
	row4->AddSpacer(spacerSize);
	row4->Add(btnNum6);
	row4->AddSpacer(spacerSize);
	row4->Add(btnAdd);
	row4->AddSpacer(10);
	mainBox->AddSpacer(10);
	mainBox->Add(row4);

	row5->AddSpacer(10);
	row5->Add(btnNum1);
	row5->AddSpacer(spacerSize);
	row5->Add(btnNum2);
	row5->AddSpacer(spacerSize);
	row5->Add(btnNum3);
	row5->AddSpacer(spacerSize);
	row5->Add(btnEquals);
	row5->AddSpacer(10);
	mainBox->AddSpacer(10);
	mainBox->Add(row5);

	row6->AddSpacer(10);
	row6->Add(btnClear);
	row6->AddSpacer(spacerSize);
	row6->Add(btnNum0);
	row6->AddSpacer(spacerSize);
	row6->Add(btnBackspace);
	row6->AddSpacer(10);
	mainBox->AddSpacer(10);
	mainBox->Add(row6);
	mainBox->AddSpacer(10);

	SetSizerAndFit(mainBox);
}

void Window::OnButtonClick(wxCommandEvent& _event)
{

}
