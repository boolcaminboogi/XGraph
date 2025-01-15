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

protected:
	CBitmap m_BackBuffer; // ���� ���۸��� ���� �� ����
	CDC m_BackDC;         // �� ���۸� ���� DC

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

