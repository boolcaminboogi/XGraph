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
	// �׸��� ǥ�ÿ���
	m_bShowGrid = true;

	// �׸��忡 ���� ǥ�� ����
	m_bShowUnit = true;
	m_dMargin_forUnit = 0.04;
	m_nDisplayFrequency = 2;

	// ���� ���� (0 ~ 1) : ���尪 0.02
	m_Margin = CDPoint(0.05, 0.15);  // 5%, 15% �������� ���

	// �׸��� ���� : ����(x), ����(y)
	m_GridCount = CPoint(20, 20);

	// �׸��� ����
	m_GridColor = RGB(255, 255, 255);

	// �׸��� ����
	m_LineColor = RGB(200, 200, 200);

	// �׸��� ���β�
	m_LineWidth = 1;

	// �׸��� ����Ÿ��
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
