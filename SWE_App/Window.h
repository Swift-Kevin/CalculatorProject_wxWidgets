#pragma once
#include "wx/wx.h"
#include "ButtonFactory.h"
#include "CalculatorProcessor.h"
#include <algorithm>

class Window : public wxFrame
{
private:
	ButtonFactory buttonFactoryObj;

	// Sizers
	wxBoxSizer* mainBox = nullptr;
	wxBoxSizer* textBoxRow = nullptr;
	wxBoxSizer* row1 = nullptr;
	wxBoxSizer* row2 = nullptr;
	wxBoxSizer* row3 = nullptr;
	wxBoxSizer* row4 = nullptr;
	wxBoxSizer* row5 = nullptr;
	wxBoxSizer* row6 = nullptr;
	std::vector<wxBoxSizer*> sizerButtonsAll;

	// Controls
	wxTextCtrl* mainTextBox = nullptr;
	wxStaticText* historyText = nullptr;
	std::vector<wxButton*> vecButtons;

	// Fonts and resizing
	wxFont genericFont;
	double buttonFontSize = 0, historyFontSize = 0, displayFontSize = 0;
	wxSize startingClientSize;

	// Calculator state
	std::vector<std::string> tokens;
	// Start false, otherwise they're random garbage
	bool wasOperaterPressed = false, wasEqualsPressed = false, wasNumberPressed = false, wasNegationPressed = false, wasDecimalPressed = false, wasTrigPressed = false;

	// Constructor helpers
	void SetUpSizers();
	void SetUpFonts();
	void SetUpDisplay();
	void SetUpButtons(wxSize _normalButtonSize, int _spacerSize);
	void SetUpKeyboardInput();
	void SetUpResizing(const wxSize& _normalButtonSize, int _spacerSize);

	// Event handlers
	void OnButtonClick(wxCommandEvent& _event);
	void OnKeyDown(wxKeyEvent& _event);
	void OnCharacterPressed(wxKeyEvent& _event);
	void OnResize(wxSizeEvent& _event);

	// Bigger button cases from OnButtonClick
	void EqualsCase();
	void DecimalCase();
	void NegativeCase();
	void BackspaceCase();
	void ClearCase();

	// Editing the equation
	void SetButtonNumTo(const wxString& _string);
	void ChangeSymbolInParsedString(const wxString& _string);
	void ChangeTrigSymbol(const wxString& _string);
	void CheckOperator();

	// Helpers
	void CreateTokens();
	std::string GetDisplayText();
	std::string GetLastToken();
	int CountCharInLastToken(char _charToCheckFor);
	void RemoveTrailingSpace(std::string& _stringToFix);
	void ResetFlags();
	void MarkNegationPressed();
	wxFont ScaleFont(wxFont _font, double _startingSize, double _scale, double _smallestSize);

public:
	Window();

	// Presses a button from code, keyboard input uses this too
	void PressButton(int _id);

	// Unit testing helpers
	int GetAmountOfButtons();
	wxBoxSizer* WindowGetBoxSizers(int _position);

	wxDECLARE_EVENT_TABLE();
};
