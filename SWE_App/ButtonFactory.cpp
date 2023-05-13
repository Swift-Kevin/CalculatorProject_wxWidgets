#include "ButtonFactory.h"

wxButton* ButtonFactory::CreateButton(wxWindow* _parentPTR, int _id, std::string _displayNum, wxSize& _buttonSize, const wxPoint& _position)
{
	return new wxButton(_parentPTR, _id, _displayNum, _position, _buttonSize);
}

void ButtonFactory::SetButtonsFont(wxFont _fontReference, std::vector<wxButton*> _vecButtons)
{
	for (size_t i = 0; i < _vecButtons.size(); ++i)
	{
		_vecButtons[i]->SetFont(_fontReference);
	}
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
	bfRow3->Add(_buttons[6]);
	bfRow3->AddSpacer(_spacerSize);
	bfRow3->Add(_buttons[7]);
	bfRow3->AddSpacer(_spacerSize);
	bfRow3->Add(_buttons[8]);
	bfRow3->AddSpacer(_spacerSize);
	bfRow3->Add(_buttons[12]);
	bfRow3->AddSpacer(10);
	bFMainBox->AddSpacer(10);
	bFMainBox->Add(bfRow3);

	bfRow4->AddSpacer(10);
	bfRow4->Add(_buttons[3]);
	bfRow4->AddSpacer(_spacerSize);
	bfRow4->Add(_buttons[4]);
	bfRow4->AddSpacer(_spacerSize);
	bfRow4->Add(_buttons[5]);
	bfRow4->AddSpacer(_spacerSize);
	bfRow4->Add(_buttons[11]);
	bfRow4->AddSpacer(10);
	bFMainBox->AddSpacer(10);
	bFMainBox->Add(bfRow4);

	bfRow5->AddSpacer(10);
	bfRow5->Add(_buttons[0]);
	bfRow5->AddSpacer(_spacerSize);
	bfRow5->Add(_buttons[1]);
	bfRow5->AddSpacer(_spacerSize);
	bfRow5->Add(_buttons[2]);
	bfRow5->AddSpacer(_spacerSize);
	bfRow5->Add(_buttons[10]);
	bfRow5->AddSpacer(10);
	bFMainBox->AddSpacer(10);
	bFMainBox->Add(bfRow5);

	bfRow6->AddSpacer(10);
	bfRow6->Add(_buttons[22]);
	bfRow6->AddSpacer(_spacerSize);
	bfRow6->Add(_buttons[9]);
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
