#pragma once
#include "IAlgorithmStratety.h"
class ImageProbe :
	public IAlgorithmStratety
{
	DECLARE_DYNAMIC_CLASS()
public:
	ImageProbe();
	~ImageProbe();
	virtual bool TryRun();
	virtual const char* GetParametersName() { return "null"; }
};

