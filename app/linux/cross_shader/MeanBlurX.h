#pragma once
#include "IAlgorithmStratety.h"
class MeanBlurX :
	public IAlgorithmStratety
{
	DECLARE_DYNAMIC_CLASS()
public:
	MeanBlurX();
	~MeanBlurX();
	virtual bool TryRun();
	virtual const char* GetParametersName() { return "maskSize"; }
};

