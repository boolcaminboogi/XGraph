
// MFCApplication1Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "CXGraph.h"


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CMFCApplication1Dlg 대화 상자



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pDlgXGraph_Attach = NULL;
	m_pDlgXGraph_Modaless = NULL;
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication1Dlg::OnBnClickedButton3)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_APPEND, &CMFCApplication1Dlg::OnBnClickedButtonAppend)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMFCApplication1Dlg 메시지 처리기

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#if 0
// 템플릿 형태로 개선된 Add 함수
template <typename T>
T Add(T a, T b)
{
	return (a + b);
}

void CMFCApplication1Dlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int a = 0;
	for (int i = 0; i < 10; i++)
	{
		a = Add(a, i);
	}

	CString msg;
	msg.Format(_T("Result : %d"), a);
	msg.Trim();
	if (msg.GetLength() > 0)
	{
		MessageBox(msg);
	}
	else
	{
		MessageBox(_T("Error"));
	}
}
#endif

BOOL CMFCApplication1Dlg::PreTranslateMessage(MSG* pMsg)
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


void CMFCApplication1Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	if (m_pDlgXGraph_Attach)
	{
		m_pDlgXGraph_Attach->DestroyWindow();

		delete m_pDlgXGraph_Attach;
		m_pDlgXGraph_Attach = NULL;
	}

	if (m_pDlgXGraph_Modaless)
	{
		m_pDlgXGraph_Modaless->DestroyWindow();

		delete m_pDlgXGraph_Modaless;
		m_pDlgXGraph_Modaless = NULL;
	}
}


void CMFCApplication1Dlg::OnBnClickedButton1()
{
	CXGraph dlg;

	dlg.m_configGrid.SetTitle(_T("21700 음극 - 양극 극간"));
	dlg.m_configGrid.SetDescription_of_the_unit(_T("Unit : mm"));

	// Grid 설정값 세팅
	dlg.m_configGrid.m_bShowGrid = true;
	dlg.m_configGrid.m_bShowUnit = true;
	dlg.m_configGrid.m_dMargin_forUnit = 0.04;
	dlg.m_configGrid.m_nDisplayFrequency = 2;

	dlg.m_configGrid.m_Margin = CDPoint(0.05, 0.15); // 5%, 15% 여백으로 사용
	dlg.m_configGrid.m_GridCount = CPoint(20, 20); // 10x10 그리드
	dlg.m_configGrid.m_GridColor = RGB(255, 255, 255); // 그리드 배경색
	dlg.m_configGrid.m_LineColor = RGB(200, 200, 200); // 그리드 선색
	dlg.m_configGrid.m_LineWidth = 1; // 그리드 선두께
	dlg.m_configGrid.m_LineStyle = PS_DOT; // 그리드 선스타일  PS_SOLID, PS_DASH, PS_DOT, PS_DASHDOT, PS_DASHDOTDOT

	// Spec 설정값 세팅
	dlg.m_configDataLine.m_nFormat = 1; // 1 : 소수점 1자리까지만 표시
	// Display Data 세팅	// Spec 세팅
	dlg.m_configDataLine.SetDisplayData(0.0, 2.0);
	dlg.m_configDataLine.m_bUseSpecLine = TRUE;
	// Spec 세팅
	dlg.m_configDataLine.SetSpec(0.5, 1.5);
	dlg.m_configDataLine.m_SpecLineColor = RGB(255, 0, 0); // spec 라인 색상
	dlg.m_configDataLine.m_SpecLineWidth = 1; // spec 라인 두께
	dlg.m_configDataLine.m_SpecLineStyle = PS_SOLID; // spec 라인 스타일 PS_SOLID, PS_DASH, PS_DOT, PS_DASHDOT, PS_DASHDOTDOT

	// DataLine 설정값 세팅
	dlg.m_configDataLine.m_DataLineColor = RGB(0, 0, 255); // 데이터 라인 색상
	dlg.m_configDataLine.m_DataLineWidth = 1; // 데이터 라인 두께
	dlg.m_configDataLine.m_DataLineStyle = PS_SOLID; // 데이터 라인 스타일 PS_SOLID, PS_DASH, PS_DOT, PS_DASHDOT, PS_DASHDOTDOT
	dlg.m_configDataLine.m_nDataCount = 20;



	// 데이터 세팅
	dlg.AppendValue(1.1);
	dlg.AppendValue(1.2);
	dlg.AppendValue(1.3);
	dlg.AppendValue(1.4);
	dlg.AppendValue(1.5);

	dlg.AppendValue(1.6);
	dlg.AppendValue(1.7);
	dlg.AppendValue(1.8);
	dlg.AppendValue(1.9);
	dlg.AppendValue(0.1);

	dlg.AppendValue(0.2);
	dlg.AppendValue(0.3);
	dlg.AppendValue(0.4);
	dlg.AppendValue(0.5);
	dlg.AppendValue(0.6);

	dlg.AppendValue(0.7);
	dlg.AppendValue(0.8);
	dlg.AppendValue(0.9);
	dlg.AppendValue(1.0);
	dlg.AppendValue(1.1);

	dlg.DoModal();
}


