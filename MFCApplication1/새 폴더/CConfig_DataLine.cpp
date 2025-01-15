#include "pch.h"
#include "CConfig_DataLine.h"

CConfig_DataLine::CConfig_DataLine()
{
	m_nFormat = 0;

	m_bUseSpecLine = TRUE;
	m_SpecLineColor = RGB(255, 0, 0);
	m_SpecLineWidth = 1;
	m_SpecLineStyle = PS_DOT; // PS_SOLID, PS_DASH, PS_DOT, PS_DASHDOT, PS_DASHDOTDOT


	m_DataLineColor = RGB(0, 0, 255);
	m_DataLineWidth = 1;
	m_DataLineStyle = PS_SOLID; // PS_SOLID, PS_DASH, PS_DOT, PS_DASHDOT, PS_DASHDOTDOT
	m_nDataCount = 20;
}

CConfig_DataLine::~CConfig_DataLine()
{
}