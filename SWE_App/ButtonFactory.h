#pragma once
#include "wx/wx.h"

class ButtonFactory
{
private:

public:
	static wxButton* CreateButton(wxWindow* _parentPTR, int _id, std::string _displayNum, wxSize& _buttonSize,const wxPoint& _position= wxDefaultPosition);
	static void SetButtonsFont(wxFont _fontReference, std::vector<wxButton*> _vecButtons);
	static void SetButtonsSpacers(int _spacerSize, std::vector<wxBoxSizer*> _sizers, wxTextCtrl& _mainTextBox, std::vector<wxButton*> _buttons);
	static void SetButtonsEnabled(std::vector<wxButton*> _buttons, std::vector<bool> _status);
};

