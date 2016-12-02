#pragma once
#include "IAlgorithmStratety.h"
class ResampleDown :
	public IAlgorithmStratety
{
	DECLARE_DYNAMIC_CLASS()
public:
	ResampleDown();
	~ResampleDown();
	virtual bool TryRun();
	virtual const char* GetParametersName() { return ""; }
};

