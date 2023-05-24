#pragma once
#include "wx/wx.h"

class Window;
class ButtonFactory
{
public:
	void CreateButtons(wxWindow* _parentPTR, std::vector<wxButton*>& _vecButtons, wxSize& _buttonSize);
	void SetButtonsFont(wxFont _fontReference, std::vector<wxButton*> _vecButtons);
	void SetButtonsSpacers(int _spacerSize, std::vector<wxBoxSizer*> _sizers, wxTextCtrl& _mainTextBox, std::vector<wxButton*> _buttons);
	void SetButtonsEnabled(std::vector<wxButton*> _buttons, std::vector<bool> _status);
	
	// Unit Testing Assitance Code
	wxFont CreateFont();
	int GetID(int _position);
	std::vector<bool> GetEnabeledVector(Window* _windowObj);
	int GetAmountOfButtons(Window* _windowObj);
	int GetSpacerSize(Window* _windowObj);
	int GetBoxSizersOrient(Window* _windowObj, int _position);


};

