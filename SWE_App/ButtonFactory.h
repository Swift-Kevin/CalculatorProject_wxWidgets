#pragma once
#include "wx/wx.h"

class ButtonFactory
{
private:

public:
	static void CreateButtons(wxWindow* _parentPTR, std::vector<wxButton*>& _vecButtons, wxSize& _buttonSize);
	static void SetButtonsFont(wxFont _fontReference, std::vector<wxButton*> _vecButtons);
	static void SetButtonsSpacers(int _spacerSize, std::vector<wxBoxSizer*> _sizers, wxTextCtrl& _mainTextBox, std::vector<wxButton*> _buttons);
	static void SetButtonsEnabled(std::vector<wxButton*> _buttons, std::vector<bool> _status);
};

