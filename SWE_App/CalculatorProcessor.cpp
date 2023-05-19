#include "CalculatorProcessor.h"

CalculatorProcessor* CalculatorProcessor::instance = nullptr;

CalculatorProcessor* CalculatorProcessor::GetInstance()
{
	if (instance == nullptr)
		instance = new CalculatorProcessor();

	return instance;
}

void CalculatorProcessor::FixOperators(std::string& _stringToRead, std::vector<std::string>& _tokens)
{
	std::string tempReadString = " ";
	bool startCharOperatorOrSpace = true;
	bool endCharOperatorOrSpace = true;
	int countOfOperators = 0;

	// Loop through and make sure to remove all ' ' or operators at the beginning
	// if there are no numbers to go off of.
	while (startCharOperatorOrSpace)
	{
		if (_stringToRead[0] == '+' || _stringToRead[0] == '-' ||
			_stringToRead[0] == '*' || _stringToRead[0] == '/' ||
			_stringToRead[0] == '%' || _stringToRead[0] == ' ')
		{
			tempReadString = _stringToRead;
			tempReadString.erase(0, 1);
			_stringToRead = tempReadString;
		}
		else startCharOperatorOrSpace = false;
	}

	for (size_t i = 0; i < _stringToRead.size(); ++i)
	{
		if (_stringToRead[i] == '+' || _stringToRead[i] == '-' ||
			_stringToRead[i] == '*' || _stringToRead[i] == '/' ||
			_stringToRead[i] == '%')
		{
			if (_stringToRead[i + 1] != ' ')
			{
				_stringToRead.insert(i + 1, i + 1, ' ');
				--i;
				continue;
			}
			else if (_stringToRead[i - 1] != ' ')
			{
				_stringToRead.insert(--i, ++i, ' ');
				--i;
			}
		}
	}

	// Go back through and make sure there are none at the end aswell.
	while (endCharOperatorOrSpace)
	{
		if (_stringToRead[_stringToRead.size() - 1] == '+' || _stringToRead[_stringToRead.size() - 1] == '-' ||
			_stringToRead[_stringToRead.size() - 1] == '*' || _stringToRead[_stringToRead.size() - 1] == '/' ||
			_stringToRead[_stringToRead.size() - 1] == '%' || _stringToRead[_stringToRead.size() - 1] == ' ')
			_stringToRead.pop_back(); // takes the last element off if it is an operator or a space
		else endCharOperatorOrSpace = false;
	}

	CreateTokens(_stringToRead, _tokens);
	_stringToRead = "";
	for (size_t i = 0; i < _tokens.size(); ++i)
		_stringToRead += _tokens[i] + ' ';
	if (_stringToRead[_stringToRead.size() - 1] == ' ')
		_stringToRead.pop_back();
}

void CalculatorProcessor::CreateAndCalcTokens(std::string& _toRead, std::string& _answer)
{
	std::string passString;
	std::stringstream lineStream(_toRead);
	std::stack<std::string> values;
	std::stack<char> operatorsStack;

	while (std::getline(lineStream, passString, ' '))
	{
		if (passString.empty() || passString == " ") continue;
		bool isStringNumber = IsNumber(passString);
		bool isStringFunction = IsFunction(passString);

		/*
			I just want it to be noted here :
			I thought of using a nested turnary, but opted for the more
			sane approach as to help with readability and also well, losing my mind.
			But turnarys are great! Use them if your doing single line if-else statements!
			Never do a nested turnary.
			Ex: isStringNumber ? values.push(passString) : isStringFunction ? values.push(passString) : continue;
		*/

		if (isStringNumber)
			values.push(passString);
		else if (isStringFunction)
			values.push(passString);
		else
		{
			while (!operatorsStack.empty() && OperatorPrecedence(operatorsStack.top()) >= OperatorPrecedence(passString[0]))
			{
				// take first two values and pop them off
				float num1 = stof(values.top());
				values.pop();
				float num2 = stof(values.top());
				values.pop();
				char operate = operatorsStack.top();
				operatorsStack.pop();

				values.push(std::to_string(CalcTwoValues(num1, num2, operate)));

			}
			operatorsStack.push(passString[0]);
		}
	}

	// All tokens should be read and applied at this point. 
	while (!operatorsStack.empty())
	{
		float num1 = stof(values.top());
		values.pop();
		float num2 = stof(values.top());
		values.pop();

		char operate = operatorsStack.top();
		operatorsStack.pop();

		values.push(std::to_string(CalcTwoValues(num1, num2, operate)));
	}

	if (stoi(values.top()) == stof(values.top()))
		_answer = std::to_string(stoi(values.top()));
	else _answer = values.top();

	if (stof(_answer) < 0)
		_answer[0] = '~';
}