void CMFCApplication1Dlg::OnBnClickedButton2()
{
	// 기능2 - Modaless로 제작하여, 계속 데이터를 누적해야 할 때
	if (m_pDlgXGraph_Modaless)
	{
		m_pDlgXGraph_Modaless->DestroyWindow();

		delete m_pDlgXGraph_Modaless;
		m_pDlgXGraph_Modaless = NULL;
	}

	if (m_pDlgXGraph_Modaless == NULL)
	{
		m_pDlgXGraph_Modaless = new CXGraph(this);
	}

	if (m_pDlgXGraph_Modaless)
	{
		CXGraph* pXGraph = m_pDlgXGraph_Modaless;

		pXGraph->m_configGrid.SetTitle(_T("21700 음극 - 양극 극간"));
		pXGraph->m_configGrid.SetDescription_of_the_unit(_T("Unit : mm"));

		// Grid 설정값 세팅
		pXGraph->m_configGrid.m_bShowGrid = true;
		pXGraph->m_configGrid.m_bShowUnit = true;
		pXGraph->m_configGrid.m_dMargin_forUnit = 0.04;
		pXGraph->m_configGrid.m_nDisplayFrequency = 2;

		pXGraph->m_configGrid.m_Margin = CDPoint(0.05, 0.15); // 5%, 15% 여백으로 사용
		pXGraph->m_configGrid.m_GridCount = CPoint(20, 20); // 10x10 그리드
		pXGraph->m_configGrid.m_GridColor = RGB(255, 255, 255); // 그리드 배경색
		pXGraph->m_configGrid.m_LineColor = RGB(200, 200, 200); // 그리드 선색
		pXGraph->m_configGrid.m_LineWidth = 1; // 그리드 선두께
		pXGraph->m_configGrid.m_LineStyle = PS_DOT; // 그리드 선스타일  PS_SOLID, PS_DASH, PS_DOT, PS_DASHDOT, PS_DASHDOTDOT

		// Spec 설정값 세팅
		pXGraph->m_configDataLine.m_nFormat = 1; // 1 : 소수점 1자리까지만 표시

		// Display Data 세팅	// Spec 세팅
		pXGraph->m_configDataLine.SetDisplayData(0.0, 2.0);

		pXGraph->m_configDataLine.m_bUseSpecLine = TRUE;
		// Spec 세팅
		pXGraph->m_configDataLine.SetSpec(0.5, 1.5);
		pXGraph->m_configDataLine.m_SpecLineColor = RGB(255, 0, 0); // spec 라인 색상
		pXGraph->m_configDataLine.m_SpecLineWidth = 1; // spec 라인 두께
		pXGraph->m_configDataLine.m_SpecLineStyle = PS_SOLID; // spec 라인 스타일 PS_SOLID, PS_DASH, PS_DOT, PS_DASHDOT, PS_DASHDOTDOT

		// DataLine 설정값 세팅
		pXGraph->m_configDataLine.m_DataLineColor = RGB(0, 0, 255); // 데이터 라인 색상
		pXGraph->m_configDataLine.m_DataLineWidth = 1; // 데이터 라인 두께
		pXGraph->m_configDataLine.m_DataLineStyle = PS_SOLID; // 데이터 라인 스타일 PS_SOLID, PS_DASH, PS_DOT, PS_DASHDOT, PS_DASHDOTDOT
		pXGraph->m_configDataLine.m_nDataCount = 20;


		// 팝업 생성 및 화면 표시
		pXGraph->Create(IDD_DIALOG_GRAPH, this);
		pXGraph->CenterWindow(this);
		pXGraph->ShowWindow(SW_SHOW);





		// 데이터 세팅
		pXGraph->AppendValue(1.1);
		pXGraph->AppendValue(1.2);
		pXGraph->AppendValue(1.3);
		pXGraph->AppendValue(1.4);
		pXGraph->AppendValue(1.5);

		pXGraph->AppendValue(1.6);
		pXGraph->AppendValue(1.7);
		pXGraph->AppendValue(1.8);
		pXGraph->AppendValue(1.9);
		pXGraph->AppendValue(0.1);

		pXGraph->AppendValue(0.2);
		pXGraph->AppendValue(0.3);
		pXGraph->AppendValue(0.4);
		pXGraph->AppendValue(0.5);
		pXGraph->AppendValue(0.6);

		pXGraph->AppendValue(0.7);
		pXGraph->AppendValue(0.8);
		pXGraph->AppendValue(0.9);
		pXGraph->AppendValue(1.0);
		pXGraph->AppendValue(1.1);
	}
}


