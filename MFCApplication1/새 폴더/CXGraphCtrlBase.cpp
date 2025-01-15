#include "pch.h"
#include "CXGraphCtrlBase.h"

// CXGraphCtrlBase
CXGraphCtrlBase::CXGraphCtrlBase()
{
	m_pConfigDlg = NULL;

	m_dSpecMin = 0.0;
	m_dSpecMax = 0.0;

	m_dDisplayMin = 0.0;
	m_dDisplayMax = 0.0;
}

CXGraphCtrlBase::~CXGraphCtrlBase()
{
	ReleaseBackBuffer();
}

BEGIN_MESSAGE_MAP(CXGraphCtrlBase, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

void CXGraphCtrlBase::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	// m_BackDC가 유효한지 확인
	if (m_BackDC.GetSafeHdc() == nullptr)
	{
		return;
	}

	// 배경 그리기
	CRect rect;
	GetClientRect(&rect);
	m_BackDC.FillSolidRect(&rect, m_configGrid.m_GridColor); // 배경을 흰색으로 채우기

#if 0
	// 예제: 빨간색 원 그리기
	CBrush brush(RGB(255, 0, 0));
	CBrush* pOldBrush = m_BackDC.SelectObject(&brush);
	m_BackDC.Ellipse(50, 50, rect.right - 50, rect.bottom - 50);

	// 백 버퍼를 화면에 복사
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &m_BackDC, 0, 0, SRCCOPY);

	// Restore the old brush
	m_BackDC.SelectObject(pOldBrush);
	// No need to call DeleteObject for stack-allocated brush

#endif

#if 1
	// 그리드 표시
	if (!m_configGrid.m_bShowGrid)
	{
		// 데이터 그리기
		OnPaint_DataLine(&m_BackDC);
	}
	else
	{
		CString strDisplayValue; 
		CSize textSize;
		double dPitch = (double)(m_dDisplayMax - m_dDisplayMin) / (double)m_configGrid.m_GridCount.y;

		CRect graph_rect;
		graph_rect.left = (int)(rect.Width() * m_configGrid.m_Margin.m_dX);
		graph_rect.top = (int)(rect.Height() * m_configGrid.m_Margin.m_dY);
		graph_rect.right = (int)(rect.Width() * (1 - m_configGrid.m_Margin.m_dX));
		graph_rect.bottom = (int)(rect.Height() * (1 - m_configGrid.m_Margin.m_dY));

		// 그리드에 단위 표시 여부
		if (m_configGrid.m_bShowUnit)
		{
			// 단위표시용으로 마진 추가
			graph_rect.left = (int)(rect.Width() * (m_configGrid.m_Margin.m_dX + m_configGrid.m_dMargin_forUnit));
			graph_rect.right = (int)(rect.Width() * (1 - m_configGrid.m_Margin.m_dX - m_configGrid.m_dMargin_forUnit));
		}

		// 펜
		CPen outline_grid_pen(PS_SOLID, 1, m_configGrid.m_LineColor);
		CPen main_grid_pen(m_configGrid.m_LineStyle, m_configGrid.m_LineWidth, m_configGrid.m_LineColor);
		CPen* pOldPen = m_BackDC.SelectObject(&main_grid_pen);

		// 브러쉬
		CBrush brush(RGB(255, 0, 0));
		CBrush* pOldBrush = m_BackDC.SelectObject(&brush);
		int y = 0;
		CString strFormat;

		// 가로선 그리기
		for (int i = 0; i <= m_configGrid.m_GridCount.y; i++)
		{
			if (i == 0 || i == m_configGrid.m_GridCount.y)
			{
				m_BackDC.SelectObject(&outline_grid_pen);
			}
			else
			{
				m_BackDC.SelectObject(&main_grid_pen);
			}

			y = graph_rect.top + (graph_rect.Height() * i / m_configGrid.m_GridCount.y);
			m_BackDC.MoveTo(graph_rect.left, y);
			m_BackDC.LineTo(graph_rect.right, y);


			if (m_configGrid.m_bShowUnit)
			{
				if (i % m_configGrid.m_nDisplayFrequency == 0)
				{
					// 텍스트로 출력
					if (m_configDataLine.m_nFormat == 0)
					{
						strDisplayValue.Format(_T("%d"), (int)(m_dDisplayMax - dPitch * i));
					}
					else
					{
						strFormat.Format(_T("%%.%df"), m_configDataLine.m_nFormat);
						strDisplayValue.Format(strFormat, m_dDisplayMax - dPitch * i);
					}

					textSize = m_BackDC.GetTextExtent(strDisplayValue);
#if 1
					// 오른쪽에 표시
					m_BackDC.TextOutW(
						graph_rect.right + (int)(rect.Width() * 0.01),
						y - textSize.cy / 2,
						strDisplayValue);
#else
					// 왼쪽에 표시
					m_BackDC.TextOutW(
						graph_rect.left - (int)(rect.Width() * 0.01) - textSize.cx,
						y - textSize.cy / 2,
						strDisplayValue);
#endif
				}
			}
		}

		// 세로선 그리기
		for (int i = 0; i <= m_configGrid.m_GridCount.x; i++)
		{
			if (i == 0 || i == m_configGrid.m_GridCount.x)
			{
				m_BackDC.SelectObject(&outline_grid_pen);
			}
			else
			{
				m_BackDC.SelectObject(&main_grid_pen);
			}

			int x = graph_rect.left + (graph_rect.Width() * i / m_configGrid.m_GridCount.x);
			m_BackDC.MoveTo(x, graph_rect.top);
			m_BackDC.LineTo(x, graph_rect.bottom);
		}

		// int old_mode = m_BackDC.SetBkMode(TRANSPARENT);
		// m_BackDC.SetBkMode(old_mode);


		// 데이터 그리기
		OnPaint_DataLine(&m_BackDC);

		// Restore the old pen
		m_BackDC.SelectObject(pOldPen);
		// Restore the old brush
		m_BackDC.SelectObject(pOldBrush);
	}

	// 백 버퍼를 화면에 복사
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &m_BackDC, 0, 0, SRCCOPY);

