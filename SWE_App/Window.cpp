#include "Window.h"

#pragma region Event Table
wxBEGIN_EVENT_TABLE(Window, wxFrame)
// Button IDs are in order, so one range covers them all
EVT_COMMAND_RANGE(IDTable::btnNum1, IDTable::btnClear, wxEVT_BUTTON, Window::OnButtonClick)
EVT_CHAR_HOOK(Window::OnKeyDown)
EVT_SIZE(Window::OnResize)
wxEND_EVENT_TABLE()
#pragma endregion

namespace
{
	// Dark theme colors
	const wxColour windowBG(28, 28, 30);
	const wxColour displayTextColor(245, 245, 247);
	const wxColour historyTextColor(142, 142, 147);
}

Window::Window() : wxFrame(nullptr, wxID_ANY, "Calculator", wxPoint(50, 50), wxSize(500, 900))
{
	SetBackgroundColour(windowBG);

	// One button size for everything so it only changes in one spot
	wxSize normalButtonSize = wxSize(GetSize().x / 5, GetSize().y / 10);
	int spacerSize = GetSize().x / 25;

	// All sized off the starting window, so do it before SetSizerAndFit
	SetUpSizers();
	SetUpFonts();
	SetUpDisplay();
	SetUpButtons(normalButtonSize, spacerSize);
	SetUpKeyboardInput();

	// Hook up the sizers
	SetSizerAndFit(mainBox);

	SetUpResizing(normalButtonSize, spacerSize);

	// Start with wasOperaterPressed true, some buttons need it false before they'll work
	wasOperaterPressed = true;
}

void Window::SetUpSizers()
{
	// Make the sizers
	mainBox = new wxBoxSizer(wxVERTICAL);
	textBoxRow = new wxBoxSizer(wxHORIZONTAL);
	row1 = new wxBoxSizer(wxHORIZONTAL);
	row2 = new wxBoxSizer(wxHORIZONTAL);
	row3 = new wxBoxSizer(wxHORIZONTAL);
	row4 = new wxBoxSizer(wxHORIZONTAL);
	row5 = new wxBoxSizer(wxHORIZONTAL);
	row6 = new wxBoxSizer(wxHORIZONTAL);
	sizerButtonsAll = { mainBox, textBoxRow, row1, row2, row3, row4, row5, row6 };
}

void Window::SetUpFonts()
{
	// Starting font sizes, OnResize scales these
	buttonFontSize = GetSize().x / 25;
	historyFontSize = GetSize().x / 35;
	displayFontSize = GetSize().x / 14;

	// Button font
	genericFont = wxFont(wxFontInfo(buttonFontSize).FaceName("Segoe UI"));
}

void Window::SetUpDisplay()
{
	// Grey line above the display with the last equation
	historyText = new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT | wxST_NO_AUTORESIZE | wxST_ELLIPSIZE_START);
	historyText->SetFont(wxFont(wxFontInfo(historyFontSize).FaceName("Segoe UI")));
	historyText->SetForegroundColour(historyTextColor);
	historyText->SetBackgroundColour(windowBG);
	historyText->SetMinSize(wxSize(-1, historyText->GetCharHeight()));

	// Read only, typing goes through OnCharacterPressed instead
	mainTextBox = new wxTextCtrl(this, IDTable::mainTextBox, "", wxDefaultPosition, wxSize(GetSize().x - (GetSize().x / 12), -1), wxTE_RIGHT | wxTE_READONLY | wxBORDER_NONE);
	mainTextBox->SetFont(wxFont(wxFontInfo(displayFontSize).FaceName("Segoe UI Light")));
	mainTextBox->SetBackgroundColour(windowBG);
	mainTextBox->SetForegroundColour(displayTextColor);
}

void Window::SetUpButtons(wxSize _normalButtonSize, int _spacerSize)
{
	// Factory makes all the buttons
	buttonFactoryObj.CreateButtons(this, vecButtons, _normalButtonSize);

	// Put the font on every button
	buttonFactoryObj.SetButtonsFont(genericFont, vecButtons);

	// Lay everything out
	buttonFactoryObj.SetButtonsSpacers(_spacerSize, sizerButtonsAll, *mainTextBox, vecButtons, historyText);
}

void Window::SetUpKeyboardInput()
{
	// Keys go to whatever has focus, so everything sends them to OnCharacterPressed
	for (wxButton* button : vecButtons)
	{
		button->Bind(wxEVT_CHAR, &Window::OnCharacterPressed, this);
	}
	mainTextBox->Bind(wxEVT_CHAR, &Window::OnCharacterPressed, this);
	Bind(wxEVT_CHAR, &Window::OnCharacterPressed, this);
}

