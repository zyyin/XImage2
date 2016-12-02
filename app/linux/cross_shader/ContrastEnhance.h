#pragma once
#include "IAlgorithmStratety.h"
class ContrastEnhance :
	public IAlgorithmStratety
{
	DECLARE_DYNAMIC_CLASS()
public:
	ContrastEnhance();
	~ContrastEnhance();
	virtual bool TryRun();
	virtual const char* GetParametersName() { return "gain1,gain2"; }
};