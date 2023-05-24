#include "ButtonFactory.h"
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

void ButtonFactory::CreateButtons(wxWindow* _parentPTR, std::vector<wxButton*>& _vecButtons, wxSize& _buttonSize)
{
	_vecButtons[1] = new wxButton(_parentPTR, IDTable::btnNum1, "1", wxDefaultPosition, _buttonSize);
	_vecButtons[2] = new wxButton(_parentPTR, IDTable::btnNum2, "2", wxDefaultPosition, _buttonSize);
	_vecButtons[3] = new wxButton(_parentPTR, IDTable::btnNum3, "3", wxDefaultPosition, _buttonSize);
	_vecButtons[4] = new wxButton(_parentPTR, IDTable::btnNum4, "4", wxDefaultPosition, _buttonSize);
	_vecButtons[5] = new wxButton(_parentPTR, IDTable::btnNum5, "5", wxDefaultPosition, _buttonSize);
	_vecButtons[6] = new wxButton(_parentPTR, IDTable::btnNum6, "6", wxDefaultPosition, _buttonSize);
	_vecButtons[7] = new wxButton(_parentPTR, IDTable::btnNum7, "7", wxDefaultPosition, _buttonSize);
	_vecButtons[8] = new wxButton(_parentPTR, IDTable::btnNum8, "8", wxDefaultPosition, _buttonSize);
	_vecButtons[9] = new wxButton(_parentPTR, IDTable::btnNum9, "9", wxDefaultPosition, _buttonSize);
	_vecButtons[0] = new wxButton(_parentPTR, IDTable::btnNum0, "0", wxDefaultPosition, _buttonSize);
	_vecButtons[10] = new wxButton(_parentPTR, IDTable::btnEquals, "=", wxDefaultPosition, _buttonSize);
	_vecButtons[11] = new wxButton(_parentPTR, IDTable::btnAdd, "+", wxDefaultPosition, _buttonSize);
	_vecButtons[12] = new wxButton(_parentPTR, IDTable::btnSubtract, "-", wxDefaultPosition, _buttonSize);
	_vecButtons[13] = new wxButton(_parentPTR, IDTable::btnMultiply, "*", wxDefaultPosition, _buttonSize);
	_vecButtons[14] = new wxButton(_parentPTR, IDTable::btnDivide, "/", wxDefaultPosition, _buttonSize);
	_vecButtons[15] = new wxButton(_parentPTR, IDTable::btnMod,  "%", wxDefaultPosition, _buttonSize);
	_vecButtons[16] = new wxButton(_parentPTR, IDTable::btnSIN, "SIN", wxDefaultPosition, _buttonSize);
	_vecButtons[17] = new wxButton(_parentPTR, IDTable::btnCOS, "COS" , wxDefaultPosition, _buttonSize);
	_vecButtons[18] = new wxButton(_parentPTR, IDTable::btnTAN, "TAN", wxDefaultPosition, _buttonSize);
	_vecButtons[19] = new wxButton(_parentPTR, IDTable::btnDecimal, ".", wxDefaultPosition, _buttonSize);
	_vecButtons[20] = new wxButton(_parentPTR, IDTable::btnNegative, "~", wxDefaultPosition, _buttonSize);
	_vecButtons[21] = new wxButton(_parentPTR, IDTable::btnBackspace, "<-", wxDefaultPosition, _buttonSize);
	_vecButtons[22] = new wxButton(_parentPTR, IDTable::btnClear, "C", wxDefaultPosition, _buttonSize);
}

void ButtonFactory::SetButtonsFont(wxFont _fontReference, std::vector<wxButton*> _vecButtons)
{
	for (size_t i = 0; i < _vecButtons.size(); ++i)
		_vecButtons[i]->SetFont(_fontReference);
	
}

