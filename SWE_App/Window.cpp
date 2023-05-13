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

Window::Window() : wxFrame(nullptr, wxID_ANY, "Main Window", wxPoint(50, 50), wxSize(500, 900))
{
	// A wxSize variable for all buttons to use, so it can be modified in one location rather thaan multiple.
	wxSize normalButtonSize = wxSize(GetSize().x / 5, GetSize().y / 10);

#pragma region Setting wxBoxSizers, wxButtons, and wxFont to defaults

	// Set all the wxBoxSizer elements to be their appropriate orientation
	mainBox = new wxBoxSizer(wxVERTICAL);
	textBoxRow = new wxBoxSizer(wxHORIZONTAL);
	row1 = new wxBoxSizer(wxHORIZONTAL);
	row2 = new wxBoxSizer(wxHORIZONTAL);
	row3 = new wxBoxSizer(wxHORIZONTAL);
	row4 = new wxBoxSizer(wxHORIZONTAL);
	row5 = new wxBoxSizer(wxHORIZONTAL);
	row6 = new wxBoxSizer(wxHORIZONTAL);
	// Now that they are all initialized, insert them into the vector of box sizer ptrs 
	vecBoxSizers = { mainBox, textBoxRow, row1, row2, row3, row4, row5, row6 };
	
	// Create a generic Font variable so we can make the font fancy in the calculator
	genericFont = wxFont(GetSize().x / 20, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	mainTextBox = new wxTextCtrl(this, IDTable::mainTextBox, "", wxDefaultPosition, wxSize(GetSize().x - (GetSize().x / 12), GetSize().y / 7));
	mainTextBox->SetFont(genericFont);

	// Use the button factory object to create all the buttons, they all follow the same layout so
	// we can use the same CreateButton method to initialize them all
	btnNum0 = buttonFactoryObj.CreateButton(this, IDTable::btnNum0, "0", normalButtonSize);
	btnNum1 = buttonFactoryObj.CreateButton(this, IDTable::btnNum1, "1", normalButtonSize);
	btnNum2 = buttonFactoryObj.CreateButton(this, IDTable::btnNum2, "2", normalButtonSize);
	btnNum3 = buttonFactoryObj.CreateButton(this, IDTable::btnNum3, "3", normalButtonSize);
	btnNum4 = buttonFactoryObj.CreateButton(this, IDTable::btnNum4, "4", normalButtonSize);
	btnNum5 = buttonFactoryObj.CreateButton(this, IDTable::btnNum5, "5", normalButtonSize);
	btnNum6 = buttonFactoryObj.CreateButton(this, IDTable::btnNum6, "6", normalButtonSize);
	btnNum7 = buttonFactoryObj.CreateButton(this, IDTable::btnNum7, "7", normalButtonSize);
	btnNum8 = buttonFactoryObj.CreateButton(this, IDTable::btnNum8, "8", normalButtonSize);
	btnNum9 = buttonFactoryObj.CreateButton(this, IDTable::btnNum9, "9", normalButtonSize);
	btnEquals = buttonFactoryObj.CreateButton(this, IDTable::btnEquals, "=", normalButtonSize);
	btnAdd = buttonFactoryObj.CreateButton(this, IDTable::btnAdd, "+", normalButtonSize);
	btnSubtract = buttonFactoryObj.CreateButton(this, IDTable::btnSubtract, "-", normalButtonSize);
	btnMultiply = buttonFactoryObj.CreateButton(this, IDTable::btnMultiply, "*", normalButtonSize);
	btnDivide = buttonFactoryObj.CreateButton(this, IDTable::btnDivide, "/", normalButtonSize);
	btnMod = buttonFactoryObj.CreateButton(this, IDTable::btnMod, "%", normalButtonSize);
	btnSIN = buttonFactoryObj.CreateButton(this, IDTable::btnSIN, "SIN", normalButtonSize);
	btnCOS = buttonFactoryObj.CreateButton(this, IDTable::btnCOS, "COS", normalButtonSize);
	btnTAN = buttonFactoryObj.CreateButton(this, IDTable::btnTAN, "TAN", normalButtonSize);
	btnDecimal = buttonFactoryObj.CreateButton(this, IDTable::btnDecimal, ".", normalButtonSize);
	btnNegative = buttonFactoryObj.CreateButton(this, IDTable::btnNegative, "~", normalButtonSize);
	btnBackspace =buttonFactoryObj.CreateButton(this, IDTable::btnBackspace, "<-", normalButtonSize);
	btnClear = buttonFactoryObj.CreateButton(this, IDTable::btnClear, "C", normalButtonSize);
	// Now all buttons are initialized we can put them into the vector in one line, instead of push_back'ing every element
	vecButtons = { btnNum1, btnNum2, btnNum3, btnNum4, btnNum5, btnNum6, btnNum7, btnNum8, btnNum9, btnNum0, btnEquals, btnAdd, btnSubtract, btnMultiply, btnDivide, btnMod, btnSIN, btnCOS, btnTAN, btnDecimal, btnNegative, btnBackspace, btnClear };
#pragma endregion

	// Use the button factory's SetButtonsFont method to put all buttons to the fonts type
	buttonFactoryObj.SetButtonsFont(genericFont, vecButtons);

	// Set Spacers and Box Size positions for Buttons in Calculator
	int spacerSize = GetSize().x / 25;
	buttonFactoryObj.SetButtonsSpacers(spacerSize, vecBoxSizers, *mainTextBox, vecButtons);

#pragma region Button Enabling / Disabling

	//				      '1'   '2'   '3'   '4'   '5'   '6'   '7'   '8'   '9'   '0'   '='   '+'   '-'   '*'   '/'   '%'   'SIN'  'COS'  'TAN'  '.'   '~'   '<-'  'C'      
	vecButtonEnabling = { true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, false, false, false, true, true, true, true };
	// Button Enabled/Disabled
	buttonFactoryObj.SetButtonsEnabled(vecButtons, vecButtonEnabling);
	
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
	// All the number cases are doing the exact same thing, so can stack the cases like this to make it more compact
	case IDTable::btnNum1: case IDTable::btnNum2: case IDTable::btnNum3: 
	case IDTable::btnNum4: case IDTable::btnNum5: case IDTable::btnNum6: 
	case IDTable::btnNum7: case IDTable::btnNum8: case IDTable::btnNum9: case IDTable::btnNum0: 
		SetButtonNumTo(evtButton->GetLabel());
		break;

#pragma endregion

	case IDTable::btnEquals:
	{
		// Ex: "3 + " stops this from running and instead forces the user to input a number
		displayAns = mainTextBox->GetValue().ToStdString();
		if (wasOperaterPressed) break;
		parseString = mainTextBox->GetValue().ToStdString();
		ParseStringCalculate();
		mainTextBox->SetLabel(displayAns);
		wasOperaterPressed = wasEqualsPressed = true;
		break;
	}

#pragma region Operations
	case IDTable::btnAdd: case IDTable::btnSubtract: case IDTable::btnMultiply: case IDTable::btnDivide: case IDTable::btnMod:
		ChangeSymbolInParsedString(evtButton->GetLabel());
		break;
#pragma endregion

#pragma region Trig Buttons
	case IDTable::btnSIN:
		// Don't implement just yet, waiting on more details from Chris L. about this function.
		break;

	case IDTable::btnCOS:
		// Don't implement just yet, waiting on more details from Chris L. about this function.
		break;

	case IDTable::btnTAN:
		// Don't implement just yet, waiting on more details from Chris L. about this function.
		break;
#pragma endregion
#pragma region Decimal | Negative | BackSpace | Clear Buttons
	case IDTable::btnDecimal:
	{
		if (mainTextBox->GetValue().ToStdString() != "")
			if (CountCharInLastToken('.') == 1) return;

		if (mainTextBox->GetValue().IsEmpty() || wasOperaterPressed || wasNumberPressed || wasNegationPressed)
			mainTextBox->AppendText('.');

		wasOperaterPressed = wasNumberPressed = false;
		wasDecimalPressed = true;
		break;
	}
	case IDTable::btnNegative:
		if (mainTextBox->GetValue().ToStdString() != "")
		{
			if (CountCharInLastToken('~') == 1) return;
			else if (CountCharInLastToken('.') == 1) return;
			
		}

		if (mainTextBox->GetValue().ToStdString() == "" || !wasOperaterPressed || !wasNumberPressed || !wasDecimalPressed)
			mainTextBox->AppendText("~");

			wasNegationPressed = true;
		break;

	case IDTable::btnBackspace:
	{
		std::string backSpaceText = mainTextBox->GetValue().ToStdString();
		if (backSpaceText.size() > 0)
			backSpaceText.pop_back();

		mainTextBox->SetLabel(backSpaceText);

		if (backSpaceText.size() > 2)
		{
			std::string lastTwoChars = backSpaceText.substr(backSpaceText.size() - 2);

			if (lastTwoChars == " +" || lastTwoChars == "+ " ||
				lastTwoChars == " -" || lastTwoChars == "- " ||
				lastTwoChars == " *" || lastTwoChars == "* " ||
				lastTwoChars == " /" || lastTwoChars == "/ " ||
				lastTwoChars == " %" || lastTwoChars == "% ")
				wasOperaterPressed = true;

			if (lastTwoChars == "0." || lastTwoChars == ". ")
				wasDecimalPressed = true;
		}

		if (mainTextBox->GetValue().ToStdString() == "")
		{
			wasEqualsPressed = wasNumberPressed = wasNegationPressed = wasDecimalPressed = false;
			wasOperaterPressed = true;
		}

		break;
	}
	case IDTable::btnClear:
		mainTextBox->SetLabelText("");
		tokens.clear();
		wasOperaterPressed = true;
		wasNegationPressed = wasNumberPressed = false;

		break;
#pragma endregion

	default:
		break;
	}
}

