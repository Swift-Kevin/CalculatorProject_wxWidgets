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

#pragma region Event Table
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
#pragma endregion

Window::Window() : wxFrame(nullptr, wxID_ANY, "Main Window", wxPoint(50, 50), wxSize(300, 700))
{
	// A wxSize variable for all buttons to use, so it can be modified in one location rather thaan multiple.
	wxSize normalButtonSize = wxSize(60, 70);

#pragma region Setting wxBoxSizers and wxButtons to defaulted sizes

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

#pragma endregion

#pragma region Set Spacers and Box Size positions for Buttons in Calculator

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
#pragma endregion

#pragma region Button Enabling / Disabling
	// Button Enabled/Disabled
	btnNum1->Enable(true);
	btnNum2->Enable(true);
	btnNum3->Enable(true);
	btnNum4->Enable(true);
	btnNum5->Enable(true);
	btnNum6->Enable(true);
	btnNum7->Enable(true);
	btnNum8->Enable(true);
	btnNum9->Enable(true);
	btnNum0->Enable(true);
	btnEquals->Enable(true);
	btnAdd->Enable(true);
	btnSubtract->Enable(true);
	btnMultiply->Enable(true);
	btnDivide->Enable(true);
	btnMod->Enable(true);
	btnSIN->Enable(false);
	btnCOS->Enable(false);
	btnTAN->Enable(false);
	btnDecimal->Enable(true);
	btnNegative->Enable(false);
	btnBackspace->Enable(true);
	btnClear->Enable(true);

#pragma endregion

	// Sets the box sizers to work properly
	SetSizerAndFit(mainBox);
	// Defaults wasOperatorPressed to true for decimal button cases
	// If its false then it would allow for ". + 3" which would cause an issue since there is no number to operate on
	wasOperaterPressed = true;
}

void Window::OnButtonClick(wxCommandEvent& _event)
{
	wxButton* evtButton = static_cast<wxButton*>(_event.GetEventObject());

	switch (evtButton->GetId())
	{
#pragma region Appending Number pressed into calculator string
	case IDTable::btnNum1:
		SetButtonNumTo(evtButton->GetLabel());
		break;

	case IDTable::btnNum2:
		SetButtonNumTo(evtButton->GetLabel());
		break;

	case IDTable::btnNum3:
		SetButtonNumTo(evtButton->GetLabel());
		break;

	case IDTable::btnNum4:
		SetButtonNumTo(evtButton->GetLabel());
		break;

	case IDTable::btnNum5:
		SetButtonNumTo(evtButton->GetLabel());
		break;

	case IDTable::btnNum6:
		SetButtonNumTo(evtButton->GetLabel());
		break;

	case IDTable::btnNum7:
		SetButtonNumTo(evtButton->GetLabel());
		break;

	case IDTable::btnNum8:
		SetButtonNumTo(evtButton->GetLabel());
		break;

	case IDTable::btnNum9:
		SetButtonNumTo(evtButton->GetLabel());
		break;

	case IDTable::btnNum0:
		SetButtonNumTo(evtButton->GetLabel());
		break;
#pragma endregion

	case IDTable::btnEquals:
	{
		// Ex: "3 + " stops this from running and instead forces the user to input a number
		if (wasOperaterPressed) break;

		parseString = mainTextBox->GetValue().ToStdString();
		ParseStringCalculate();
		mainTextBox->SetLabel(displayAns);
		break;
	}
#pragma region Operator Buttons
	case IDTable::btnAdd:
		ChangeSymbolInParsedString(evtButton->GetLabel());
		break;
	case IDTable::btnSubtract:
		ChangeSymbolInParsedString(evtButton->GetLabel());
		break;

	case IDTable::btnMultiply:
		ChangeSymbolInParsedString(evtButton->GetLabel());
		break;

	case IDTable::btnDivide:
		ChangeSymbolInParsedString(evtButton->GetLabel());
		break;

	case IDTable::btnMod:
		ChangeSymbolInParsedString(evtButton->GetLabel());
		break;

	case IDTable::btnSIN:
		// Don't implement just yet, waiting on more details from Chris L. about this function.
		break;

	case IDTable::btnCOS:
		// Don't implement just yet, waiting on more details from Chris L. about this function.
		break;

	case IDTable::btnTAN:
		// Don't implement just yet, waiting on more details from Chris L. about this function.
		break;

	case IDTable::btnDecimal:
		if (mainTextBox->GetValue().IsEmpty() || wasOperaterPressed)
			mainTextBox->AppendText('0' + evtButton->GetLabel());
		else mainTextBox->AppendText(evtButton->GetLabel());

		wasOperaterPressed = false;
		break;

	case IDTable::btnNegative:
		// Don't implement just yet, waiting on more details from Chris L. about this function.
		break;
#pragma endregion

	case IDTable::btnBackspace:
	{
		std::string backSpaceText = mainTextBox->GetValue().ToStdString();
		if (backSpaceText.size() > 0)
			backSpaceText.pop_back();

		mainTextBox->SetLabel(backSpaceText);
		break;
	}
	case IDTable::btnClear:
		mainTextBox->SetLabelText("");
		tokens.clear();
		break;

	default:
		break;
	}
}

