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

	// 그리드 표시여부
	bool m_bShowGrid;

	// 그리드에 단위 표시 여부
	bool m_bShowUnit;			// 기본값 false
	double m_dMargin_forUnit;	// 기본값 0.05
	int m_nDisplayFrequency;	// 기본값 2 - 2칸에 한번씩만 표시

	// 여백 비율 (0.0 ~ 1.0) : 권장값 0.02
	CDPoint m_Margin;

	// 그리드 개수 : 가로(x), 세로(y)
	CPoint m_GridCount;


	//-------------------------------------------------------------------

	// 그리드 배경색
	COLORREF m_GridColor;

	// 그리드 선색
	COLORREF m_LineColor;

	// 그리드 선두께
	int m_LineWidth;

	// 그리드 선스타일
	int m_LineStyle;
};

