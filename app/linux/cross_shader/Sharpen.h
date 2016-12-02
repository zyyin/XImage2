#pragma once
#include "IAlgorithmStratety.h"
class Sharpen :
	public IAlgorithmStratety
{
	DECLARE_DYNAMIC_CLASS()
public:
	Sharpen();
	~Sharpen();
	virtual bool TryRun();
	virtual const char* GetParametersName() { return "sharpen"; }
};

