#include "pch.h"
#include "CConfig_DataLine.h"

CConfig_DataLine::CConfig_DataLine()
{
	SetDefault();
}

CConfig_DataLine::~CConfig_DataLine()
{
}

void CConfig_DataLine::SetDefault()
{
	m_nFormat = 1; // 1 : 소수점 1자리까지만 표시

	m_dDisplayMin = 0.0;
	m_dDisplayMax = 2.0;

	m_bUseSpecLine = TRUE;
	m_dSpecMin = 0.5;
	m_dSpecMax = 1.5;
	m_SpecLineColor = RGB(255, 0, 0);
	m_SpecLineWidth = 1;
	m_SpecLineStyle = PS_SOLID; // PS_SOLID, PS_DASH, PS_DOT, PS_DASHDOT, PS_DASHDOTDOT

	m_DataLineColor = RGB(0, 0, 255);
	m_DataLineWidth = 1;
	m_DataLineStyle = PS_SOLID; // PS_SOLID, PS_DASH, PS_DOT, PS_DASHDOT, PS_DASHDOTDOT
	m_nDataCount = 20;
}

void CConfig_DataLine::SetSpec(double dMin, double dMax)
{
	m_dSpecMin = dMin;
	m_dSpecMax = dMax;
}

// Display Data Min, Max 세팅
void CConfig_DataLine::SetDisplayData(double dMin, double dMax)
{
	m_dDisplayMin = dMin;
	m_dDisplayMax = dMax;
}