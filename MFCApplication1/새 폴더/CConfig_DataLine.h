#pragma once
class CConfig_DataLine
{
public:
	CConfig_DataLine();
	~CConfig_DataLine();

	// �Ҽ��� �ڸ���
	int m_nFormat;

	// ���� ����	��� ����
	BOOL m_bUseSpecLine;

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

