#pragma once
#include <afxwin.h>
#include "CConfig_Grid.h"
#include "CConfig_DataLine.h"
#include "CXGraphCtrlBase_Config.h"

class CXGraphCtrlBase : public CWnd
{
public:
	CXGraphCtrlBase();
	~CXGraphCtrlBase();

public:
	CConfig_Grid m_configGrid;

	// Data Line에 대한 설정값
	CConfig_DataLine m_configDataLine;

	void InitBackBuffer();
	void ReleaseBackBuffer();

	// Min, Max spec 세팅
	void SetSpec(double dMin, double dMax);

	// Min, Max spec 가져오기
	double GetSpecMin()
	{
		return m_dSpecMin;
	};
	double GetSpecMax()
	{
		return m_dSpecMax;
	};

protected:
	CBitmap m_BackBuffer; // 더블 버퍼링을 위한 백 버퍼
	CDC m_BackDC;         // 백 버퍼를 위한 DC

	CString m_strTitle;
	CString m_strDescription_of_the_unit;

	double m_dSpecMin;
	double m_dSpecMax;

	double m_dDisplayMin;
	double m_dDisplayMax;

	// 설정 창
	CXGraphCtrlBase_Config* m_pConfigDlg;

public:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnPaint();
	virtual void OnPaint_DataLine(CDC* pDC);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

