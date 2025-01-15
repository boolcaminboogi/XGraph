#pragma once
#include "afxdialogex.h"
#include "CXGraphCtrl.h"
#include "CConfig_Grid.h"
#include "CConfig_DataLine.h"

// CXGraph 대화 상자

class CXGraph : public CDialogEx
{
	DECLARE_DYNAMIC(CXGraph)

public:
	CXGraph(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CXGraph();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GRAPH };
#endif


public:
	// Grid에 대한 설정값
	CConfig_Grid m_configGrid;

	// Data Line에 대한 설정값
	CConfig_DataLine m_configDataLine;

	// 최근값만 셋팅할 수 있다.
	void AppendValue(double dValue);

protected:
	// Graph Control
	CXGraphCtrl m_XGraphCtrl;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
