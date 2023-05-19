#pragma once
#include <stack>
#include <unordered_map>
#include <sstream>

class CalculatorProcessor
{
private:

protected: 
	static CalculatorProcessor* instance;
	CalculatorProcessor(){};

public:
	// Copy CTOR deletes new copied objects (ONLY ONE OBJ)
	CalculatorProcessor(CalculatorProcessor& other) = delete;
	// Assignment Operator deletes new copied objects (ONLY ONE OBJ)
	void operator=(const CalculatorProcessor&) = delete;

	static CalculatorProcessor* GetInstance();

	void FixOperators(std::string& _toRead, std::vector<std::string>& _tokens);
	void CreateAndCalcTokens(std::string& _toRead, std::string& _answer);
	void SolveTrig(std::string& _stringToRead);
	bool IsNumber(std::string _stringToRead);
	bool IsFunction(std::string& _stringToRead);
	int OperatorPrecedence(char _op);
	float CalcTwoValues(float val1, float val2, char _op);
	void CreateTokens(std::string& _stringToRead, std::vector<std::string>& _tokens);
};

