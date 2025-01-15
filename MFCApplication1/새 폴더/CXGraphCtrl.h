#pragma once
#include <afxwin.h>
#include "CXGraphCtrlBase.h"
#include <vector>  // STL vector ����� ���� ���

using namespace std;

class CXGraphCtrl : public CXGraphCtrlBase
{
public:
    CXGraphCtrl();
    ~CXGraphCtrl();

    // Ÿ��Ʋ
    void SetTitle(CString strTitle);
    // ����
    void SetDescription_of_the_unit(CString strUnit);
    
    // Display Data Min, Max ����
    void SetDisplayData(double dMin, double dMax);

    // �ֱٰ��� ������ �� �ִ�.
    void AppendValue(double dValue);
    // ������ ǥ�� (OnPaint���� ȣ���)
    virtual void OnPaint_DataLine(CDC* pDC);

protected:
    std::vector<double> m_data;  // ��� ������ ���ø� Ÿ������ ����
};
