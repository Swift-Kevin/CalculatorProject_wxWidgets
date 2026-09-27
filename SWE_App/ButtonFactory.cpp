#include "ButtonFactory.h"
#include "Window.h"

wxButton* ButtonFactory::CreateButton(wxWindow* _parentPTR, int _id, const wxString& _label, ButtonType _type, const wxSize& _buttonSize)
{
	// Button colors, numbers are darkest so the operators pop
	const wxColour numberBG(59, 59, 64);
	const wxColour functionBG(90, 90, 98);
	const wxColour operatorBG(255, 149, 0);
	const wxColour clearBG(214, 69, 65);
	const wxColour buttonText(245, 245, 247);

	wxButton* newButton = new wxButton(_parentPTR, _id, _label, wxDefaultPosition, _buttonSize, wxBORDER_NONE);

	switch (_type)
	{
	case ButtonType::Number:
		newButton->SetBackgroundColour(numberBG);
		break;
	case ButtonType::Operator:
		newButton->SetBackgroundColour(operatorBG);
		break;
	case ButtonType::Clear:
		newButton->SetBackgroundColour(clearBG);
		break;
	default:
		newButton->SetBackgroundColour(functionBG);
		break;
	}
	newButton->SetForegroundColour(buttonText);

	return newButton;
}

void ButtonFactory::CreateButtons(wxWindow* _parentPTR, std::vector<wxButton*>& _vecButtons, wxSize& _buttonSize)
{
	const std::vector<ButtonInfo>& buttonTable = GetButtonTable();

	_vecButtons.resize(buttonTable.size());
	for (size_t i = 0; i < buttonTable.size(); ++i)
	{
		_vecButtons[i] = CreateButton(_parentPTR, buttonTable[i].id, buttonTable[i].label, buttonTable[i].type, _buttonSize);
	}
}

const std::vector<ButtonInfo>& ButtonFactory::GetButtonTable()
{
	static const std::vector<ButtonInfo> buttonTable = 
	{
		{ IDTable::btnNum0, L"0", "0", L"0", ButtonType::Number },
		{ IDTable::btnNum1, L"1", "1", L"1", ButtonType::Number },
		{ IDTable::btnNum2, L"2", "2", L"2", ButtonType::Number },
		{ IDTable::btnNum3, L"3", "3", L"3", ButtonType::Number },
		{ IDTable::btnNum4, L"4", "4", L"4", ButtonType::Number },
		{ IDTable::btnNum5, L"5", "5", L"5", ButtonType::Number },
		{ IDTable::btnNum6, L"6", "6", L"6", ButtonType::Number },
		{ IDTable::btnNum7, L"7", "7", L"7", ButtonType::Number },
		{ IDTable::btnNum8, L"8", "8", L"8", ButtonType::Number },
		{ IDTable::btnNum9, L"9", "9", L"9", ButtonType::Number },
		{ IDTable::btnEquals, L"=", "",  L"=\r", ButtonType::Operator },
		{ IDTable::btnAdd, L"+", "+", L"+", ButtonType::Operator },
		{ IDTable::btnSubtract, L"\u2212", "-", L"-", ButtonType::Operator },
		{ IDTable::btnMultiply, L"\u00D7", "*", L"*xX", ButtonType::Operator },
		{ IDTable::btnDivide, L"\u00F7", "/", L"/", ButtonType::Operator },
		{ IDTable::btnMod, L"%", "%", L"%", ButtonType::Function },
		{ IDTable::btnSIN, L"sin", "s", L"sS", ButtonType::Function },
		{ IDTable::btnCOS, L"cos", "c", L"cC", ButtonType::Function },
		{ IDTable::btnTAN, L"tan", "t", L"tT", ButtonType::Function },
		{ IDTable::btnDecimal, L".", ".", L".,", ButtonType::Number },
		{ IDTable::btnNegative, L"\u00B1", "~", L"~", ButtonType::Function },
		{ IDTable::btnBackspace, L"\u232B", "",  L"", ButtonType::Function },
		{ IDTable::btnClear, L"C", "",  L"", ButtonType::Clear }
	};

	return buttonTable;
}

const ButtonInfo* ButtonFactory::GetButtonInfo(int _id)
{
	for (const ButtonInfo& info : GetButtonTable())
	{
		if (info.id == _id)
		{
			return &info;
		}
	}

	return nullptr;
}

