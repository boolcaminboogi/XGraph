#pragma once
class CConfig_DataLine
{
public:
	CConfig_DataLine();
	~CConfig_DataLine();

	void SetDefault();

	// Data Spec Min, Max ����
	void SetSpec(double dMin, double dMax);
	// Min, Max spec ��������
	double GetSpecMin()
	{
		return m_dSpecMin;
	};
	double GetSpecMax()
	{
		return m_dSpecMax;
	};

	// Display Data Min, Max ����
	void SetDisplayData(double dMin, double dMax);




	// �Ҽ��� �ڸ���
	int m_nFormat;

	// ȭ�鿡 ǥ�õǴ� �� ���� (min ~ max)
	double m_dDisplayMin;
	double m_dDisplayMax;

	// ���� ����	��� ����
	BOOL m_bUseSpecLine;

	// min / max
	double m_dSpecMin;
	double m_dSpecMax;

	// ���� ���� ����
	COLORREF m_SpecLineColor;

	// ���� ���� �β�
	int m_SpecLineWidth;

	// ���� ���� ��Ÿ��
	int m_SpecLineStyle;


	// ������ ���� ����
	COLORREF m_DataLineColor;

	// ������ ���� �β�
	int m_DataLineWidth;

	// ������ ���� ��Ÿ��
	int m_DataLineStyle;

	// ǥ���� ������ ����
	size_t m_nDataCount;
};

