#include "stdafx.h"
#include "ContrastEnhance.h"


ContrastEnhance::ContrastEnhance()
{
	m_sink.push_back(ConnectPoint(INTERFACE_TYPE_IMAGE));
	m_src.push_back(ConnectPoint(INTERFACE_TYPE_IMAGE));
	m_passDownOrder.push_back(0);
}


ContrastEnhance::~ContrastEnhance()
{
}
bool ContrastEnhance::TryRun()
{
	if (!GetSinkState(0))
	{
		LOG_ERROR;
		return false;
	}
	if (m_sink[0].image.empty())
	{
		LOG_ERROR;
		return false;
	}
	if (m_sink[0].image.type() != CV_8UC1)
	{
		LOG_ERROR;
		return false;
	}
	Mat lut(1, 256, CV_8U);
	Mat tmp;
	float nThreshold = m_mapParamerter["gain1"];
	float nRatio = m_mapParamerter["gain2"];
	nRatio /= 100;
	for (int i = 0; i < 256; i++)
	{
		lut.at<uchar>(i) = saturate_cast<uchar>((i - nThreshold) * nRatio + nThreshold);;
	}
	LUT(m_sink[0].image, lut, m_src[0].image);

	SetSinkState(0, false);
	return true;
}

IMPLEMENT_DYNAMIC_CLASS(ContrastEnhance)