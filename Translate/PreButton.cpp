// PreButton.cpp : 实现文件
//

#include "stdafx.h"
#include "Translate.h"
#include "PreButton.h"


// CPreButton

IMPLEMENT_DYNAMIC(CPreButton, CButton)

CPreButton::CPreButton()
{

}

CPreButton::~CPreButton()
{
}


BEGIN_MESSAGE_MAP(CPreButton, CButton)
    ON_WM_CREATE()
    ON_WM_ENABLE()
    ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()



// CPreButton 消息处理程序



void CPreButton::PreSubclassWindow()
{
    CButton::PreSubclassWindow();
   
    
}

int CPreButton::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CButton::OnCreate(lpCreateStruct) == -1)
        return -1;
    // 设置字体
    SetFont(CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT)));


    return 0;
}

void CPreButton::OnEnable(BOOL bEnable)
{
    CButton::OnEnable(bEnable);
    // 设置为勾选状态
    //SetCheck(1);
    SendMessage(BM_SETCHECK,BST_CHECKED);
}




HBRUSH CPreButton::CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/)
{
    // 返回刷子颜色
    HBRUSH brush = CreateSolidBrush (RGB(135,206,235));

    return brush;
}