void Window::SetUpResizing(const wxSize& _normalButtonSize, int _spacerSize)
{
	// OnResize scales off this
	startingClientSize = GetClientSize();

	// Lower the min sizes so the window can shrink, the 0 button stays two wide
	wxSize smallestButtonSize = wxSize(_normalButtonSize.x / 2, _normalButtonSize.y / 2);
	for (wxButton* button : vecButtons)
	{
		button->SetMinSize(smallestButtonSize);
	}
	ButtonFactory::GetButton(vecButtons, IDTable::btnNum0)->SetMinSize(wxSize(smallestButtonSize.x * 2 + _spacerSize, smallestButtonSize.y));
	mainTextBox->SetMinSize(wxSize(smallestButtonSize.x, -1));

	// Can't shrink smaller than everything fits
	SetMinClientSize(mainBox->GetMinSize());
}

void Window::OnButtonClick(wxCommandEvent& _event)
{
	wxButton* evtButton = static_cast<wxButton*>(_event.GetEventObject());
	// Look the button up in the table
	const ButtonInfo* buttonInfo = ButtonFactory::GetButtonInfo(evtButton->GetId());
	if (buttonInfo == nullptr)
	{
		return;
	}

	// Any button clears undef and starts fresh
	if (GetDisplayText() == CalculatorProcessor::ErrorText)
	{
		mainTextBox->SetLabelText("");
		ResetFlags();
	}

	switch (evtButton->GetId())
	{
		// All the numbers do the same thing, so stack the cases
	case IDTable::btnNum1: case IDTable::btnNum2: case IDTable::btnNum3:
	case IDTable::btnNum4: case IDTable::btnNum5: case IDTable::btnNum6:
	case IDTable::btnNum7: case IDTable::btnNum8: case IDTable::btnNum9: case IDTable::btnNum0:
		wasEqualsPressed = false;
		SetButtonNumTo(buttonInfo->symbol);
		break;

	case IDTable::btnEquals:
		EqualsCase();
		break;

	case IDTable::btnAdd: case IDTable::btnSubtract: case IDTable::btnMultiply: case IDTable::btnDivide: case IDTable::btnMod:
		// Labels have the fancy symbols, so use the plain one from the table
		wasEqualsPressed = false;
		ChangeSymbolInParsedString(buttonInfo->symbol);
		break;
	case IDTable::btnSIN: case IDTable::btnCOS: case IDTable::btnTAN:
		ChangeTrigSymbol(buttonInfo->symbol);
		break;

	case IDTable::btnDecimal:
		DecimalCase();
		break;

	case IDTable::btnNegative:
		NegativeCase();
		CheckOperator();

		wasNegationPressed = true;
		break;

	case IDTable::btnBackspace:
		BackspaceCase();
		break;

	case IDTable::btnClear:
		ClearCase();
		break;

	default:
		break;
	}
}

void Window::PressButton(int _id)
{
	// Fake a click so keys go through OnButtonClick too
	wxButton* buttonToPress = ButtonFactory::GetButton(vecButtons, _id);
	if (buttonToPress == nullptr)
	{
		return;
	}

	wxCommandEvent clickEvent(wxEVT_BUTTON, _id);
	clickEvent.SetEventObject(buttonToPress);
	OnButtonClick(clickEvent);
}

void Window::OnKeyDown(wxKeyEvent& _event)
{
	// Runs before the focused button sees the key, stops Space clicking the last button
	// Enter shows up here or in OnCharacterPressed depending on focus
	switch (_event.GetKeyCode())
	{
	case WXK_RETURN: case WXK_NUMPAD_ENTER:
		PressButton(IDTable::btnEquals);
		break;
	case WXK_BACK:
		PressButton(IDTable::btnBackspace);
		break;
	case WXK_ESCAPE: case WXK_DELETE:
		PressButton(IDTable::btnClear);
		break;
	case WXK_F9:
		PressButton(IDTable::btnNegative);
		break;
	case WXK_SPACE:
		break;
	default:
		// Everything else goes to OnCharacterPressed
		_event.Skip();
		break;
	}
}

void Window::OnCharacterPressed(wxKeyEvent& _event)
{
	// what key was pressed
	const ButtonInfo* buttonInfo = ButtonFactory::GetButtonInfoForKey(_event.GetUnicodeKey());

	if (buttonInfo != nullptr)
	{
		PressButton(buttonInfo->id);
	}

	_event.Skip();
}

