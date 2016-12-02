#pragma once
#include "IAlgorithmStratety.h"
class WarmColor :
public IAlgorithmStratety
{
	DECLARE_DYNAMIC_CLASS()
public:
	WarmColor();
	~WarmColor();
	// input 2 or 3   output 2
	virtual bool TryRun();
	virtual const char* GetParametersName() { return "warm"; }
};
