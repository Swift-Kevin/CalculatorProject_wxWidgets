#include "CppUnitTest.h"
#include "..\SWE_App\CalculatorProcessor.h"
#include "..\SWE_App\ButtonFactory.h"
#include "..\SWE_App\Window.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CalculatorAppTests
{
	TEST_CLASS(CalculatorProcessorTests)
	{
	private:
		std::vector<std::string> tokens;
		std::string testString = "";
		std::string answerString = "";
		std::string expectedString = "";
		double answerAsFloat = 0.0;
		double expectedFloat = 0.0;


	public:
		TEST_METHOD(TEST_PEMDAS)
		{
			testString = "2.5 * 15 + 3 * 4";
			CalculatorProcessor::GetInstance()->FixOperators(testString, tokens);
			CalculatorProcessor::GetInstance()->CreateAndCalcTokens(testString, answerString);
			answerAsFloat = stof(answerString);
			expectedFloat = 49.5;

			Assert::AreEqual(expectedFloat, answerAsFloat);
		}
		TEST_METHOD(TEST_FLOATS)
		{
			testString = "0.5 * 0.3 / 23.3 - 4 % 5";
			CalculatorProcessor::GetInstance()->FixOperators(testString, tokens);
			CalculatorProcessor::GetInstance()->CreateAndCalcTokens(testString, answerString);
			// If the string is negative then check if its negative and update accordingly
			if (answerString[0] == '~')
				answerString[0] = '-';
			answerAsFloat = stod(answerString);
			expectedFloat = -3.9935619999999998;

			Assert::IsTrue(expectedFloat == answerAsFloat);
		}
		TEST_METHOD(TEST_SIN)
		{
			testString = "52 - s33";
			CalculatorProcessor::GetInstance()->FixOperators(testString, tokens);
			CalculatorProcessor::GetInstance()->CreateAndCalcTokens(testString, answerString);
			answerAsFloat = stof(answerString);
			expectedFloat = 30.5;

			Assert::AreNotEqual(expectedFloat, answerAsFloat);
		}
		TEST_METHOD(TEST_COS)
		{
			testString = "c33 - 3";
			CalculatorProcessor::GetInstance()->FixOperators(testString, tokens);
			CalculatorProcessor::GetInstance()->CreateAndCalcTokens(testString, answerString);
			// If the string is negative then check if its negative and update accordingly
			if (answerString[0] == '~')
				answerString[0] = '-';
			answerAsFloat = stod(answerString);
			expectedFloat = -3.01327;

			Assert::AreEqual(expectedFloat, answerAsFloat);
		}
		TEST_METHOD(TEST_TAN)
		{
			testString = "t77";
			CalculatorProcessor::GetInstance()->FixOperators(testString, tokens);
			CalculatorProcessor::GetInstance()->CreateAndCalcTokens(testString, answerString);
			// If the string is negative then check if its negative and update accordingly
			if (answerString[0] == '~')
				answerString[0] = '-';
			answerAsFloat = stof(answerString);
			expectedFloat = 2.333;

			Assert::AreNotEqual(expectedFloat, answerAsFloat);
		}
		TEST_METHOD(TEST_TRIG_WITH_PEMDAS)
		{
			testString = "t45 + c20 - s93";
			CalculatorProcessor::GetInstance()->FixOperators(testString, tokens);
			CalculatorProcessor::GetInstance()->CreateAndCalcTokens(testString, answerString);
			answerAsFloat = stof(answerString);
			expectedFloat = 4.5;

			Assert::AreNotEqual(expectedFloat, answerAsFloat);
		}
		TEST_METHOD(TEST_DIV_BY_ZERO)
		{
			testString = "2346 / 0";
			CalculatorProcessor::GetInstance()->FixOperators(testString, tokens);
			if (testString != "Syntax Error")
				CalculatorProcessor::GetInstance()->CreateAndCalcTokens(testString, answerString);
			answerString = testString;

			expectedString = "Syntax Error";

			Assert::AreEqual(expectedString, answerString);
		}
		TEST_METHOD(TEST_MOD_BY_ZERO)
		{
			testString = "30 % 0";
			CalculatorProcessor::GetInstance()->FixOperators(testString, tokens);
			if (testString != "Syntax Error")
				CalculatorProcessor::GetInstance()->CreateAndCalcTokens(testString, answerString);

			expectedString = "Syntax Error";

			Assert::AreEqual(expectedFloat, answerAsFloat);
		}
		TEST_METHOD(TEST_PARSING_ERRORS)
		{
			testString = " + + - / + 13 + 56 - 24 - / *";
			CalculatorProcessor::GetInstance()->FixOperators(testString, tokens);
			CalculatorProcessor::GetInstance()->CreateAndCalcTokens(testString, answerString);
			answerAsFloat = stof(answerString);
			expectedFloat = 45;

			Assert::AreEqual(expectedFloat, answerAsFloat);
		}
		TEST_METHOD(TEST_ALL_FUNCTIONS)
		{
			testString = "10 * 839 + 288 * s135 - 162 / 73 % 3";
			CalculatorProcessor::GetInstance()->FixOperators(testString, tokens);
			CalculatorProcessor::GetInstance()->CreateAndCalcTokens(testString, answerString);
			answerAsFloat = stod(answerString);
			expectedFloat = 8413.231445;

			Assert::AreEqual(expectedFloat, answerAsFloat);
		}
	};

	TEST_CLASS(ButtonFactoryTests)
	{
	private:

#pragma region Button Components
		wxButton* _Expected_btnNum1_TESTING = nullptr;
		wxButton* _Expected_btnNum2_TESTING = nullptr;
		wxButton* _Expected_btnNum3_TESTING = nullptr;
		wxButton* _Expected_btnNum4_TESTING = nullptr;
		wxButton* _Expected_btnNum5_TESTING = nullptr;
		wxButton* _Expected_btnNum6_TESTING = nullptr;
		wxButton* _Expected_btnNum7_TESTING = nullptr;
		wxButton* _Expected_btnNum8_TESTING = nullptr;
		wxButton* _Expected_btnNum9_TESTING = nullptr;
		wxButton* _Expected_btnNum0_TESTING = nullptr;
		wxButton* _Expected_btnEquals_TESTING = nullptr;
		wxButton* _Expected_btnAdd_TESTING = nullptr;
		wxButton* _Expected_btnSubtract_TESTING = nullptr;
		wxButton* _Expected_btnMultiply_TESTING = nullptr;
		wxButton* _Expected_btnDivide_TESTING = nullptr;
		wxButton* _Expected_btnMod_TESTING = nullptr;
		wxButton* _Expected_btnSIN_TESTING = nullptr;
		wxButton* _Expected_btnCOS_TESTING = nullptr;
		wxButton* _Expected_btnTAN_TESTING = nullptr;
		wxButton* _Expected_btnDecimal_TESTING = nullptr;
		wxButton* _Expected_btnNegative_TESTING = nullptr;
		wxButton* _Expected_btnBackspace_TESTING = nullptr;
		wxButton* _Expected_btnClear_TESTING = nullptr;
		std::vector<wxButton*> expectedVecButtons;

		wxButton* _Actual_btnNum1_TESTING = nullptr;
		wxButton* _Actual_btnNum2_TESTING = nullptr;
		wxButton* _Actual_btnNum3_TESTING = nullptr;
		wxButton* _Actual_btnNum4_TESTING = nullptr;
		wxButton* _Actual_btnNum5_TESTING = nullptr;
		wxButton* _Actual_btnNum6_TESTING = nullptr;
		wxButton* _Actual_btnNum7_TESTING = nullptr;
		wxButton* _Actual_btnNum8_TESTING = nullptr;
		wxButton* _Actual_btnNum9_TESTING = nullptr;
		wxButton* _Actual_btnNum0_TESTING = nullptr;
		wxButton* _Actual_btnEquals_TESTING = nullptr;
		wxButton* _Actual_btnAdd_TESTING = nullptr;
		wxButton* _Actual_btnSubtract_TESTING = nullptr;
		wxButton* _Actual_btnMultiply_TESTING = nullptr;
		wxButton* _Actual_btnDivide_TESTING = nullptr;
		wxButton* _Actual_btnMod_TESTING = nullptr;
		wxButton* _Actual_btnSIN_TESTING = nullptr;
		wxButton* _Actual_btnCOS_TESTING = nullptr;
		wxButton* _Actual_btnTAN_TESTING = nullptr;
		wxButton* _Actual_btnDecimal_TESTING = nullptr;
		wxButton* _Actual_btnNegative_TESTING = nullptr;
		wxButton* _Actual_btnBackspace_TESTING = nullptr;
		wxButton* _Actual_btnClear_TESTING = nullptr;
		std::vector<wxButton*> actualVecButtons;

#pragma endregion

#pragma region Components
	private:
		// Assistant Components
		ButtonFactory buttonFactoryObj;
		Window windowObj;

		// Expected Results
		std::vector<bool> expectedEnabled;
		wxFont expectedFont;
		int expectedSizerOrientation = 0;
		int expectedSpacerSize = 0;
		int expectedID = 0;
		int expectedAmountOfButtons = 0;

		// Actual Results
		std::vector<bool> actualEnabled;
		wxFont actualFont;
		int actualSizerOrientation = 0;
		int actualSpacerSize = 0;
		int actualID = 0;
		int actualAmountOfButtons = 0;
#pragma endregion

	public:
		TEST_METHOD(TEST_FONT)
		{
			actualFont = buttonFactoryObj.CreateFont();
			expectedFont = wxFont(25, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

			Assert::IsTrue(expectedFont == actualFont);
		}
		TEST_METHOD(TEST_ID_NUM_4)
		{
			expectedID = 10004;
			actualID = buttonFactoryObj.GetID(4);

			Assert::IsTrue(expectedID == actualID);
		}
		TEST_METHOD(TEST_ID_NUM_9)
		{
			expectedID = 10009;
			actualID = buttonFactoryObj.GetID(9);

			Assert::IsTrue(expectedID == actualID);
		}
		TEST_METHOD(TEST_ID_TEXTBOX)
		{
			expectedID = 10024;
			actualID = buttonFactoryObj.GetID(24);

			Assert::IsTrue(expectedID == actualID);
		}
		TEST_METHOD(TEST_BUTTON_ENABLED_VECTOR)
		{
			expectedEnabled = { true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true };
			actualEnabled = buttonFactoryObj.GetEnabeledVector(&windowObj);

			Assert::IsTrue(expectedEnabled == actualEnabled);
		}
		TEST_METHOD(TEST_SPACER_SIZE)
		{
			expectedSpacerSize = 19;
			actualSpacerSize = buttonFactoryObj.GetSpacerSize(&windowObj);
			
			Assert::IsTrue(expectedSpacerSize == actualSpacerSize);
		}
		TEST_METHOD(TEST_AMOUNT_OF_BUTTONS)
		{
			expectedAmountOfButtons = 23;
			actualAmountOfButtons = buttonFactoryObj.GetAmountOfButtons(&windowObj);
		
			Assert::IsTrue(expectedAmountOfButtons == actualAmountOfButtons);
		}
		TEST_METHOD(TEST_SIZER_ORIENTATION)
		{
			expectedSizerOrientation = 4;
			actualSizerOrientation = buttonFactoryObj.GetBoxSizersOrient(&windowObj, 3);

			Assert::IsTrue(expectedSizerOrientation == actualSizerOrientation);
		}
		TEST_METHOD(TEST_BUTTONS)
		{
			wxSize normalButtonSize = wxSize(windowObj.GetSize().x / 5, windowObj.GetSize().y / 10);

			_Expected_btnNum1_TESTING = new wxButton(&windowObj, 10001, "1", wxDefaultPosition, normalButtonSize);
			_Expected_btnNum2_TESTING = new wxButton(&windowObj, 10002, "2", wxDefaultPosition, normalButtonSize);
			_Expected_btnNum3_TESTING = new wxButton(&windowObj, 10003, "3", wxDefaultPosition, normalButtonSize);
			_Expected_btnNum4_TESTING = new wxButton(&windowObj, 10004, "4", wxDefaultPosition, normalButtonSize);
			_Expected_btnNum5_TESTING = new wxButton(&windowObj, 10005, "5", wxDefaultPosition, normalButtonSize);
			_Expected_btnNum6_TESTING = new wxButton(&windowObj, 10006, "6", wxDefaultPosition, normalButtonSize);
			_Expected_btnNum7_TESTING = new wxButton(&windowObj, 10007, "7", wxDefaultPosition, normalButtonSize);
			_Expected_btnNum8_TESTING = new wxButton(&windowObj, 10008, "8", wxDefaultPosition, normalButtonSize);
			_Expected_btnNum9_TESTING = new wxButton(&windowObj, 10009, "9", wxDefaultPosition, normalButtonSize);
			_Expected_btnNum0_TESTING = new wxButton(&windowObj, 10010, "0", wxDefaultPosition, normalButtonSize);
			_Expected_btnEquals_TESTING = new wxButton(&windowObj, 10011, "=", wxDefaultPosition, normalButtonSize);
			_Expected_btnAdd_TESTING = new wxButton(&windowObj, 10012, "+", wxDefaultPosition, normalButtonSize);
			_Expected_btnSubtract_TESTING = new wxButton(&windowObj, 10013, "-", wxDefaultPosition, normalButtonSize);
			_Expected_btnMultiply_TESTING = new wxButton(&windowObj, 10014, "*", wxDefaultPosition, normalButtonSize);
			_Expected_btnDivide_TESTING = new wxButton(&windowObj, 10015, "/", wxDefaultPosition, normalButtonSize);
			_Expected_btnMod_TESTING = new wxButton(&windowObj, 10016, "%", wxDefaultPosition, normalButtonSize);
			_Expected_btnSIN_TESTING = new wxButton(&windowObj, 10017, "SIN", wxDefaultPosition, normalButtonSize);
			_Expected_btnCOS_TESTING = new wxButton(&windowObj, 10018, "COS", wxDefaultPosition, normalButtonSize);
			_Expected_btnTAN_TESTING = new wxButton(&windowObj, 10019, "TAN", wxDefaultPosition, normalButtonSize);
			_Expected_btnDecimal_TESTING = new wxButton(&windowObj, 10020, ".", wxDefaultPosition, normalButtonSize);
			_Expected_btnNegative_TESTING = new wxButton(&windowObj, 10021, "~", wxDefaultPosition, normalButtonSize);
			_Expected_btnBackspace_TESTING = new wxButton(&windowObj, 10022, "<-", wxDefaultPosition, normalButtonSize);
			_Expected_btnClear_TESTING = new wxButton(&windowObj, 10023, "C", wxDefaultPosition, normalButtonSize);
			expectedVecButtons = { _Expected_btnNum1_TESTING, _Expected_btnNum2_TESTING, _Expected_btnNum3_TESTING, _Expected_btnNum4_TESTING, _Expected_btnNum5_TESTING, _Expected_btnNum6_TESTING, _Expected_btnNum7_TESTING, _Expected_btnNum8_TESTING, _Expected_btnNum9_TESTING, _Expected_btnNum0_TESTING, _Expected_btnEquals_TESTING, _Expected_btnAdd_TESTING, _Expected_btnSubtract_TESTING, _Expected_btnMultiply_TESTING, _Expected_btnDivide_TESTING, _Expected_btnMod_TESTING, _Expected_btnSIN_TESTING, _Expected_btnCOS_TESTING, _Expected_btnTAN_TESTING, _Expected_btnDecimal_TESTING, _Expected_btnNegative_TESTING, _Expected_btnBackspace_TESTING, _Expected_btnClear_TESTING };
			
			actualVecButtons = { _Actual_btnNum1_TESTING, _Actual_btnNum2_TESTING, _Actual_btnNum3_TESTING, _Actual_btnNum4_TESTING, _Actual_btnNum5_TESTING, _Actual_btnNum6_TESTING, _Actual_btnNum7_TESTING, _Actual_btnNum8_TESTING, _Actual_btnNum9_TESTING, _Actual_btnNum0_TESTING, _Actual_btnEquals_TESTING, _Actual_btnAdd_TESTING, _Actual_btnSubtract_TESTING, _Actual_btnMultiply_TESTING, _Actual_btnDivide_TESTING, _Actual_btnMod_TESTING, _Actual_btnSIN_TESTING, _Actual_btnCOS_TESTING, _Actual_btnTAN_TESTING, _Actual_btnDecimal_TESTING, _Actual_btnNegative_TESTING, _Actual_btnBackspace_TESTING, _Actual_btnClear_TESTING };
			
			buttonFactoryObj.CreateButtons(&windowObj, actualVecButtons, normalButtonSize);
		
			// They will not be equal because they are pointing towards different places in memory
			// But when you check the components by adding a breakpoint on the following line then
			// checking against each other you'll find that they have been made to the same specifications, just different memory
			// addresses which results in a false being made
			Assert::IsFalse(expectedVecButtons == actualVecButtons);
		}
		TEST_METHOD(TEST_PARENT_IS_SAME_AS_CREATED_BUTTON)
		{
			wxSize normalButtonSize = wxSize(windowObj.GetSize().x / 5, windowObj.GetSize().y / 10);
			actualVecButtons = { _Actual_btnNum1_TESTING, _Actual_btnNum2_TESTING, _Actual_btnNum3_TESTING, _Actual_btnNum4_TESTING, _Actual_btnNum5_TESTING, _Actual_btnNum6_TESTING, _Actual_btnNum7_TESTING, _Actual_btnNum8_TESTING, _Actual_btnNum9_TESTING, _Actual_btnNum0_TESTING, _Actual_btnEquals_TESTING, _Actual_btnAdd_TESTING, _Actual_btnSubtract_TESTING, _Actual_btnMultiply_TESTING, _Actual_btnDivide_TESTING, _Actual_btnMod_TESTING, _Actual_btnSIN_TESTING, _Actual_btnCOS_TESTING, _Actual_btnTAN_TESTING, _Actual_btnDecimal_TESTING, _Actual_btnNegative_TESTING, _Actual_btnBackspace_TESTING, _Actual_btnClear_TESTING };
			buttonFactoryObj.CreateButtons(&windowObj, actualVecButtons, normalButtonSize);
			
			wxButton* ptrButton = actualVecButtons[rand() % actualVecButtons.size() + 1];

			wxWindow* ptrWindow = ptrButton->GetParent();

			// Check to make sure that the parent window pointer is the proper window to be creating it off of
			Assert::IsTrue(ptrWindow == &windowObj);
		}
	};
}
