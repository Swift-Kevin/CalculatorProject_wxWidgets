#include "CppUnitTest.h"
#include "..\SWE_App\CalculatorProcessor.h"
#include "..\SWE_App\ButtonFactory.h"

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
		float answerAsFloat = 0.0;
		float expectedFloat = 0.0;


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
			answerAsFloat = stof(answerString);
			expectedFloat = -3.993562;

			Assert::AreEqual(expectedFloat, answerAsFloat);
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
			answerAsFloat = stof(answerString);
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
			answerAsFloat = stof(answerString);
			expectedFloat = 8413.231445;

			Assert::AreEqual(expectedFloat, answerAsFloat);
		}
	};

	TEST_CLASS(ButtonFactoryTests)
	{
	
	};
}
