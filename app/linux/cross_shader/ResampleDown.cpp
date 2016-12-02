#include "stdafx.h"
#include "ResampleDown.h"


ResampleDown::ResampleDown()
{
	m_sink.push_back(ConnectPoint(INTERFACE_TYPE_IMAGE));
	m_src.push_back(ConnectPoint(INTERFACE_TYPE_IMAGE));
	m_passDownOrder.push_back(0);
}


ResampleDown::~ResampleDown()
{
}

bool ResampleDown::TryRun()
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
	pyrDown(m_sink[0].image, m_src[0].image);
	SetSinkState(0, false);
	return true;
}


IMPLEMENT_DYNAMIC_CLASS(ResampleDown)