void Window::OnResize(wxSizeEvent& _event)
{
	// Skip while the window is still being built
	if (startingClientSize.x > 0 && startingClientSize.y > 0)
	{
		// Scale off whichever side shrunk more
		double widthScale = (double)GetClientSize().x / startingClientSize.x;
		double heightScale = (double)GetClientSize().y / startingClientSize.y;
		double scale = std::min(widthScale, heightScale);

		genericFont = ScaleFont(genericFont, buttonFontSize, scale, 6.0);
		buttonFactoryObj.SetButtonsFont(genericFont, vecButtons);

		historyText->SetFont(ScaleFont(historyText->GetFont(), historyFontSize, scale, 6.0));
		historyText->SetMinSize(wxSize(-1, historyText->GetCharHeight()));

		mainTextBox->SetFont(ScaleFont(mainTextBox->GetFont(), displayFontSize, scale, 8.0));
	}

	// Let the sizers handle the rest
	_event.Skip();
}

void Window::EqualsCase()
{
	// FixOperators cleans up leftovers first (Ex: "3 + " -> "3")
	std::string needsFixing = GetDisplayText();
	std::string displayAns = needsFixing;

	CalculatorProcessor* instance = CalculatorProcessor::GetInstance();
	instance->FixOperators(needsFixing, tokens);

	mainTextBox->SetValue(needsFixing);
	CreateTokens();

	// Nothing left to solve
	if (needsFixing == "")
	{
		mainTextBox->SetLabel(CalculatorProcessor::ErrorText);
		return;
	}

	// Anything else wrong comes back as undef
	std::string calculatorDisplayAns;
	instance->CreateAndCalcTokens(needsFixing, calculatorDisplayAns);

	historyText->SetLabel(displayAns + " =");
	mainTextBox->SetLabel(calculatorDisplayAns);
	wasOperaterPressed = wasEqualsPressed = true;
}

void Window::DecimalCase()
{
	std::string displayText = GetDisplayText();

	// One decimal per number
	if (!displayText.empty() && CountCharInLastToken('.') == 1)
	{
		return;
	}

	if (displayText.empty() || wasOperaterPressed || wasNumberPressed || wasNegationPressed)
	{
		mainTextBox->AppendText('.');
	}

	wasOperaterPressed = wasNumberPressed = false;
	wasDecimalPressed = true;
}

void Window::NegativeCase()
{
	Window::CreateTokens();
	Window::CheckOperator();

	if (tokens.empty())
	{
		tokens.push_back(GetDisplayText());
	}

	// After an operator or answer, ~ starts a new number
	bool lastTokenIsOperator = tokens.back().size() == 1 && CalculatorProcessor::IsOperator(tokens.back()[0]);
	if ((wasOperaterPressed && lastTokenIsOperator) || (!wasNegationPressed && wasEqualsPressed))
	{
		mainTextBox->AppendText('~');
		MarkNegationPressed();
		return;
	}

	// Otherwise flip the sign on the last number
	std::string& lastToken = tokens.back();
	if (!lastToken.empty())
	{
		if (lastToken.front() == '~')
		{
			lastToken.erase(0, 1);
		}
		else
		{
			lastToken.insert(0, 1, '~');
		}
	}
	else if (GetDisplayText().empty())
	{
		lastToken.push_back('~');
	}

	mainTextBox->SetLabelText(CalculatorProcessor::JoinTokens(tokens));

	MarkNegationPressed();
}

void Window::BackspaceCase()
{
	std::string backSpaceText = GetDisplayText();
	if (!backSpaceText.empty())
	{
		backSpaceText.pop_back();
	}

	mainTextBox->SetLabel(backSpaceText);

	// Fix the flags to match what's left
	CheckOperator();

	if (backSpaceText.empty())
	{
		ResetFlags();
	}
}

void Window::ClearCase()
{
	mainTextBox->SetLabelText("");
	historyText->SetLabel("");
	tokens.clear();
	// Reset everything, wasEqualsPressed too or trig stays blocked
	ResetFlags();
}

void Window::SetButtonNumTo(const wxString& _string)
{
	mainTextBox->AppendText(_string);
	wasOperaterPressed = wasNegationPressed = wasDecimalPressed = wasTrigPressed = false;
	wasNumberPressed = true;
}

