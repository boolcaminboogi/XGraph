// CXGraph.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "CXGraph.h"


// CXGraph 대화 상자

IMPLEMENT_DYNAMIC(CXGraph, CDialogEx)

CXGraph::CXGraph(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_GRAPH, pParent)
{
	
}

CXGraph::~CXGraph()
{
}

void CXGraph::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CXGraph, CDialogEx)
	ON_BN_CLICKED(IDOK, &CXGraph::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CXGraph::OnBnClickedCancel)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CXGraph 메시지 처리기


void CXGraph::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void CXGraph::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


BOOL CXGraph::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
	{
		return TRUE;
	}

	if (pMsg->message == WM_SYSKEYDOWN && pMsg->wParam == VK_F4)
	{
		return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL CXGraph::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
#if 1
	CRect r;
	m_XGraphCtrl.m_configGrid = m_configGrid;
	m_XGraphCtrl.m_configDataLine = m_configDataLine;

	m_XGraphCtrl.CreateEx(WS_EX_TRANSPARENT/*WS_EX_CLIENTEDGE*/, NULL, NULL, WS_CHILD | WS_VISIBLE, r, this, 25000);
	m_XGraphCtrl.ShowWindow(SW_SHOW);

	GetClientRect(&r);
	m_XGraphCtrl.MoveWindow(0, 0, r.Width(), r.Height(), 0);
	// m_XGraphCtrl.Invalidate();
	// m_XGraphCtrl.UpdateWindow();
#endif

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CXGraph::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (cx > 0 && cy > 0)
	{
		if (m_XGraphCtrl)
			m_XGraphCtrl.MoveWindow(0, 0, cx, cy);

#if 0
		// Get the window rect and client rect
		CRect windowRect, clientRect;
		GetWindowRect(&windowRect);
		GetClientRect(&clientRect);

		// Log or inspect the dimensions
		TRACE(_T("Window Rect: Width=%d, Height=%d\n"), windowRect.Width(), windowRect.Height());
		TRACE(_T("Client Rect: Width=%d, Height=%d\n"), clientRect.Width(), clientRect.Height());
		TRACE(_T("OnSize: cx=%d, cy=%d\n"), cx, cy);
#endif
	}
}

void CXGraph::SetTitle(CString strTitle)
{
	m_XGraphCtrl.SetTitle(strTitle);
}
void CXGraph::SetDescription_of_the_unit(CString strUnit)
{
	m_XGraphCtrl.SetDescription_of_the_unit(strUnit);
}

void CXGraph::SetSpec(double dMin, double dMax)
{
	m_XGraphCtrl.SetSpec(dMin, dMax);
}

// Display Data Min, Max 세팅
void CXGraph::SetDisplayData(double dMin, double dMax)
{
	m_XGraphCtrl.SetDisplayData(dMin, dMax);
}

// 최근값만 셋팅할 수 있다.
void CXGraph::AppendValue(double dValue)
{
	m_XGraphCtrl.AppendValue(dValue);
}