void Window::ParseStringCalculate()
{
	tokens.clear();
	std::stringstream lineStream(parseString);

	std::string secondaryStringToParseWith;

	// Collects all tokens in the string from mainTextBox
	while (std::getline(lineStream, secondaryStringToParseWith, ' '))
	{
		tokens.push_back(secondaryStringToParseWith);
	}

	if (tokens.size() < 3) return;

	// Stores the tokens at the first, second, and third values as
	// ints and a char (ascii val)
	num1 = std::stof(tokens[0]);
	operational = *tokens[1].c_str();
	num2 = std::stof(tokens[2]);
	switch (operational)
	{
	case 37: // mod - in ascii value for case #
		answer = (int)num1 % (int)num2;
		break;
	case 42: // multiply - in ascii value for case #
		answer = num1 * num2;
		break;
	case 43: // add - in ascii value for case #
		answer = num1 + num2;
		break;
	case 45: // subtract - in ascii value for case #
		answer = num1 - num2;
		break;
	case 47: // divide - in ascii value for case #
		answer = num1 / num2;
		break;
	}

	if ((int)answer == answer)
		displayAns = std::to_string((int)answer);
	else displayAns = std::to_string(answer);
	
}

void Window::ChangeSymbolInParsedString(wxString _string)
{
	if (wasOperaterPressed)
	{
		std::string replaceSymString = mainTextBox->GetValue().ToStdString();
		if (mainTextBox->GetValue().ToStdString().size() == 0)
		{
			mainTextBox->AppendText("0 " + _string + " ");
			return;
		}

		// Check to see if the current last character is a space or not
		if (replaceSymString.back() == ' ')
			replaceSymString.pop_back();

		// Check to see if the current character is a symbol or not
		// This helps with backspacing against operaters and then overriding numbers
		// by accidentally deleting them
		if (replaceSymString.back() == '+' ||
			replaceSymString.back() == '-' ||
			replaceSymString.back() == '*' ||
			replaceSymString.back() == '/' ||
			replaceSymString.back() == '%')
			replaceSymString.pop_back();

		// Check to see if the current last character is a space or not
		if (replaceSymString.back() == ' ')
			replaceSymString.pop_back();
		mainTextBox->SetLabel(replaceSymString);
		mainTextBox->AppendText(" " + _string + " ");
	}
	else
	{
		mainTextBox->AppendText(" " + _string + " ");
		wasOperaterPressed = true;
	}
}

void Window::SetButtonNumTo(wxString _string)
{
	mainTextBox->AppendText(_string);
	wasOperaterPressed = false;
}