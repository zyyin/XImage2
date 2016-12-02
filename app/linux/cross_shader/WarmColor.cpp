#include "stdafx.h"
#include "WarmColor.h"


WarmColor::WarmColor()
{
	m_sink.push_back(ConnectPoint(INTERFACE_TYPE_IMAGE));
	m_src.push_back(ConnectPoint(INTERFACE_TYPE_IMAGE));

	m_passDownOrder.push_back(0);
}


WarmColor::~WarmColor()
{
}

bool WarmColor::TryRun()
{
	if (!GetSinkState(0))
		return false;

	if (m_sink[0].image.empty())
	{
		LOG_ERROR;
		return false;
	}
	int nWarm = m_mapParamerter["warm"];
	Mat yuv;
	vector<Mat> vec;
	cvtColor(m_sink[0].image, yuv, CV_BGR2YUV);
	split(yuv, vec);
	vec[1] += nWarm;
	vec[2] -= nWarm;
	merge(vec, yuv);
	cvtColor(yuv, m_src[0].image, CV_YUV2BGR);

	SetSinkState(0, false);
	return true;
}

IMPLEMENT_DYNAMIC_CLASS(WarmColor);