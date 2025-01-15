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

	// 
	void SetDefault();
	void SetTitle(CString strTitle);
	void SetDescription_of_the_unit(CString strUnit);

	CString m_strTitle;
	CString m_strDescription_of_the_unit;

	// �׸��� ǥ�ÿ���
	bool m_bShowGrid;

	// �׸��忡 ���� ǥ�� ����
	bool m_bShowUnit;			// �⺻�� false
	double m_dMargin_forUnit;	// �⺻�� 0.05
	int m_nDisplayFrequency;	// �⺻�� 2 - 2ĭ�� �ѹ����� ǥ��

	// ���� ���� (0.0 ~ 1.0) : ���尪 0.02
	CDPoint m_Margin;

	// �׸��� ���� : ����(x), ����(y)
	CPoint m_GridCount;


	//-------------------------------------------------------------------

	// �׸��� ����
	COLORREF m_GridColor;

	// �׸��� ����
	COLORREF m_LineColor;

	// �׸��� ���β�
	int m_LineWidth;

	// �׸��� ����Ÿ��
	int m_LineStyle;
};