void Window::ChangeSymbolInParsedString(const wxString& _string)
{
	if (wasOperaterPressed)
	{
		std::string replaceSymString = GetDisplayText();
		if (replaceSymString.empty())
		{
			mainTextBox->AppendText("0 " + _string + " ");
			return;
		}

		// Drop the trailing space
		RemoveTrailingSpace(replaceSymString);

		// Swap out the old operator so you can change your mind
		if (!replaceSymString.empty() && CalculatorProcessor::IsOperator(replaceSymString.back()))
		{
			replaceSymString.pop_back();
		}

		// And the one before the operator
		RemoveTrailingSpace(replaceSymString);
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

void Window::ChangeTrigSymbol(const wxString& _string)
{
	if (wasEqualsPressed)
	{
		return;
	}

	if (wasTrigPressed)
	{
		std::string replaceSymString = GetDisplayText();
		if (replaceSymString.empty())
		{
			mainTextBox->AppendText(_string);
			return;
		}

		if (CalculatorProcessor::IsTrigSymbol(replaceSymString.back()))
		{
			replaceSymString.pop_back();
		}

		mainTextBox->SetLabel(replaceSymString);
		mainTextBox->AppendText(_string);
	}
	else if (wasOperaterPressed)
	{
		// One trig per number
		std::string lastToken = GetLastToken();
		for (char trigSymbol : { 's', 'c', 't' })
		{
			if (std::count(lastToken.begin(), lastToken.end(), trigSymbol) == 1)
			{
				return;
			}
		}

		mainTextBox->AppendText(_string);
		wasTrigPressed = true;
	}
	wasNumberPressed = wasDecimalPressed = wasOperaterPressed = false;
}

void Window::CheckOperator()
{
	std::string checkForOperator = GetDisplayText();
	if (checkForOperator.size() > 2)
	{
		std::string lastTwoChars = checkForOperator.substr(checkForOperator.size() - 2);

		// Ex: "+ "
		if (lastTwoChars[1] == ' ' && CalculatorProcessor::IsOperator(lastTwoChars[0]))
		{
			wasOperaterPressed = true;
		}
		// Ex: " +"
		else if (lastTwoChars[0] == ' ' && CalculatorProcessor::IsOperator(lastTwoChars[1]))
		{
			wasOperaterPressed = true;
			lastTwoChars.push_back(' ');
		}

		if (lastTwoChars == "0." || lastTwoChars == ". ")
		{
			wasDecimalPressed = true;
		}

		// Ex: "s " or " s"
		if ((lastTwoChars[1] == ' ' && CalculatorProcessor::IsTrigSymbol(lastTwoChars[0])) ||
			(lastTwoChars[0] == ' ' && CalculatorProcessor::IsTrigSymbol(lastTwoChars[1])))
		{
			wasTrigPressed = true;
		}
	}
}

void Window::CreateTokens()
{
	wasEqualsPressed = false;

	// Split the display into tokens
	CalculatorProcessor::SplitIntoTokens(GetDisplayText(), tokens);
}

std::string Window::GetDisplayText()
{
	// Display text as a std::string
	return mainTextBox->GetValue().ToStdString();
}

std::string Window::GetLastToken()
{
	Window::CreateTokens();

	// No tokens yet? Use the whole display
	return tokens.empty() ? GetDisplayText() : tokens.back();
}

int Window::CountCharInLastToken(char _charToCheckFor)
{
	std::string lastToken = GetLastToken();
	int characterAbundanceCount = (int)std::count(lastToken.begin(), lastToken.end(), _charToCheckFor);

	return characterAbundanceCount;
}

void Window::RemoveTrailingSpace(std::string& _stringToFix)
{
	if (!_stringToFix.empty() && _stringToFix.back() == ' ')
	{
		_stringToFix.pop_back();
	}
}

void Window::ResetFlags()
{
	// Back to how it starts when the app opens
	wasOperaterPressed = true;
	wasEqualsPressed = wasNumberPressed = wasNegationPressed = wasDecimalPressed = wasTrigPressed = false;
}

void Window::MarkNegationPressed()
{
	// Same flags every time something gets negated
	wasNegationPressed = true;
	wasOperaterPressed = wasEqualsPressed = false;
}

wxFont Window::ScaleFont(wxFont _font, double _startingSize, double _scale, double _smallestSize)
{
	// Scale it, but never below _smallestSize
	_font.SetFractionalPointSize(std::max(_startingSize * _scale, _smallestSize));
	return _font;
}

int Window::GetAmountOfButtons()
{
	return vecButtons.size();
}

wxBoxSizer* Window::WindowGetBoxSizers(int _position)
{
	return sizerButtonsAll[_position];
}
