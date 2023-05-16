#pragma once
class CalculatorProcessor
{
protected: 
	static CalculatorProcessor* instance;
	CalculatorProcessor(){};

public:
	// Copy CTOR deletes new copied objects (ONLY ONE OBJ)
	CalculatorProcessor(CalculatorProcessor& other) = delete;
	// Assignment Operator deletes new copied objects (ONLY ONE OBJ)
	void operator=(const CalculatorProcessor&) = delete;

	static CalculatorProcessor* GetInstance();

	void AddProcessor();
	void SubtractProcessor();
	void MultiplyProcessor();
	void DivideProcessor();
	void ModProcessor();
	void SINProcessor();
	void COSProcessor();
	void TANProcessor();


};

CalculatorProcessor* CalculatorProcessor::instance = nullptr;