bool CalculatorProcessor::IsNumber(std::string _stringToRead)
{
	if (_stringToRead == "-")
		return false;

	int index = 0;
	_stringToRead[0] == '-' ? index = 1 : index = 0;

	for (size_t i = index; i < _stringToRead.size(); ++i)
		if (_stringToRead[i] == '.') continue;
		else if (!isdigit(_stringToRead[i]))
			return false;

	return true;
}

bool CalculatorProcessor::IsFunction(std::string& _stringToRead)
{
	if (_stringToRead.size() < 2) return false;

	int index = 0;
	_stringToRead[0] == '-' ? index = 1 : index = 0;

	if (_stringToRead[index] == 's' || _stringToRead[index] == 'c' || _stringToRead[index] == 't')
	{
		SolveTrig(_stringToRead);
		return true;
	}
	else return false;
}

int CalculatorProcessor::OperatorPrecedence(char _op)
{
	if (_op == '+' || _op == '-')
		return 1;
	if (_op == '*' || _op == '/' || _op == '%')
		return 2;
	return 0;
}

float CalculatorProcessor::CalcTwoValues(float val1, float val2, char _op)
{
	float answer = 0;
	switch (_op)
	{
	case '%':
		answer = fmod(val2, val1);
		break;
	case '*':
		answer = val1 * val2;
		break;
	case '+':
		answer = val1 + val2;
		break;
	case '-':
		answer = -val1 + val2;
		break;
	case '/':
		answer = val2 / val1;
		break;
	}
	return answer;
}

void CalculatorProcessor::SolveTrig(std::string& _stringToRead)
{
	std::string tempSubstring;
	int index = 0;
	_stringToRead[0] == '-' ? index = 1 : index = 0;

	tempSubstring = _stringToRead.substr(index + 1, _stringToRead.size());

	switch (_stringToRead[index])
	{
	case 's':
		_stringToRead = std::to_string(sin(stof(tempSubstring)));
		break;
	case 'c':
		_stringToRead = std::to_string(cos(stof(tempSubstring)));
		break;
	case 't':
		_stringToRead = std::to_string(tan(stof(tempSubstring)));
		break;
	default: break;
	}

	if (index == 1)
	{
		if (_stringToRead[0] == '-')
			_stringToRead = _stringToRead.substr(index, _stringToRead.size());
		else _stringToRead = '-' + _stringToRead;
	}
}

void CalculatorProcessor::CreateTokens(std::string& _stringToRead, std::vector<std::string>& _tokens)
{ 
	_tokens.clear();

	std::stringstream lineStream(_stringToRead);
	std::string secondaryStringToParseWith;

	// Collects all tokens in the string from mainTextBox
	while (std::getline(lineStream, secondaryStringToParseWith, ' '))
	{
		if (secondaryStringToParseWith == "")
			continue;
		else
			_tokens.push_back(secondaryStringToParseWith);
	}

	for (size_t i = 0; i < _tokens.size(); ++i)
	{
		if (_tokens[i][0] == '~')
			_tokens[i][0] = '-';

		if (_tokens[i].size() == 1 && _tokens[i][0] == '.')
			_tokens[i] = '0';

		if (_tokens[i].size() == 2 && _tokens[i][0] == '-' && _tokens[i][1] == '.')
			_tokens[i] = '0';
		else if (_tokens[i].size() > 2 && _tokens[i][0] == '-' && _tokens[i][1] == '.')
			_tokens[i].insert(1, 2, '0');
	}
}