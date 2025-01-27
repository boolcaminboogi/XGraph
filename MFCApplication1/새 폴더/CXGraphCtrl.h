#pragma once
#include <afxwin.h>
#include "CXGraphCtrlBase.h"
#include <vector>  // STL vector 사용을 위한 헤더

using namespace std;

class CXGraphCtrl : public CXGraphCtrlBase
{
public:
    CXGraphCtrl();
    ~CXGraphCtrl();

    // 타이틀
    void SetTitle(CString strTitle);
    // 단위
    void SetDescription_of_the_unit(CString strUnit);
    
    // Display Data Min, Max 세팅
    void SetDisplayData(double dMin, double dMax);

    // 최근값만 셋팅할 수 있다.
    void AppendValue(double dValue);
    // 데이터 표시 (OnPaint에서 호출됨)
    virtual void OnPaint_DataLine(CDC* pDC);

protected:
    std::vector<double> m_data;  // 멤버 변수를 템플릿 타입으로 선언
};
