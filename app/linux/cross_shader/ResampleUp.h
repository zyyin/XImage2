#pragma once
#include "IAlgorithmStratety.h"
class ResampleUp :
	public IAlgorithmStratety
{
	DECLARE_DYNAMIC_CLASS()
public:
	ResampleUp();
	~ResampleUp();
	virtual bool TryRun();
	virtual const char* GetParametersName() { return ""; }
};

