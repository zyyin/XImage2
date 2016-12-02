#include "stdafx.h"
#include "MeanBlurX.h"


MeanBlurX::MeanBlurX()
{
	m_sink.push_back(ConnectPoint(INTERFACE_TYPE_IMAGE));
	m_src.push_back(ConnectPoint(INTERFACE_TYPE_IMAGE));
	m_passDownOrder.push_back(0);
}


MeanBlurX::~MeanBlurX()
{
}
bool MeanBlurX::TryRun()
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

	int nMaskSize = m_mapParamerter["maskSize"];
	int nSize = nMaskSize / 2 * 2 + 1;

	blur(m_sink[0].image, m_src[0].image, Size(nSize, nSize));
	//m_src[0].image_gpu = m_sink[0].image_gpu.clone();
	SetSinkState(0, false);
	return true;
}

IMPLEMENT_DYNAMIC_CLASS(MeanBlurX)