#pragma once
#include "wx/wx.h"

// Button IDs, shared by the Window and the factory
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

// Kind of button, decides its color
enum class ButtonType
{
	Number,
	Operator,
	Function,
	Clear
};

// Everything about one button, the factory keeps a table of these
struct ButtonInfo
{
	int id;
	const wchar_t* label;	// Text on the button
	const char* symbol;		// What it adds to the equation
	const wchar_t* keys;	// Keys that press it
	ButtonType type;
};

class Window;
class ButtonFactory
{
public:
	// Making buttons
	wxButton* CreateButton(wxWindow* _parentPTR, int _id, const wxString& _label, ButtonType _type, const wxSize& _buttonSize);
	void CreateButtons(wxWindow* _parentPTR, std::vector<wxButton*>& _vecButtons, wxSize& _buttonSize);

	// Button table lookups
	static const std::vector<ButtonInfo>& GetButtonTable();
	static const ButtonInfo* GetButtonInfo(int _id);
	static const ButtonInfo* GetButtonInfoForKey(wxChar _key);
	static wxButton* GetButton(const std::vector<wxButton*>& _buttons, int _id);

	// Font and layout
	void SetButtonsFont(wxFont _fontReference, const std::vector<wxButton*>& _vecButtons);
	void SetButtonsSpacers(int _spacerSize, const std::vector<wxBoxSizer*>& _sizers, wxTextCtrl& _mainTextBox, const std::vector<wxButton*>& _buttons, wxStaticText* _historyText = nullptr);

	// Unit testing helpers
	wxFont CreateFont();
	int GetID(int _position);
	int GetAmountOfButtons(Window* _windowObj);
	int GetSpacerSize(Window* _windowObj);
	int GetBoxSizersOrient(Window* _windowObj, int _position);
};

