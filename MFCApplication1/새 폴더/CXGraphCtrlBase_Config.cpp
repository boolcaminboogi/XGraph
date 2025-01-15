// CXGraphCtrlBase_Config.cpp: 구현 파일
//

#include "pch.h"
#include "CXGraphCtrlBase_Config.h"
#include "afxdialogex.h"
#include "CXGraphCtrlBase.h"


// CXGraphCtrlBase_Config 대화 상자

IMPLEMENT_DYNAMIC(CXGraphCtrlBase_Config, CDialogEx)

CXGraphCtrlBase_Config::CXGraphCtrlBase_Config(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_GRAPH_CONFIG, pParent)
{
	m_pConfig_Grid = NULL;
	m_pConfig_DataLine = NULL;

	m_pdSpecMin = NULL;
	m_pdSpecMax = NULL;
}

CXGraphCtrlBase_Config::~CXGraphCtrlBase_Config()
{
}

void CXGraphCtrlBase_Config::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CXGraphCtrlBase_Config, CDialogEx)
	ON_BN_CLICKED(IDOK, &CXGraphCtrlBase_Config::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CXGraphCtrlBase_Config::OnBnClickedCancel)
END_MESSAGE_MAP()


// CXGraphCtrlBase_Config 메시지 처리기


void CXGraphCtrlBase_Config::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pConfig_Grid)
	{
		CString strX;
		CString strY;
		CString strUnit;

		// Grid 표시 여부
		m_pConfig_Grid->m_bShowGrid =
			((CButton*)GetDlgItem(IDC_CHECK_SHOW_GRID))->GetCheck() == BST_CHECKED ? TRUE : FALSE;

		// Grid 단위 표시 여부
		m_pConfig_Grid->m_bShowUnit = 
			((CButton*)GetDlgItem(IDC_CHECK_SHOW_GRID_UNIT))->GetCheck() == BST_CHECKED ? TRUE : FALSE;

		// 단위 표시용 여백 비율
		GetDlgItemText(IDC_EDIT_MARGIN_FOR_UNIT, strUnit);
		m_pConfig_Grid->m_dMargin_forUnit = _ttof(strUnit);

		// 단위 표시 주기
		GetDlgItemText(IDC_EDIT_DISPLAY_FREQUENCY_FOR_UNIT, strUnit);
		m_pConfig_Grid->m_nDisplayFrequency = _ttoi(strUnit);
		
		// Grid Margin
		GetDlgItemText(IDC_EDIT_MARGIN_X, strX);
		GetDlgItemText(IDC_EDIT_MARGIN_Y, strY);
		m_pConfig_Grid->m_Margin.m_dX = _ttof(strX);
		m_pConfig_Grid->m_Margin.m_dY = _ttof(strY);

		// Grid 개수
		GetDlgItemText(IDC_EDIT_GRID_COUNT_X, strX);
		GetDlgItemText(IDC_EDIT_GRID_COUNT_Y, strY);
	 	m_pConfig_Grid->m_GridCount.x = _ttoi(strX);
		m_pConfig_Grid->m_GridCount.y = _ttoi(strY);



		if (m_pConfig_DataLine)
		{
			// 표시할 데이터 개수
			GetDlgItemText(IDC_EDIT_DATA_COUNT, strUnit);
			m_pConfig_DataLine->m_nDataCount = _ttoi(strUnit);

			// 소수점 자리수
			GetDlgItemText(IDC_EDIT_FORMAT, strUnit);
			m_pConfig_DataLine->m_nFormat = _ttoi(strUnit);

			// Spec Line 표시 여부
			m_pConfig_DataLine->m_bUseSpecLine =
				((CButton*)GetDlgItem(IDC_CHECK_USE_SPEC_LINE))->GetCheck() == BST_CHECKED ? TRUE : FALSE;

			CString strMin, strMax;
			// Spec min ~ max
			if (m_pdSpecMin)
			{
				GetDlgItemText(IDC_EDIT_SPEC_MIN, strMin);
				*m_pdSpecMin = _ttof(strMin);
			}
			if (m_pdSpecMax)
			{
				GetDlgItemText(IDC_EDIT_SPEC_MAX, strMax);
				*m_pdSpecMax = _ttoi(strMax);
			}
		}


		CWnd* pParent = GetParent();
		if (pParent && pParent->GetSafeHwnd())
		{
			pParent->Invalidate();
		}
	}

	// CDialogEx::OnOK();
}


void CXGraphCtrlBase_Config::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


BOOL CXGraphCtrlBase_Config::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	if (m_pConfig_Grid)
	{
		CString strX;
		CString strY;
		CString strUnit;

		// Grid 표시 여부
		((CButton*)GetDlgItem(IDC_CHECK_SHOW_GRID))->SetCheck(
			m_pConfig_Grid->m_bShowGrid == TRUE ? BST_CHECKED : BST_UNCHECKED);

		// Grid 단위 표시 여부
		((CButton*)GetDlgItem(IDC_CHECK_SHOW_GRID_UNIT))->SetCheck(
			m_pConfig_Grid->m_bShowUnit == TRUE ? BST_CHECKED : BST_UNCHECKED);

		// 단위 표시용 여백 비율
		strUnit.Format(_T("%.3f"), m_pConfig_Grid->m_dMargin_forUnit);
		SetDlgItemText(IDC_EDIT_MARGIN_FOR_UNIT, strUnit);

		// 단위 표시 주기
		strUnit.Format(_T("%d"), m_pConfig_Grid->m_nDisplayFrequency);
		SetDlgItemText(IDC_EDIT_DISPLAY_FREQUENCY_FOR_UNIT, strUnit);

		// Grid Margin
		strX.Format(_T("%.3f"), m_pConfig_Grid->m_Margin.m_dX);
		strY.Format(_T("%.3f"), m_pConfig_Grid->m_Margin.m_dY);
		SetDlgItemText(IDC_EDIT_MARGIN_X, strX);
		SetDlgItemText(IDC_EDIT_MARGIN_Y, strY);

		// Grid 개수
		strX.Format(_T("%d"), m_pConfig_Grid->m_GridCount.x);
		strY.Format(_T("%d"), m_pConfig_Grid->m_GridCount.y);
		SetDlgItemText(IDC_EDIT_GRID_COUNT_X, strX);
		SetDlgItemText(IDC_EDIT_GRID_COUNT_Y, strY);


		if (m_pConfig_DataLine)
		{
			// 표시할 데이터 개수
			strUnit.Format(_T("%d"), m_pConfig_DataLine->m_nDataCount);
			SetDlgItemText(IDC_EDIT_DATA_COUNT, strUnit);

			// 소수점 자리수
			strUnit.Format(_T("%d"), m_pConfig_DataLine->m_nFormat);
			SetDlgItemText(IDC_EDIT_FORMAT, strUnit);


			// Spec Line 표시 여부
			((CButton*)GetDlgItem(IDC_CHECK_USE_SPEC_LINE))->SetCheck(
				m_pConfig_DataLine->m_bUseSpecLine == TRUE ? BST_CHECKED : BST_UNCHECKED);

			// Spec min ~ max
			CString strMin, strMax;
			if (m_pdSpecMin)
			{
				strMin.Format(_T("%.3f"), *m_pdSpecMin);
				SetDlgItemText(IDC_EDIT_SPEC_MIN, strMin);
			}
			if (m_pdSpecMax)
			{
				strMax.Format(_T("%.3f"), *m_pdSpecMax);
				SetDlgItemText(IDC_EDIT_SPEC_MAX, strMax);
			}
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
