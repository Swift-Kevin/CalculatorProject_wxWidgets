#include "CalculatorProcessor.h"

CalculatorProcessor* CalculatorProcessor::GetInstance()
{
	if (instance == nullptr)
		instance = new CalculatorProcessor();

	return instance;
}

void CalculatorProcessor::AddProcessor()
{
}

void CalculatorProcessor::SubtractProcessor()
{
}

void CalculatorProcessor::MultiplyProcessor()
{
}

void CalculatorProcessor::DivideProcessor()
{
}

void CalculatorProcessor::ModProcessor()
{
}

void CalculatorProcessor::SINProcessor()
{
}

void CalculatorProcessor::COSProcessor()
{
}

void CalculatorProcessor::TANProcessor()
{
}