void CMFCApplication1Dlg::OnBnClickedButton3()
{
	// 기능3 - 정해진 위치에 그래프를 표시하고 싶을 때 (Attach 방식, CHILD)
	if (m_pDlgXGraph_Attach)
	{
		m_pDlgXGraph_Attach->DestroyWindow();

		delete m_pDlgXGraph_Attach;
		m_pDlgXGraph_Attach = NULL;
	}

	if (m_pDlgXGraph_Attach == NULL)
	{
		m_pDlgXGraph_Attach = new CXGraph(this);
	}

	if (m_pDlgXGraph_Attach)
	{
		CXGraph* pXGraph = m_pDlgXGraph_Attach;

		pXGraph->m_configGrid.SetTitle(_T("21700 음극 - 양극 극간"));
		pXGraph->m_configGrid.SetDescription_of_the_unit(_T("Unit : mm"));

		// Grid 설정값 세팅
		pXGraph->m_configGrid.m_bShowGrid = true;
		pXGraph->m_configGrid.m_bShowUnit = true;
		pXGraph->m_configGrid.m_dMargin_forUnit = 0.04;
		pXGraph->m_configGrid.m_nDisplayFrequency = 2;

		pXGraph->m_configGrid.m_Margin = CDPoint(0.05, 0.15); // 5%, 15% 여백으로 사용
		pXGraph->m_configGrid.m_GridCount = CPoint(20, 20); // 10x10 그리드
		pXGraph->m_configGrid.m_GridColor = RGB(255, 255, 255); // 그리드 배경색
		pXGraph->m_configGrid.m_LineColor = RGB(200, 200, 200); // 그리드 선색
		pXGraph->m_configGrid.m_LineWidth = 1; // 그리드 선두께
		pXGraph->m_configGrid.m_LineStyle = PS_DOT; // 그리드 선스타일  PS_SOLID, PS_DASH, PS_DOT, PS_DASHDOT, PS_DASHDOTDOT

		// Spec 설정값 세팅
		pXGraph->m_configDataLine.m_nFormat = 1; // 1 : 소수점 1자리까지만 표시

		// Display Data 세팅	// Spec 세팅
		pXGraph->m_configDataLine.SetDisplayData(0.0, 2.0);

		pXGraph->m_configDataLine.m_bUseSpecLine = TRUE;
		// Spec 세팅
		pXGraph->m_configDataLine.SetSpec(0.5, 1.5);
		pXGraph->m_configDataLine.m_SpecLineColor = RGB(255, 0, 0); // spec 라인 색상
		pXGraph->m_configDataLine.m_SpecLineWidth = 1; // spec 라인 두께
		pXGraph->m_configDataLine.m_SpecLineStyle = PS_SOLID; // spec 라인 스타일 PS_SOLID, PS_DASH, PS_DOT, PS_DASHDOT, PS_DASHDOTDOT

		// DataLine 설정값 세팅
		pXGraph->m_configDataLine.m_DataLineColor = RGB(0, 0, 255); // 데이터 라인 색상
		pXGraph->m_configDataLine.m_DataLineWidth = 1; // 데이터 라인 두께
		pXGraph->m_configDataLine.m_DataLineStyle = PS_SOLID; // 데이터 라인 스타일 PS_SOLID, PS_DASH, PS_DOT, PS_DASHDOT, PS_DASHDOTDOT
		pXGraph->m_configDataLine.m_nDataCount = 20;





		// 팝업 생성 및 화면 표시
		pXGraph->Create(IDD_DIALOG_GRAPH, this);
		pXGraph->ModifyStyle(WS_BORDER | WS_CAPTION | WS_CLIPSIBLINGS | WS_DLGFRAME | WS_POPUP | WS_SYSMENU | WS_THICKFRAME, WS_CHILD);
		pXGraph->ModifyStyleEx(WS_EX_NOPARENTNOTIFY | WS_EX_TOPMOST | WS_EX_MDICHILD, 0);

		pXGraph->SetParent(this);

		DWORD dwStyle = pXGraph->GetStyle();
		if (dwStyle & WS_POPUP)
		{
			pXGraph->ModifyStyle(WS_POPUP, 0);
		}
		/*
		DWORD dwStyleEx = pXGraph->GetStyle();
		if (dwStyle & WS_POPUP)
		{
			pXGraph->ModifyStyle(WS_POPUP, 0);
		}
		*/

		// 위치 / 크기 확인
		CRect rectAttach;
		GetDlgItem(IDC_STATIC_ATTACH)->GetWindowRect(&rectAttach);
		ScreenToClient(&rectAttach);

		// 위치 / 크기 조정
		pXGraph->MoveWindow(&rectAttach);
		pXGraph->ShowWindow(SW_SHOW);





		// 데이터 세팅
		pXGraph->AppendValue(1.1);
		pXGraph->AppendValue(1.2);
		pXGraph->AppendValue(1.3);
		pXGraph->AppendValue(1.4);
		pXGraph->AppendValue(1.5);

		pXGraph->AppendValue(1.6);
		pXGraph->AppendValue(1.7);
		pXGraph->AppendValue(1.8);
		pXGraph->AppendValue(1.9);
		pXGraph->AppendValue(0.1);

		pXGraph->AppendValue(0.2);
		pXGraph->AppendValue(0.3);
		pXGraph->AppendValue(0.4);
		pXGraph->AppendValue(0.5);
		pXGraph->AppendValue(0.6);

		pXGraph->AppendValue(0.7);
		pXGraph->AppendValue(0.8);
		pXGraph->AppendValue(0.9);
		pXGraph->AppendValue(1.0);
		pXGraph->AppendValue(1.1);
	}
}


void CMFCApplication1Dlg::OnBnClickedButtonAppend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strValue;
	GetDlgItemText(IDC_EDIT1, strValue);

	double dValue = _ttof(strValue);

	if (m_pDlgXGraph_Attach)
	{
		m_pDlgXGraph_Attach->AppendValue(dValue);
		m_pDlgXGraph_Attach->Invalidate();
	}

	if (m_pDlgXGraph_Modaless)
	{
		m_pDlgXGraph_Modaless->AppendValue(dValue);
		m_pDlgXGraph_Modaless->Invalidate();
	}
}


void CMFCApplication1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnTimer(nIDEvent);
}
