#pragma once
#include <stack>
#include <queue>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <cerrno>

class CalculatorProcessor
{
private:
	// Private CTOR so GetInstance has to be used
	CalculatorProcessor(){};

	// Cleaning up the equation
	void CreateTokens(std::string& _stringToRead, std::vector<std::string>& _tokens);
	static bool HasDivModByZero(const std::vector<std::string>& _tokens);

	// Shunting yard helpers
	bool ConvertToPostfix(std::vector<std::string>& _tokens, std::queue<std::string>& _outputQueue);
	bool SolvePostfix(std::queue<std::string>& _outputQueue, float& _result);
	float CalcTwoValues(float val1, float val2, char _op);
	std::string FormatAnswer(float _value);

	// Trig
	bool IsFunction(std::string& _stringToRead);
	void SolveTrig(std::string& _stringToRead);

	// Token checks
	bool IsNumber(std::string _stringToRead);
	static int OperatorPrecedence(char _op);
	static int GetStartIndex(const std::string& _stringToRead);
	static bool ToFloat(const std::string& _text, float& _value);

public:
	CalculatorProcessor(const CalculatorProcessor& other) = delete;
	void operator=(const CalculatorProcessor&) = delete;

	static CalculatorProcessor* GetInstance();

	// Shown instead of an answer when something's wrong
	static const std::string ErrorText;

	// Clean up the equation, then solve it
	void FixOperators(std::string& _toRead, std::vector<std::string>& _tokens);
	void CreateAndCalcTokens(std::string& _toRead, std::string& _answer);

	// Static helpers so the Window can use them too
	static bool IsOperator(char _charToCheck);
	static bool IsTrigSymbol(char _charToCheck);
	static void SplitIntoTokens(const std::string& _stringToRead, std::vector<std::string>& _tokens);
	static std::string JoinTokens(const std::vector<std::string>& _tokens);
};
