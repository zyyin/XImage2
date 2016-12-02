#include "stdafx.h"
#include "Sharpen.h"


Sharpen::Sharpen()
{
	m_sink.push_back(ConnectPoint(INTERFACE_TYPE_IMAGE));
	m_src.push_back(ConnectPoint(INTERFACE_TYPE_IMAGE));
	m_passDownOrder.push_back(0);
}


Sharpen::~Sharpen()
{
}

bool Sharpen::TryRun()
{
	if (m_sink[0].image.empty())
	{
		LOG_ERROR;
		return false;
	}
	if (!GetSinkState(0))
	{
		LOG_ERROR;
		return false;
	}
	float fSharpen = m_mapParamerter["sharpen"];

	Mat tmp;
	blur(m_sink[0].image, tmp, Size(fSharpen, fSharpen));
	cv::addWeighted(m_sink[0].image, 1.5, tmp, -0.5, 0, m_src[0].image);
	SetSinkState(0, false);
	return true;
}

IMPLEMENT_DYNAMIC_CLASS(Sharpen)