void Window::ParseStringCalculate()
{
	CreateTokens();

	for (size_t i = 0; i < tokens.size(); ++i)
	{
		if (tokens[i][0] == '~')
			tokens[i][0] = '-';

		if (tokens[i].size() == 1 && tokens[i][0] == '.')
			tokens[i] = '0';

		if (tokens[i].size() == 2 && tokens[i][0] == '-' && tokens[i][1] == '.')
			tokens[i] = '0';
	}

	if (tokens.size() < 3) return;

	// Stores the tokens at the first, second, and third values as
	// ints and a char (ascii val)
	num1 = std::stof(tokens[0]);
	operational = *tokens[1].c_str();
	num2 = std::stof(tokens[2]);

	switch (operational)
	{
	case '%':
		if (num1 < 1 || num2 < 1)
			answer = 0;
		else answer = (int)num1 % (int)num2;
		break;
	case '*':
		answer = num1 * num2;
		break;
	case '+':
		answer = num1 + num2;
		break;
	case '-':
		answer = num1 - num2;
		break;
	case '/':
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
	wasNumberPressed = wasDecimalPressed = false;
}

void Window::SetButtonNumTo(wxString _string)
{
	mainTextBox->AppendText(_string);
	wasOperaterPressed = wasNegationPressed = wasDecimalPressed = false;
	wasNumberPressed = true;
}

void Window::CreateTokens()
{
	tokens.clear();
	std::stringstream lineStream(mainTextBox->GetValue().ToStdString());

	std::string secondaryStringToParseWith;

	// Collects all tokens in the string from mainTextBox
	while (std::getline(lineStream, secondaryStringToParseWith, ' '))
		tokens.push_back(secondaryStringToParseWith);
	
}

int Window::CountCharInLastToken(char _charToCheckFor)
{
	int characterAbundanceCount = 0;
	CreateTokens();

	if (tokens.size() == 0)
	{
		for (auto characters : mainTextBox->GetValue().ToStdString())
			if (characters == _charToCheckFor)
				++characterAbundanceCount;
	}
	else
	{
		for (auto characters : tokens[tokens.size() - 1])
		{
			if (characters == _charToCheckFor)
				++characterAbundanceCount;
		}
	}

	return characterAbundanceCount;
}