const ButtonInfo* ButtonFactory::GetButtonInfoForKey(wxChar _key)
{
	// 0 means the key didn't type a character
	if (_key == 0)
	{
		return nullptr;
	}

	for (const ButtonInfo& info : GetButtonTable())
	{
		if (wcschr(info.keys, _key) != nullptr)
		{
			return &info;
		}
	}

	return nullptr;
}

wxButton* ButtonFactory::GetButton(const std::vector<wxButton*>& _buttons, int _id)
{
	for (wxButton* button : _buttons)
	{
		if (button != nullptr && button->GetId() == _id)
		{
			return button;
		}
	}

	return nullptr;
}

void ButtonFactory::SetButtonsFont(wxFont _fontReference, const std::vector<wxButton*>& _vecButtons)
{
	for (size_t i = 0; i < _vecButtons.size(); ++i)
	{
		_vecButtons[i]->SetFont(_fontReference);
	}
}

void ButtonFactory::SetButtonsSpacers(int _spacerSize, const std::vector<wxBoxSizer*>& _sizers, wxTextCtrl& _mainTextBox, const std::vector<wxButton*>& _buttons, wxStaticText* _historyText)
{
	wxSizer* bFMainBox = _sizers[0];
	wxSizer* bFTextBoxRow = _sizers[1];

	// Button layout, top to bottom
	//   SIN  COS  TAN  <-
	//   C    +/-  %    /
	//   7    8    9    *
	//   4    5    6    -
	//   1    2    3    +
	//   0 (wide)  .    =
	const std::vector<std::vector<int>> rowLayout = {
		{ IDTable::btnSIN, IDTable::btnCOS, IDTable::btnTAN,IDTable::btnBackspace },
		{ IDTable::btnClear, IDTable::btnNegative, IDTable::btnMod, IDTable::btnDivide },
		{ IDTable::btnNum7, IDTable::btnNum8, IDTable::btnNum9, IDTable::btnMultiply },
		{ IDTable::btnNum4, IDTable::btnNum5, IDTable::btnNum6, IDTable::btnSubtract },
		{ IDTable::btnNum1, IDTable::btnNum2, IDTable::btnNum3, IDTable::btnAdd },
		{ IDTable::btnNum0, IDTable::btnDecimal, IDTable::btnEquals }
	};

	const int buttonProportion = 5;
	const int spacerProportion = 1;
	const int wideButtonProportion = buttonProportion * 2 + spacerProportion;

	wxButton* zeroButton = GetButton(_buttons, IDTable::btnNum0);
	wxSize normalSize = zeroButton->GetSize();
	zeroButton->SetMinSize(wxSize(normalSize.x * 2 + _spacerSize, normalSize.y));

	// Display area, last equation on top and the current value under it
	bFMainBox->AddSpacer(_spacerSize);
	if (_historyText != nullptr)
	{
		bFMainBox->Add(_historyText, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	}

	bFTextBoxRow->AddSpacer(10);
	bFTextBoxRow->Add(&_mainTextBox, 1, wxEXPAND);
	bFTextBoxRow->AddSpacer(10);
	bFMainBox->Add(bFTextBoxRow, 0, wxEXPAND);
	bFMainBox->AddSpacer(_spacerSize);

	for (size_t row = 0; row < rowLayout.size(); ++row)
	{
		wxSizer* rowSizer = _sizers[row + 2];

		rowSizer->AddSpacer(10);
		for (size_t col = 0; col < rowLayout[row].size(); ++col)
		{
			if (col > 0)
			{
				rowSizer->Add(0, 0, spacerProportion);
			}

			int buttonID = rowLayout[row][col];
			rowSizer->Add(GetButton(_buttons, buttonID), buttonID == IDTable::btnNum0 ? wideButtonProportion : buttonProportion, wxEXPAND);
		}
		rowSizer->AddSpacer(10);

		// Rows split the height evenly so buttons stretch with the window
		if (row > 0)
		{
			bFMainBox->AddSpacer(10);
		}

		bFMainBox->Add(rowSizer, 1, wxEXPAND);
	}
	bFMainBox->AddSpacer(10);
}

wxFont ButtonFactory::CreateFont()
{
	return wxFont(25, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
}

int ButtonFactory::GetID(int _position)
{
	return IDTable(_position) + 10000;
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
