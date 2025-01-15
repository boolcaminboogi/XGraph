#pragma once
class CConfig_DataLine
{
public:
	CConfig_DataLine();
	~CConfig_DataLine();

	// 소수점 자리수
	int m_nFormat;

	// 스펙 라인	사용 여부
	BOOL m_bUseSpecLine;

	// 스펙 라인 색상
	COLORREF m_SpecLineColor;

	// 스펙 라인 두께
	int m_SpecLineWidth;

	// 스펙 라인 스타일
	int m_SpecLineStyle;



	// 데이터 라인 색상
	COLORREF m_DataLineColor;

	// 데이터 라인 두께
	int m_DataLineWidth;

	// 데이터 라인 스타일
	int m_DataLineStyle;

	// 표시할 데이터 개수
	size_t m_nDataCount;
};

