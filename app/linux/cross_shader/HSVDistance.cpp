#include "stdafx.h"
#include "HSVDistance.h"


HSVDistance::HSVDistance()
{
	m_sink.push_back(ConnectPoint(INTERFACE_TYPE_IMAGE));
	m_src.push_back(ConnectPoint(INTERFACE_TYPE_IMAGE));
	m_passDownOrder.push_back(0);
}


HSVDistance::~HSVDistance()
{
}
void HSVDistance::SetParameter(const char* szKey, float fVal)
{
	string str = szKey;
	if (str == "sv")
	{
		Mat sv = imread("sv.png", CV_LOAD_IMAGE_GRAYSCALE);
		if (sv.empty() )
		{
			m_sv = Mat(256, 256, CV_8UC1);
			return;
		}
		if (mean(sv)[0] == 0)
		{
			m_sv = Mat(256, 256, CV_8UC1);
			return;
		}
		double diff = m_mapParamerter["svRatio"];
		Mat tmp;
		tmp = sv.clone();
		Mat element = cv::getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
		float ratio = 1;
		while (1)
		{
			double avg = mean(sv)[0];
			if (avg > 250)
				break;
			Mat sv2;

			dilate(sv, sv2, element);
			tmp += (sv2 - sv)*ratio;
			ratio -= diff;
			sv = sv2.clone();
		}
		m_sv = tmp.clone();
		
	}
		
	if (str == "minH")
		m_nMinH = fVal;
	if (str == "maxH")
		m_nMaxH = fVal;
	IAlgorithmStratety::SetParameter(szKey, fVal);
}


double HSVDistance::GetDistance(Vec3b& B)
{
	double d = 0;
	if (B[0] >= m_nMinH && B[0] <= m_nMaxH && B[2] > 30)
	{
		d = m_sv.at<uchar>(B[1], B[2]);
		return 255-d;
	}
	else
		return 255;
}
bool HSVDistance::TryRun()
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
	if (m_sink[0].image.type() != CV_8UC3)
	{
		LOG_ERROR;
		return false;
	}
	Mat hsv;

	cvtColor(m_sink[0].image, hsv, CV_BGR2HSV_FULL);
	m_src[0].image.create(m_sink[0].image.size(), CV_8UC1);
	for (int i = 0; i < m_sink[0].image.rows; i++)
	{
		for (int j = 0; j <m_sink[0].image.cols; j++)
		{
			
			Vec3b bc = hsv.at<Vec3b>(i, j);

			double dist = GetDistance(bc);
			dist = saturate_cast<uchar>(dist);

			m_src[0].image.at<uchar>(i, j) = dist;
		}
	}
	SetSinkState(0, false);
	return true;
}


IMPLEMENT_DYNAMIC_CLASS(HSVDistance)
