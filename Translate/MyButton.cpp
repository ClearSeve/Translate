// MyButton.cpp : 实现文件
//

#include "stdafx.h"
#include "Translate.h"
#include "MyButton.h"


// CMyButton

IMPLEMENT_DYNAMIC(CMyButton, CButton)

CMyButton::CMyButton()
{
    // 默认鼠标没有在上面
    m_bMouseOver = FALSE;

}

CMyButton::~CMyButton()
{
}


BEGIN_MESSAGE_MAP(CMyButton, CButton)
    ON_WM_MOUSEMOVE()
    ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)//需要调用别的函数消息触发
END_MESSAGE_MAP()



// CMyButton 消息处理程序



void CMyButton::PreSubclassWindow()
{
    // 增加自绘制风格
    ModifyStyle(0,BS_OWNERDRAW);

    CButton::PreSubclassWindow();
}

void CMyButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    //////////////////////////////////////////////////////////////////////////
    CDC   MemDC;   //首先定义一个显示设备对象   
    CBitmap   MemBitmap;//定义一个位图对象   
    //随后建立与屏幕显示兼容的内存显示设备   
    MemDC.CreateCompatibleDC(NULL);   
    //这时还不能绘图，因为没有地方画   ^_^   
    //////////////////////////////////////////////////////////////////////////

    // 获取绘图对象
    CDC dc; 
    dc.Attach(lpDrawItemStruct->hDC);

    //////////////////////////////////////////////////////////////////////////
    //下面建立一个与屏幕显示兼容的位图，至于位图的大小嘛，可以用窗口的大小   
    MemBitmap.CreateCompatibleBitmap(&dc,lpDrawItemStruct->rcItem.right,lpDrawItemStruct->rcItem.bottom);
    //将位图选入到内存显示设备中   
    //只有选入了位图的内存显示设备才有地方绘图，画到指定的位图上   
    CBitmap   *pOldBit=MemDC.SelectObject(&MemBitmap);   
    // 保存BRUSH结构体信息
    LOGBRUSH LogBrush = {0};
    // 创建画刷
    CBrush* pSysBrush = CBrush::FromHandle((HBRUSH)GetStockObject(4                       ));
   
    // 获取BRUSH画刷颜色
    pSysBrush->GetLogBrush(&LogBrush);
    
    //先用背景色将位图清除干净，这里我用的是白色作为背景   
    //你也可以用自己应该用的颜色   
    MemDC.FillSolidRect(0,0,lpDrawItemStruct->rcItem.right,lpDrawItemStruct->rcItem.bottom,LogBrush.lbColor);   
    
    
    //////////////////////////////////////////////////////////////////////////

    // 创建画刷对象
    CBrush brush;
    // 创建白色画刷
    brush.CreateSolidBrush(RGB(255,255,255));
   
    // 将画刷设置到绘图对象
    CBrush* pOldBrush = dc.SelectObject(&brush);
    // 绘制图形
    MemDC.RoundRect(&lpDrawItemStruct->rcItem,CPoint(10,10));
    // 设置就画刷
    MemDC.SelectObject(pOldBrush);
    // 设置背景透明
    MemDC.SetBkMode(TRANSPARENT);
    

    if(m_bMouseOver==TRUE)//判断是否在BUTTON中
    {//鼠标在上面
        MemDC.SetTextColor(RGB(0,114,227)); // 设置黑色文本
    }else
    {//鼠标不再上面
        MemDC.SetTextColor(RGB(0,0,0)); // 设置蓝色文本
    }
  
    // 绘制文字
    MemDC.DrawText(_T("Hello"),&lpDrawItemStruct->rcItem,DT_CENTER | DT_VCENTER | DT_SINGLELINE );

    //////////////////////////////////////////////////////////////////////////
    //将内存中的图拷贝到屏幕上进行显示   
    dc.BitBlt(0,0,lpDrawItemStruct->rcItem.right,lpDrawItemStruct->rcItem.bottom,&MemDC,0,0,SRCCOPY);   
    //绘图完成后的清理   
    MemBitmap.DeleteObject();   
    MemDC.DeleteDC();   
    //////////////////////////////////////////////////////////////////////////
}

void CMyButton::OnMouseMove(UINT nFlags, CPoint point)
{
    CButton::OnMouseMove(nFlags, point);

    if (m_bMouseOver==FALSE)//如果一开始的FALSE,就是说明没在
    {
        m_bMouseOver = TRUE;//然后就给修改为TRUE
        Invalidate(FALSE);//调用刷新
    }

    //////////////////////////////////////////////////////////////////////////
    //设置触发鼠标离开
    TRACKMOUSEEVENT et = {0};
    et.cbSize = sizeof(et);
    et.hwndTrack = m_hWnd;
    et.dwFlags = TME_LEAVE;//鼠标离开时通知
    et.dwHoverTime = HOVER_DEFAULT;//默认时间
    _TrackMouseEvent(&et);
}

LRESULT CMyButton::OnMouseLeave(WPARAM wParam,LPARAM lParam)
{
    //设置鼠标离开
    m_bMouseOver = FALSE;
    Invalidate(FALSE);//不用背景填充
    return TRUE;
} 