#endif
}
void CXGraphCtrlBase::OnPaint_DataLine(CDC* pDC)
{
	// 
}

BOOL CXGraphCtrlBase::OnEraseBkgnd(CDC* pDC)
{
	// 깜박임을 방지하기 위해 배경 지우기를 비활성화
	return TRUE;
}

BOOL CXGraphCtrlBase::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CXGraphCtrlBase::OnDestroy()
{
	CWnd::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	ReleaseBackBuffer();
}


void CXGraphCtrlBase::InitBackBuffer()
{
	CRect rect;
	GetClientRect(&rect);

	CDC* pThisDC = GetDC();
	if (pThisDC)
	{
		m_BackBuffer.CreateCompatibleBitmap(pThisDC, rect.Width(), rect.Height());
		m_BackDC.CreateCompatibleDC(pThisDC);
		m_BackDC.SelectObject(&m_BackBuffer);

		m_BackBuffer.DeleteObject();
		ReleaseDC(pThisDC);
		pThisDC = NULL;
	}
}

void CXGraphCtrlBase::ReleaseBackBuffer()
{
	if (m_BackDC.GetSafeHdc() != nullptr)
	{
		m_BackDC.DeleteDC();
	}
	if (m_BackBuffer.GetSafeHandle() != nullptr)
	{
		m_BackBuffer.DeleteObject();
	}

	if (m_pConfigDlg)
	{
		m_pConfigDlg->DestroyWindow();
		delete m_pConfigDlg;
		m_pConfigDlg = NULL;
	}
}

void CXGraphCtrlBase::SetSpec(double dMin, double dMax)
{
	m_dSpecMin = dMin;
	m_dSpecMax = dMax;
}

void CXGraphCtrlBase::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (cx > 0 && cy > 0)
	{
		// 백 버퍼 해제 및 재초기화
		ReleaseBackBuffer();
		InitBackBuffer();
		Invalidate(); // 창을 다시 그리도록 요청
	}
}


void CXGraphCtrlBase::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_pConfigDlg)
	{
		m_pConfigDlg->DestroyWindow();
		delete m_pConfigDlg;
		m_pConfigDlg = NULL;
	}

	m_pConfigDlg = new CXGraphCtrlBase_Config(this);
	if (m_pConfigDlg)
	{
		// 설정값
		m_pConfigDlg->m_pConfig_Grid = &m_configGrid;
		m_pConfigDlg->m_pConfig_DataLine = &m_configDataLine;
		m_pConfigDlg->m_pdSpecMin = &m_dSpecMin;
		m_pConfigDlg->m_pdSpecMax = &m_dSpecMax;
		m_pConfigDlg->Create(IDD_DIALOG_GRAPH_CONFIG, this);
		m_pConfigDlg->CenterWindow(this);
		m_pConfigDlg->ShowWindow(SW_SHOW);
	}

	CWnd::OnLButtonDblClk(nFlags, point);
}
