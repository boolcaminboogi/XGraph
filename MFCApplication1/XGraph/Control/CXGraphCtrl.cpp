#include "pch.h"
#include "CXGraphCtrl.h"

// CXGraphCtrl
CXGraphCtrl::CXGraphCtrl()
{
	m_configDataLine.SetSpec(0.0, 0.0);
}


CXGraphCtrl::~CXGraphCtrl()
{
}

// 최근값만 셋팅할 수 있다.
void CXGraphCtrl::AppendValue(double dValue)
{
	m_data.push_back(dValue);

	// 오래된 데이터 삭제
	while (m_configDataLine.m_nDataCount != 0 && m_data.size() > m_configDataLine.m_nDataCount)
	{
		m_data.erase(m_data.begin());
	}
}

// 데이터 그려주기
void CXGraphCtrl::OnPaint_DataLine(CDC* pDC)
{
	if (pDC)
	{
		CString strSpec;
		CString strFormat;

		CRect rect;
		GetClientRect(&rect);

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

		//---------------------------------
		// [0] Title 표시
		//---------------------------------
		// 텍스트의 가로, 세로 크기 측정
		CSize textSize = pDC->GetTextExtent(m_configGrid.m_strTitle);

		// 텍스트 크기 출력 (가로, 세로 크기)
		//CString sizeInfo;
		//sizeInfo.Format(_T("Text Width: %d, Text Height: %d"), textSize.cx, textSize.cy);
		//AfxMessageBox(sizeInfo);

		// 텍스트를 출력
		pDC->TextOutW(
			graph_rect.left, 
			graph_rect.top - textSize.cy - (int)(rect.Height() * 0.02), 
			m_configGrid.m_strTitle);
		//---------------------------------


		//---------------------------------
		// [0] Unit 표시
		//---------------------------------
		textSize = pDC->GetTextExtent(m_configGrid.m_strDescription_of_the_unit);
#if 1
		pDC->TextOutW(
			graph_rect.left,
			graph_rect.bottom + (int)(rect.Height() * 0.02),
			m_configGrid.m_strDescription_of_the_unit);
#else
		pDC->TextOutW(
			graph_rect.right - textSize.cx,
			graph_rect.bottom + (int)(rect.Height() * 0.02), 
			m_strDescription_of_the_unit);
#endif
		//---------------------------------


#if 0
		//---------------------------------
		// [0] Spec 문자열로 표시
		//---------------------------------
		strSpec.Format(_T("Spec : %.3f ~ %.3f ("), m_dSpecMin, m_dSpecMax);
		strSpec += m_strDescription_of_the_unit;
		strSpec += _T(")");
		textSize = pDC->GetTextExtent(strSpec);
		pDC->TextOutW(
			graph_rect.left,
			graph_rect.bottom + (int)(rect.Height() * 0.02), 
			strSpec);
		//---------------------------------
#endif


		//---------------------------------
		// [1] Draw the spec line
		//---------------------------------
		if (m_configDataLine.m_bUseSpecLine)
		{
			if (m_configDataLine.m_dSpecMin < m_configDataLine.m_dDisplayMax &&
				m_configDataLine.m_dSpecMax > m_configDataLine.m_dDisplayMin)
			{
				// 펜
				CPen main_spec_pen(m_configDataLine.m_SpecLineStyle, m_configDataLine.m_SpecLineWidth, m_configDataLine.m_SpecLineColor);
				CPen* pOldPen = pDC->SelectObject(&main_spec_pen);

				int y = 0;

				// Draw the spec line
				if (m_configDataLine.m_dSpecMin > m_configDataLine.m_dDisplayMin)
				{
					y = (int)(((double)graph_rect.Height()) * (m_configDataLine.m_dSpecMin - m_configDataLine.m_dDisplayMin) / (m_configDataLine.m_dDisplayMax - m_configDataLine.m_dDisplayMin));
					y = graph_rect.Height() - y + graph_rect.top;
					pDC->MoveTo(graph_rect.left, y);
					pDC->LineTo(graph_rect.right, y);

					// 텍스트로 출력
					if (m_configDataLine.m_nFormat == 0)
					{
						strSpec.Format(_T("%d"), (int)m_configDataLine.m_dSpecMin);
					}
					else
					{
						strFormat.Format(_T("%%.%df"), m_configDataLine.m_nFormat);
						strSpec.Format(strFormat, m_configDataLine.m_dSpecMin);
					}
					textSize = pDC->GetTextExtent(strSpec);
#if 0
					pDC->TextOutW(
						graph_rect.right + (int)(rect.Width() * 0.01),
						y - textSize.cy / 2,
						strSpec);
#else
					// 왼쪽에 표시
					pDC->TextOutW(
						graph_rect.left - (int)(rect.Width() * 0.01) - textSize.cx,
						y - textSize.cy / 2,
						strSpec);
#endif
				}

				if (m_configDataLine.m_dSpecMax < m_configDataLine.m_dDisplayMax)
				{
					y = (int)((double)graph_rect.Height() * (m_configDataLine.m_dSpecMax - m_configDataLine.m_dDisplayMin) / (m_configDataLine.m_dDisplayMax - m_configDataLine.m_dDisplayMin));
					y = graph_rect.Height() - y + graph_rect.top;
					pDC->MoveTo(graph_rect.left, y);
					pDC->LineTo(graph_rect.right, y);

					// 텍스트로 출력
					if (m_configDataLine.m_nFormat == 0)
					{
						strSpec.Format(_T("%d"), (int)m_configDataLine.m_dSpecMax);
					}
					else
					{
						strFormat.Format(_T("%%.%df"), m_configDataLine.m_nFormat);
						strSpec.Format(strFormat, m_configDataLine.m_dSpecMax);
					}
					textSize = pDC->GetTextExtent(strSpec);
#if 0
					// 오른쪽에 표시
					pDC->TextOutW(
						graph_rect.right + (int)(rect.Width() * 0.01),
						y - textSize.cy / 2,
						strSpec);
#else
					// 왼쪽에 표시
					pDC->TextOutW(
						graph_rect.left - (int)(rect.Width() * 0.01) - textSize.cx,
						y - textSize.cy / 2,
						strSpec);
#endif
				}

				// Restore the old pen
				pDC->SelectObject(pOldPen);
			}
		}
		//---------------------------------



		//---------------------------------
		// [2] Draw the data line
		//---------------------------------
		if (m_data.size() > 0)
		{
			// 펜
			CPen main_data_pen(m_configDataLine.m_DataLineStyle, m_configDataLine.m_DataLineWidth, m_configDataLine.m_DataLineColor);
			CPen* pOldPen = m_BackDC.SelectObject(&main_data_pen);

			// Draw the data line
			double x_pitch = (double)graph_rect.Width() / (double)m_configDataLine.m_nDataCount;

			int x = (int)((double)graph_rect.left + round(x_pitch / 2.0));
			int x_start = x;
			int y = (int)((double)graph_rect.Height() * (m_data[0] - m_configDataLine.m_dDisplayMin) / (m_configDataLine.m_dDisplayMax - m_configDataLine.m_dDisplayMin));
			y = graph_rect.Height() - y + graph_rect.top;
			pDC->MoveTo(x, y);


			//------------
			// 점 표시
			//------------
			double dotsize = 0.1;
			CRect dot_rect;
			dot_rect.left = (int)((double)x - (x_pitch * dotsize));
			dot_rect.right = (int)((double)x + (x_pitch * dotsize));
			dot_rect.top = (int)((double)y - (x_pitch * dotsize));
			dot_rect.bottom = (int)((double)y + (x_pitch * dotsize));

			for (size_t i = 1; i < m_data.size(); i++)
			{
				x = (int)((double)x_start + (i * x_pitch));
				y = (int)((double)graph_rect.Height() * (m_data[i] - m_configDataLine.m_dDisplayMin) / (m_configDataLine.m_dDisplayMax - m_configDataLine.m_dDisplayMin));
				y = graph_rect.Height() - y + graph_rect.top;
				pDC->LineTo(x, y);

				// 점 표시 (이전 값을 표시한다.)
				if (m_configDataLine.m_bUseSpecLine && (m_data[i - 1] < m_configDataLine.m_dSpecMin || m_data[i - 1] > m_configDataLine.m_dSpecMax))
				{
					pDC->FillSolidRect(&dot_rect, RGB(255, 0, 0)); // 빨강색 채우기
				}
				else
				{
					pDC->FillSolidRect(&dot_rect, m_configDataLine.m_DataLineColor); // 검정으로 채우기
				}

				dot_rect.left = (int)((double)x - (x_pitch * dotsize));
				dot_rect.right = (int)((double)x + (x_pitch * dotsize));
				dot_rect.top = (int)((double)y - (x_pitch * dotsize));
				dot_rect.bottom = (int)((double)y + (x_pitch * dotsize));
			}
			//---------------------------------

			if (m_data.size() > 0)
			{
				int idxLast = (int)m_data.size() - 1;
				if (m_configDataLine.m_bUseSpecLine && (m_data[idxLast] < m_configDataLine.m_dSpecMin || m_data[idxLast] > m_configDataLine.m_dSpecMax))
				{
					pDC->FillSolidRect(&dot_rect, RGB(255, 0, 0)); // 빨강색 채우기
				}
				else
				{
					pDC->FillSolidRect(&dot_rect, m_configDataLine.m_DataLineColor); // 검정으로 채우기
				}
			}

			// Restore the old pen
			pDC->SelectObject(pOldPen);
		}
	}
}
