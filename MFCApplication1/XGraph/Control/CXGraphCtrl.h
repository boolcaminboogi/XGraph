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

    // �ֱٰ��� ������ �� �ִ�.
    void AppendValue(double dValue);
    // ������ ǥ�� (OnPaint���� ȣ���)
    virtual void OnPaint_DataLine(CDC* pDC);

protected:
    std::vector<double> m_data;  // ��� ������ ���ø� Ÿ������ ����
};
