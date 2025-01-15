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

	// Data Line�� ���� ������
	CConfig_DataLine m_configDataLine;

	void InitBackBuffer();
	void ReleaseBackBuffer();

	// Min, Max spec ����
	void SetSpec(double dMin, double dMax);

	// Min, Max spec ��������
	double GetSpecMin()
	{
		return m_dSpecMin;
	};
	double GetSpecMax()
	{
		return m_dSpecMax;
	};

protected:
	CBitmap m_BackBuffer; // ���� ���۸��� ���� �� ����
	CDC m_BackDC;         // �� ���۸� ���� DC

	CString m_strTitle;
	CString m_strDescription_of_the_unit;

	double m_dSpecMin;
	double m_dSpecMax;

	double m_dDisplayMin;
	double m_dDisplayMax;

	// ���� â
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

