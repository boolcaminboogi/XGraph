#pragma once

class CDPoint
{
public:
	CDPoint();
	CDPoint(double x, double y);
	
	double m_dX;
	double m_dY;
};

class CConfig_Grid
{
public:
	CConfig_Grid();
	~CConfig_Grid();

	// �׸��� ǥ�ÿ���
	bool m_bShowGrid;

	// �׸��忡 ���� ǥ�� ����
	bool m_bShowUnit;
	double m_dMargin_forUnit;
	int m_nDisplayFrequency;

	// ���� ���� (0 ~ 1) : ���尪 0.02
	CDPoint m_Margin;

	// �׸��� ���� : ����(x), ����(y)
	CPoint m_GridCount;

	// �׸��� ����
	COLORREF m_GridColor;

	// �׸��� ����
	COLORREF m_LineColor;

	// �׸��� ���β�
	int m_LineWidth;

	// �׸��� ����Ÿ��
	int m_LineStyle;
};

