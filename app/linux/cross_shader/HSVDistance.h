#pragma once
#include "IAlgorithmStratety.h"
class HSVDistance :
	public IAlgorithmStratety
{
	DECLARE_DYNAMIC_CLASS()
public:
	HSVDistance();
	~HSVDistance();
	
	virtual bool TryRun();
	virtual void SetParameter(const char* szKey, float fVal);
	virtual const char* GetParametersName() { return "svRatio,sv"; }
	double  GetDistance(Vec3b& B);
	float IsBlue(Vec3b& v); 
private:
	Mat m_sv;
	int m_nMinH;
	int m_nMaxH;
};

