#include "wx/wx.h"
#include "wx/tokenzr.h"
#include <queue>
#include <sstream>

class Window : public wxFrame
{
	wxBoxSizer* mainBox = nullptr;
	wxBoxSizer* textBoxRow = nullptr;
	wxBoxSizer* row1 = nullptr;
	wxBoxSizer* row2 = nullptr;
	wxBoxSizer* row3 = nullptr;
	wxBoxSizer* row4 = nullptr;
	wxBoxSizer* row5 = nullptr;
	wxBoxSizer* row6 = nullptr;

	wxButton* btnNum1 = nullptr;
	wxButton* btnNum2 = nullptr;
	wxButton* btnNum3 = nullptr;
	wxButton* btnNum4 = nullptr;
	wxButton* btnNum5 = nullptr;
	wxButton* btnNum6 = nullptr;
	wxButton* btnNum7 = nullptr;
	wxButton* btnNum8 = nullptr;
	wxButton* btnNum9 = nullptr;
	wxButton* btnNum0 = nullptr;
	wxButton* btnEquals = nullptr;
	wxButton* btnAdd = nullptr;
	wxButton* btnSubtract = nullptr;
	wxButton* btnMultiply = nullptr;
	wxButton* btnDivide = nullptr;
	wxButton* btnMod = nullptr;
	wxButton* btnSIN = nullptr;
	wxButton* btnCOS = nullptr;
	wxButton* btnTAN = nullptr;
	wxButton* btnDecimal = nullptr;
	wxButton* btnNegative = nullptr;
	wxButton* btnBackspace = nullptr;
	wxButton* btnClear = nullptr;
	wxTextCtrl* mainTextBox = nullptr;

	std::string parseString;
	std::vector<std::string> tokens;
	std::queue<float> operandsQueue;
	std::queue<char> operatorsQueue;

	int charIndex = 0;
	wxString answer;
	

public:
	Window();
	void OnButtonClick(wxCommandEvent& _event);
	void ParseStringCalculate();

	wxDECLARE_EVENT_TABLE();
};
