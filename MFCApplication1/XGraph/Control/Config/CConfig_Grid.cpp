#include "pch.h"
#include "CConfig_Grid.h"

// CDPoint
CDPoint::CDPoint()
{
	m_dX = 0.0;
	m_dY = 0.0;
}
CDPoint::CDPoint(double x, double y)
{
	m_dX = x;
	m_dY = y;
}

// CConfig_Grid
CConfig_Grid::CConfig_Grid()
{
	SetDefault();
}

CConfig_Grid::~CConfig_Grid()
{
}

void CConfig_Grid::SetDefault()
{
	// 그리드 표시여부
	m_bShowGrid = true;

	// 그리드에 단위 표시 여부
	m_bShowUnit = true;
	m_dMargin_forUnit = 0.04;
	m_nDisplayFrequency = 2;

	// 여백 비율 (0 ~ 1) : 권장값 0.02
	m_Margin = CDPoint(0.05, 0.15);  // 5%, 15% 여백으로 사용

	// 그리드 개수 : 가로(x), 세로(y)
	m_GridCount = CPoint(20, 20);

	// 그리드 배경색
	m_GridColor = RGB(255, 255, 255);

	// 그리드 선색
	m_LineColor = RGB(200, 200, 200);

	// 그리드 선두께
	m_LineWidth = 1;

	// 그리드 선스타일
	m_LineStyle = PS_DOT;
}

void CConfig_Grid::SetTitle(CString strTitle)
{
	m_strTitle = strTitle;
}

void CConfig_Grid::SetDescription_of_the_unit(CString strUnit)
{
	m_strDescription_of_the_unit = strUnit;
}
