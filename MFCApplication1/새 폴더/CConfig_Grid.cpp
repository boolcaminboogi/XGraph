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
	// �׸��� ǥ�ÿ���
	m_bShowGrid = false;

	// �׸��忡 ���� ǥ�� ����
	m_bShowUnit = false;
	m_dMargin_forUnit = 0.05;
	m_nDisplayFrequency = 2;

	// ���� ���� (0 ~ 1) : ���尪 0.02
	m_Margin = CDPoint(0.0, 0.0);

	// �׸��� ���� : ����(x), ����(y)
	m_GridCount = CPoint();

	// �׸��� ����
	m_GridColor = RGB(255, 255, 255);

	// �׸��� ����
	m_LineColor = RGB(220, 220, 220);

	// �׸��� ���β�
	m_LineWidth = 1;

	// �׸��� ����Ÿ��
	m_LineStyle = PS_DOT;
}

CConfig_Grid::~CConfig_Grid()
{
}
