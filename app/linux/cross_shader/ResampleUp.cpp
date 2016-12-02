#include "stdafx.h"
#include "ResampleUp.h"


ResampleUp::ResampleUp()
{
	m_sink.push_back(ConnectPoint(INTERFACE_TYPE_IMAGE));
	m_src.push_back(ConnectPoint(INTERFACE_TYPE_IMAGE));
	m_passDownOrder.push_back(0);
}


ResampleUp::~ResampleUp()
{
}

bool ResampleUp::TryRun()
{
	if (!GetSinkState(0))
	{
		LOG_ERROR;
		return false;
	}

	pyrUp(m_sink[0].image, m_src[0].image);
	SetSinkState(0, false);
	return true;
}

IMPLEMENT_DYNAMIC_CLASS(ResampleUp)