void ButtonFactory::SetButtonsSpacers(int _spacerSize, std::vector<wxBoxSizer*> _sizers, wxTextCtrl& _mainTextBox, std::vector<wxButton*> _buttons)
{
	wxSizer* bFMainBox = _sizers[0];
	wxSizer* bFTextBoxRow = _sizers[1];
	wxSizer* bFRow1 = _sizers[2];
	wxSizer* bfRow2 = _sizers[3];
	wxSizer* bfRow3 = _sizers[4];
	wxSizer* bfRow4 = _sizers[5];
	wxSizer* bfRow5 = _sizers[6];
	wxSizer* bfRow6 = _sizers[7];

	bFMainBox->AddSpacer(_spacerSize);

	bFTextBoxRow->AddSpacer(10);
	bFTextBoxRow->Add(&_mainTextBox);
	bFMainBox->Add(bFTextBoxRow);

	bFRow1->AddSpacer(10);
	bFRow1->Add(_buttons[16]);
	bFRow1->AddSpacer(_spacerSize);
	bFRow1->Add(_buttons[17]);
	bFRow1->AddSpacer(_spacerSize);
	bFRow1->Add(_buttons[18]);
	bFRow1->AddSpacer(_spacerSize);
	bFRow1->Add(_buttons[13]);
	bFRow1->AddSpacer(10);
	bFMainBox->AddSpacer(10);
	bFMainBox->Add(bFRow1);

	bfRow2->AddSpacer(10);
	bfRow2->Add(_buttons[19]);
	bfRow2->AddSpacer(_spacerSize);
	bfRow2->Add(_buttons[20]);
	bfRow2->AddSpacer(_spacerSize);
	bfRow2->Add(_buttons[15]);
	bfRow2->AddSpacer(_spacerSize);
	bfRow2->Add(_buttons[14]);
	bfRow2->AddSpacer(10);
	bFMainBox->AddSpacer(10);
	bFMainBox->Add(bfRow2);

	bfRow3->AddSpacer(10);
	bfRow3->Add(_buttons[7]);
	bfRow3->AddSpacer(_spacerSize);
	bfRow3->Add(_buttons[8]);
	bfRow3->AddSpacer(_spacerSize);
	bfRow3->Add(_buttons[9]);
	bfRow3->AddSpacer(_spacerSize);
	bfRow3->Add(_buttons[12]);
	bfRow3->AddSpacer(10);
	bFMainBox->AddSpacer(10);
	bFMainBox->Add(bfRow3);

	bfRow4->AddSpacer(10);
	bfRow4->Add(_buttons[4]);
	bfRow4->AddSpacer(_spacerSize);
	bfRow4->Add(_buttons[5]);
	bfRow4->AddSpacer(_spacerSize);
	bfRow4->Add(_buttons[6]);
	bfRow4->AddSpacer(_spacerSize);
	bfRow4->Add(_buttons[11]);
	bfRow4->AddSpacer(10);
	bFMainBox->AddSpacer(10);
	bFMainBox->Add(bfRow4);

	bfRow5->AddSpacer(10);
	bfRow5->Add(_buttons[1]);
	bfRow5->AddSpacer(_spacerSize);
	bfRow5->Add(_buttons[2]);
	bfRow5->AddSpacer(_spacerSize);
	bfRow5->Add(_buttons[3]);
	bfRow5->AddSpacer(_spacerSize);
	bfRow5->Add(_buttons[10]);
	bfRow5->AddSpacer(10);
	bFMainBox->AddSpacer(10);
	bFMainBox->Add(bfRow5);

	bfRow6->AddSpacer(10);
	bfRow6->Add(_buttons[22]);
	bfRow6->AddSpacer(_spacerSize);
	bfRow6->Add(_buttons[0]);
	bfRow6->AddSpacer(_spacerSize);
	bfRow6->Add(_buttons[21]);
	bfRow6->AddSpacer(10);
	bFMainBox->AddSpacer(10);
	bFMainBox->Add(bfRow6);
	bFMainBox->AddSpacer(10);
}

void ButtonFactory::SetButtonsEnabled(std::vector<wxButton*> _buttons, std::vector<bool> _status)
{
	for (size_t i = 0; i < _buttons.size(); i++)
		_buttons[i]->Enable(_status[i]);
}

wxFont ButtonFactory::CreateFont()
{
	return wxFont(25, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
}

int ButtonFactory::GetID(int _position)
{
	return IDTable(_position) + 10000;
}

std::vector<bool> ButtonFactory::GetEnabeledVector(Window* _windowObj)
{
	return _windowObj->vecButtonEnabling;
}

int ButtonFactory::GetAmountOfButtons(Window* _windowObj)
{
	return _windowObj->GetAmountOfButtons();
}

int ButtonFactory::GetSpacerSize(Window* _windowObj)
{
	return _windowObj->GetSize().x / 25;
}

int ButtonFactory::GetBoxSizersOrient(Window* _windowObj, int _position)
{
	return _windowObj->WindowGetBoxSizers(_position)->GetOrientation();
}
