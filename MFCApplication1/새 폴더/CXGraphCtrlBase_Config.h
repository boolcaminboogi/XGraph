#pragma once
#include "resource.h"
#include "CConfig_Grid.h"
#include "CConfig_DataLine.h"

// CXGraphCtrlBase_Config 대화 상자
class CXGraphCtrlBase_Config : public CDialogEx
{
	DECLARE_DYNAMIC(CXGraphCtrlBase_Config)

public:
	CXGraphCtrlBase_Config(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CXGraphCtrlBase_Config();

	CConfig_Grid* m_pConfig_Grid;
	CConfig_DataLine* m_pConfig_DataLine;
	double* m_pdSpecMin;
	double* m_pdSpecMax;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GRAPH_CONFIG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
};
