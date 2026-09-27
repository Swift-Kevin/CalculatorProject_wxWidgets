#include "CalculatorProcessor.h"

// Shown when an equation can't be solved
const std::string CalculatorProcessor::ErrorText = "undef";

CalculatorProcessor* CalculatorProcessor::GetInstance()
{
	static CalculatorProcessor instance;
	return &instance;
}

void CalculatorProcessor::FixOperators(std::string& _stringToRead, std::vector<std::string>& _tokens)
{
	std::string tempReadString = " ";
	bool startCharOperatorOrSpace = true;
	bool endCharOperatorOrSpace = true;

	// Strip spaces and operators off the front
	while (startCharOperatorOrSpace)
	{
		if (IsOperator(_stringToRead[0]) || _stringToRead[0] == ' ')
		{
			tempReadString = _stringToRead;
			tempReadString.erase(0, 1);
			_stringToRead = tempReadString;
		}
		else
		{
			startCharOperatorOrSpace = false;
		}
	}

	for (size_t i = 0; i < _stringToRead.size(); ++i)
	{
		if (IsOperator(_stringToRead[i]))
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

	// Same thing for the end
	while (endCharOperatorOrSpace)
	{
		if (_stringToRead.size() < 1)
		{
			break;
		}
		else if (IsOperator(_stringToRead.back()) || IsTrigSymbol(_stringToRead.back()) ||
			_stringToRead.back() == ' ' || _stringToRead.back() == '~')
		{
			_stringToRead.pop_back();
		}
		else
		{
			endCharOperatorOrSpace = false;
		}
	}

	CreateTokens(_stringToRead, _tokens);

	if (HasDivModByZero(_tokens))
	{
		_stringToRead = ErrorText;
	}
}

void CalculatorProcessor::CreateTokens(std::string& _stringToRead, std::vector<std::string>& _tokens)
{
	SplitIntoTokens(_stringToRead, _tokens);

	for (size_t i = 0; i < _tokens.size(); ++i)
	{
		if (_tokens[i].size() == 1 && _tokens[i][0] == '~')
		{
			_tokens[i][0] = '0';
		}
		else if (_tokens[i][0] == '~')
		{
			_tokens[i][0] = '-';
		}

		if (_tokens[i].size() == 1 && _tokens[i][0] == '.')
		{
			_tokens[i] = '0';
		}

		if (_tokens[i].size() == 2 && _tokens[i][0] == '-' && _tokens[i][1] == '.')
		{
			_tokens[i] = '0';
		}
		else if (_tokens[i].size() > 2 && _tokens[i][0] == '-' && _tokens[i][1] == '.')
		{
			_tokens[i].insert(1, 2, '0');
		}
	}

	_stringToRead = JoinTokens(_tokens);
}

bool CalculatorProcessor::HasDivModByZero(const std::vector<std::string>& _tokens)
{
	// Check what comes after every / or %, all of these turn into 0
	for (size_t i = 0; i + 1 < _tokens.size(); ++i)
	{
		// are we dividing or modding?
		if (_tokens[i] == "%" || _tokens[i] == "/")
		{
			// is the next going to turn into a 0?
			if (_tokens[i + 1] == "0" || _tokens[i + 1] == "~" || _tokens[i + 1] == "." || _tokens[i + 1] == "~.")
			{
				return true;
			}
		}
	}

	return false;
}

void CalculatorProcessor::CreateAndCalcTokens(std::string& _toRead, std::string& _answer)
{
	// Stays undef unless everything solves
	_answer = ErrorText;

	if (_toRead == ErrorText)
	{
		return;
	}

	std::vector<std::string> _mockTokens;
	CalculatorProcessor::CreateTokens(_toRead, _mockTokens);

	float result = 0;

	if (_mockTokens.size() == 1)
	{
		IsFunction(_mockTokens[0]);
		if (ToFloat(_mockTokens[0], result))
		{
			_answer = FormatAnswer(result);
		}
		return;
	}

	// Shunting yard, convert to postfix then solve it
	std::queue<std::string> outputQueue;

	if (ConvertToPostfix(_mockTokens, outputQueue) && SolvePostfix(outputQueue, result))
	{
		_answer = FormatAnswer(result);
	}
}

bool CalculatorProcessor::ConvertToPostfix(std::vector<std::string>& _tokens, std::queue<std::string>& _outputQueue)
{
	std::stack<char> operatorsStack;

	for (size_t i = 0; i < _tokens.size(); ++i)
	{
		std::string& currToken = _tokens[i];
		if (currToken.empty() || currToken == " ")
		{
			continue;
		}

		if (IsNumber(currToken))
		{
			_outputQueue.push(currToken);
		}
		else if (IsFunction(currToken))
		{
			_outputQueue.push(currToken);
		}
		else if (IsOperator(currToken[0]))
		{
			// Anything with the same or higher precedence goes first
			while (!operatorsStack.empty() && 
				OperatorPrecedence(operatorsStack.top()) >= OperatorPrecedence(currToken[0]))
			{
				_outputQueue.push(std::string(1, operatorsStack.top()));
				operatorsStack.pop();
			}
			operatorsStack.push(currToken[0]);
		}
		// undef, not known
		else 
		{
			return false;
		}
	}

	// push operators over
	while (!operatorsStack.empty())
	{
		_outputQueue.push(std::string(1, operatorsStack.top()));
		operatorsStack.pop();
	}

	return true;
}

bool CalculatorProcessor::SolvePostfix(std::queue<std::string>& _outputQueue, float& _result)
{
	std::stack<float> values;

	while (!_outputQueue.empty())
	{
		std::string passString = _outputQueue.front();
		_outputQueue.pop();

		if (IsNumber(passString))
		{
			// Too big for a float
			float value = 0;
			if (!ToFloat(passString, value))
			{
				return false;
			}

			values.push(value);
			continue;
		}

		// Not a number or an operator, like a trig that couldn't be solved
		if (!IsOperator(passString[0]))
		{
			return false;
		}

		// Every operator needs two numbers
		if (values.size() < 2)
		{
			return false;
		}

		// Pop the top two values
		float num1 = values.top();
		values.pop();
		float num2 = values.top();
		values.pop();
		char operate = passString[0];

		// No dividing or modding by 0 (Ex: 5 / 0.0)
		if ((operate == '/' || operate == '%') && num1 == 0)
		{
			return false;
		}

		values.push(CalcTwoValues(num1, num2, operate));
	}

	// Only the answer should be left
	if (values.size() != 1)
	{
		return false;
	}

	_result = values.top();
	return true;
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

std::string CalculatorProcessor::FormatAnswer(float _value)
{
	// Too big for a float
	if (std::isnan(_value) || std::isinf(_value))
	{
		return ErrorText;
	}

	// Stops -0 from showing up as ~0
	if (_value == 0)
	{
		_value = 0;
	}

	std::string answer = std::to_string(_value);

	// Trim the trailing 0's and the '.' if it's a whole number
	// Ex: "49.500000" -> "49.5" and "100.000000" -> "100"
	if (answer.find('.') != std::string::npos)
	{
		while (answer.back() == '0')
		{
			answer.pop_back();
		}
		if (answer.back() == '.')
		{
			answer.pop_back();
		}
	}

	if (answer[0] == '-')
	{
		answer[0] = '~';
	}

	return answer;
}

bool CalculatorProcessor::IsFunction(std::string& _stringToRead)
{
	if (_stringToRead.size() < 2)
	{
		return false;
	}

	int index = GetStartIndex(_stringToRead);

	if (IsTrigSymbol(_stringToRead[index]))
	{
		SolveTrig(_stringToRead);
		return true;
	}
	else
	{
		return false;
	}
}

void CalculatorProcessor::SolveTrig(std::string& _stringToRead)
{
	std::string tempSubstring;
	int index = GetStartIndex(_stringToRead);

	// Too short to have a trig symbol, and substr would throw
	if (_stringToRead.size() < (size_t)index + 1)
	{
		_stringToRead = ErrorText;
		return;
	}

	tempSubstring = _stringToRead.substr(index + 1, _stringToRead.size());

	// No number or a bad one (Ex: "-s"), so it's undef
	float angle = 0;
	if (!ToFloat(tempSubstring, angle))
	{
		_stringToRead = ErrorText;
		return;
	}

	switch (_stringToRead[index])
	{
	case 's':
		_stringToRead = std::to_string(sin(angle));
		break;
	case 'c':
		_stringToRead = std::to_string(cos(angle));
		break;
	case 't':
		_stringToRead = std::to_string(tan(angle));
		break;
	default: break;
	}

	if (index == 1)
	{
		_stringToRead = _stringToRead[0] == '-'
			? _stringToRead.substr(index, _stringToRead.size())
			: '-' + _stringToRead;
	}
}

bool CalculatorProcessor::IsNumber(std::string _stringToRead)
{
	if (_stringToRead == "-")
	{
		return false;
	}

	int index = GetStartIndex(_stringToRead);

	for (size_t i = index; i < _stringToRead.size(); ++i)
	{
		if (_stringToRead[i] == '.')
		{
			continue;
		}
		else if (!isdigit(_stringToRead[i]))
		{
			return false;
		}
	}

	return true;
}

bool CalculatorProcessor::IsOperator(char _charToCheck)
{
	// Only operators have a precedence
	return OperatorPrecedence(_charToCheck) > 0;
}

bool CalculatorProcessor::IsTrigSymbol(char _charToCheck)
{
	return _charToCheck == 's' || _charToCheck == 'c' || _charToCheck == 't';
}

int CalculatorProcessor::OperatorPrecedence(char _op)
{
	if (_op == '+' || _op == '-')
	{
		return 1;
	}

	if (_op == '*' || _op == '/' || _op == '%')
	{
		return 2;
	}

	return 0;
}

int CalculatorProcessor::GetStartIndex(const std::string& _stringToRead)
{
	// Skip the negative sign if there is one
	return _stringToRead[0] == '-' ? 1 : 0;
}

void CalculatorProcessor::SplitIntoTokens(const std::string& _stringToRead, std::vector<std::string>& _tokens)
{
	_tokens.clear();

	std::stringstream lineStream(_stringToRead);
	std::string secondaryStringToParseWith;

	// Split it up by spaces
	while (std::getline(lineStream, secondaryStringToParseWith, ' '))
	{
		if (secondaryStringToParseWith == "")
		{
			continue;
		}
		else
		{
			_tokens.push_back(secondaryStringToParseWith);
		}
	}
}

std::string CalculatorProcessor::JoinTokens(const std::vector<std::string>& _tokens)
{
	// add tokens back up for display
	std::string joinedString = "";
	for (size_t i = 0; i < _tokens.size(); ++i)
	{
		joinedString += _tokens[i] + ' ';
	}

	if (joinedString.size() > 0)
	{
		if (joinedString[joinedString.size() - 1] == ' ')
		{
			joinedString.pop_back();
		}
	}

	return joinedString;
}

bool CalculatorProcessor::ToFloat(const std::string& _text, float& _value)
{
	// Same as stof but gives back false instead of throwing
	const char* start = _text.c_str();
	char* end = nullptr;
	errno = 0;
	_value = std::strtof(start, &end);

	return end != start && errno != ERANGE;
}
