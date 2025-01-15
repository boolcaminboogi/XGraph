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

	// m_BackDC�� ��ȿ���� Ȯ��
	if (m_BackDC.GetSafeHdc() == nullptr)
	{
		return;
	}

	// ��� �׸���
	CRect rect;
	GetClientRect(&rect);
	m_BackDC.FillSolidRect(&rect, m_configGrid.m_GridColor); // ����� ������� ä���

#if 0
	// ����: ������ �� �׸���
	CBrush brush(RGB(255, 0, 0));
	CBrush* pOldBrush = m_BackDC.SelectObject(&brush);
	m_BackDC.Ellipse(50, 50, rect.right - 50, rect.bottom - 50);

	// �� ���۸� ȭ�鿡 ����
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &m_BackDC, 0, 0, SRCCOPY);

	// Restore the old brush
	m_BackDC.SelectObject(pOldBrush);
	// No need to call DeleteObject for stack-allocated brush

#endif

#if 1
	// �׸��� ǥ��
	if (!m_configGrid.m_bShowGrid)
	{
		// ������ �׸���
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

		// �׸��忡 ���� ǥ�� ����
		if (m_configGrid.m_bShowUnit)
		{
			// ����ǥ�ÿ����� ���� �߰�
			graph_rect.left = (int)(rect.Width() * (m_configGrid.m_Margin.m_dX + m_configGrid.m_dMargin_forUnit));
			graph_rect.right = (int)(rect.Width() * (1 - m_configGrid.m_Margin.m_dX - m_configGrid.m_dMargin_forUnit));
		}

		// ��
		CPen outline_grid_pen(PS_SOLID, 1, m_configGrid.m_LineColor);
		CPen main_grid_pen(m_configGrid.m_LineStyle, m_configGrid.m_LineWidth, m_configGrid.m_LineColor);
		CPen* pOldPen = m_BackDC.SelectObject(&main_grid_pen);

		// �귯��
		CBrush brush(RGB(255, 0, 0));
		CBrush* pOldBrush = m_BackDC.SelectObject(&brush);
		int y = 0;
		CString strFormat;

		// ���μ� �׸���
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
					// �ؽ�Ʈ�� ���
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
					// �����ʿ� ǥ��
					m_BackDC.TextOutW(
						graph_rect.right + (int)(rect.Width() * 0.01),
						y - textSize.cy / 2,
						strDisplayValue);
#else
					// ���ʿ� ǥ��
					m_BackDC.TextOutW(
						graph_rect.left - (int)(rect.Width() * 0.01) - textSize.cx,
						y - textSize.cy / 2,
						strDisplayValue);
#endif
				}
			}
		}

		// ���μ� �׸���
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


		// ������ �׸���
		OnPaint_DataLine(&m_BackDC);

		// Restore the old pen
		m_BackDC.SelectObject(pOldPen);
		// Restore the old brush
		m_BackDC.SelectObject(pOldBrush);
	}

	// �� ���۸� ȭ�鿡 ����
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &m_BackDC, 0, 0, SRCCOPY);

#endif
}
void CXGraphCtrlBase::OnPaint_DataLine(CDC* pDC)
{
	// 
}

BOOL CXGraphCtrlBase::OnEraseBkgnd(CDC* pDC)
{
	// �������� �����ϱ� ���� ��� ����⸦ ��Ȱ��ȭ
	return TRUE;
}

BOOL CXGraphCtrlBase::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CXGraphCtrlBase::OnDestroy()
{
	CWnd::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
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

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	if (cx > 0 && cy > 0)
	{
		// �� ���� ���� �� ���ʱ�ȭ
		ReleaseBackBuffer();
		InitBackBuffer();
		Invalidate(); // â�� �ٽ� �׸����� ��û
	}
}


void CXGraphCtrlBase::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	if (m_pConfigDlg)
	{
		m_pConfigDlg->DestroyWindow();
		delete m_pConfigDlg;
		m_pConfigDlg = NULL;
	}

	m_pConfigDlg = new CXGraphCtrlBase_Config(this);
	if (m_pConfigDlg)
	{
		// ������
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
