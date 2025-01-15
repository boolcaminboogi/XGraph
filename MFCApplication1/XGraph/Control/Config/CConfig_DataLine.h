#pragma once
class CConfig_DataLine
{
public:
	CConfig_DataLine();
	~CConfig_DataLine();

	void SetDefault();

	// Data Spec Min, Max 세팅
	void SetSpec(double dMin, double dMax);
	// Min, Max spec 가져오기
	double GetSpecMin()
	{
		return m_dSpecMin;
	};
	double GetSpecMax()
	{
		return m_dSpecMax;
	};

	// Display Data Min, Max 세팅
	void SetDisplayData(double dMin, double dMax);




	// 소수점 자리수
	int m_nFormat;

	// 화면에 표시되는 값 영역 (min ~ max)
	double m_dDisplayMin;
	double m_dDisplayMax;

	// 스펙 라인	사용 여부
	BOOL m_bUseSpecLine;

	// min / max
	double m_dSpecMin;
	double m_dSpecMax;

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

