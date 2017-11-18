// LanguageDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "Translate.h"
#include "LanguageDialog.h"



// CLanguageDialog 对话框

IMPLEMENT_DYNAMIC(CLanguageDialog, CDialog)

CLanguageDialog::CLanguageDialog(CWnd* pParent /*=NULL*/) : CDialog(CLanguageDialog::IDD, pParent)
{
    // 语言选择按钮
    m_pButton = NULL;
    // 是否为前一个的按钮
    m_bIsFront = TRUE;
}

CLanguageDialog::CLanguageDialog(CButton* pButton,CTranslateView* pView ,BOOL bIsFront ,CWnd* pParent/*=NULL*/ ) : CDialog(CLanguageDialog::IDD, pParent)
{
    // 语言选择按钮
    m_pButton = pButton;
    // 是否为前一个的按钮
    m_bIsFront = bIsFront;
    m_pView = pView;
    // 互斥对象
    m_pMutexObject = NULL;
}

CLanguageDialog::~CLanguageDialog()
{
}

void CLanguageDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLanguageDialog, CDialog)
    ON_WM_CTLCOLOR()
    ON_WM_LBUTTONDOWN()
    ON_WM_KILLFOCUS()
    ON_WM_PAINT()
    ON_COMMAND_RANGE(0xF0,0x10B,OnCommand)
    ON_WM_SETFOCUS()
    ON_WM_NCLBUTTONDOWN()
    ON_WM_ACTIVATE()
END_MESSAGE_MAP()


// CLanguageDialog 消息处理程序
BOOL CLanguageDialog::OnInitDialog()
{
    CDialog::OnInitDialog();


    CRect rc; // rounded rectangle 
    GetClientRect(&rc); // window rect in screen coords
    m_rgn.CreateRoundRectRgn(rc.left,rc.top,rc.right,rc.bottom,3,3); 
    //设置这个区域
    SetWindowRgn(m_rgn,TRUE); // set window region to make rounded window
    // 设置窗口颜色
    m_brush.CreateSolidBrush(RGB(135,206,235));   //   生成一白色刷子 


    // 第一列
    m_wndBut[0].Create(_T("阿拉伯语"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(15,75,80,95),this,0xF0);
    m_wndBut[1].Create(_T("爱沙尼亚语"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(15,100,90,120),this,0xF1);
    m_wndBut[2].Create(_T("保加利亚语"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(15,125,90,145),this,0xF2);
    m_wndBut[3].Create(_T("波兰语"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(15,150,65,170),this,0xF3);
    // 第二列
    m_wndBut[4].Create(_T("丹麦语"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(105,75,155,95),this,0xF4);
    m_wndBut[5].Create(_T("德语"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(105,100,145,120),this,0xF5);
    m_wndBut[6].Create(_T("俄语"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(105,125,145,145),this,0xF6);
    m_wndBut[7].Create(_T("法语"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(105,150,145,170),this,0xF7);
    m_wndBut[8].Create(_T("芬兰语"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(105,175,155,195),this,0xF8);
    // 第三列
    m_wndBut[9].Create(_T("韩语"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(175,75,215,95),this,0xF9);
    m_wndBut[10].Create(_T("荷兰语"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(175,100,225,120),this,0xFA);
    m_wndBut[11].Create(_T("捷克语"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(175,125,225,145),this,0xFB);
    m_wndBut[12].Create(_T("罗马尼亚语"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(175,150,245,170),this,0xFC);
    // 第四列
    m_wndBut[13].Create(_T("葡萄牙语"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(270,75,335,95),this,0xFD);
    m_wndBut[14].Create(_T("日语"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(270,100,310,120),this,0xfE);
    m_wndBut[15].Create(_T("瑞典语"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(270,125,320,145),this,0xFF);
    m_wndBut[16].Create(_T("斯洛文尼亚语"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(270,150,350,170),this,0x100);
    m_wndBut[17].Create(_T("泰语"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(270,175,310,195),this,0x101);
    // 第五列
    m_wndBut[18].Create(_T("文言文"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(365,75,415,95),this,0x102);
    m_wndBut[19].Create(_T("西班牙语"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(365,100,430,120),this,0x103);
    m_wndBut[20].Create(_T("希腊语"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(365,125,415,145),this,0x104);
    m_wndBut[21].Create(_T("匈牙利语"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(365,150,430,170),this,0x105);
    // 第六列
    m_wndBut[22].Create(_T("中文"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(450,75,490,95),this,0x106);
    m_wndBut[23].Create(_T("英语"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(450,100,490,120),this,0x107);
    m_wndBut[24].Create(_T("意大利语"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(450,125,515,145),this,0x108);
    m_wndBut[25].Create(_T("粤语"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(450,150,490,170),this,0x109);
    m_wndBut[26].Create(_T("中文繁体"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(450,175,515,195),this,0x10A);
    
    if(m_bIsFront == TRUE)
    {// 翻译前语言选择视图
        // 自动输入的语言
        m_wndAutoBut.Create(_T("自动检测"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(10,10,90,36),this,0x10B);
        // 设置默认语言字符串
        CTranslateView::strPreLanguage = _T("auto");
        // 默认旧ID为自动检测
        m_nOldID = 0x10B;
        
    }else
    {// 需要翻译成什么语言选择视图
        // 默认英语
        m_nOldID = 0x107;
        // 循环添加 勾选框
        for (int nIndex = 0;nIndex<27;nIndex++)
        {
            //m_wndBut[nIndex].ModifyStyle(0,BS_CHECKBOX|BS_AUTOCHECKBOX);
        }
        
    }

    // 设置自动检测禁止
    GetDlgItem(m_nOldID)->EnableWindow(FALSE);
    




    return TRUE;  // return TRUE unless you set the focus to a contro
    // 异常: OCX 属性页应返回 FALSE
}



HBRUSH CLanguageDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialog::OnCtlColor(pDC,   pWnd,   nCtlColor);

    ////在这加一条是否为对话框的判断语句
    if(nCtlColor == CTLCOLOR_DLG)
        return m_brush;   //返加绿色刷子

    return   hbr;
}

void CLanguageDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
    //ShowWindow(SW_HIDE);

    CDialog::OnLButtonDown(nFlags, point);
}


void CLanguageDialog::OnKillFocus(CWnd* pNewWnd)
{
    ShowWindow(SW_HIDE);
    CDialog::OnKillFocus(pNewWnd);
    
    
}

BOOL CLanguageDialog::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{

    return CDialog::OnWndMsg(message, wParam, lParam, pResult);
}


void CLanguageDialog::OnPaint()
{
    CPaintDC dc(this); // device context for painting

    // 设置新字体
    CFont* pOldFont = dc.SelectObject(CFont::FromHandle( (HFONT)GetStockObject(DEFAULT_GUI_FONT)));

    // 设置透明
    dc.SetBkMode(TRANSPARENT);
    // 绘制文本
    dc.TextOut(15,60,_T("ABC"));
    dc.TextOut(105,60,_T("DEFG"));
    dc.TextOut(175,60,_T("HIJKLMN"));
    dc.TextOut(270,60,_T("OPQRST"));
    dc.TextOut(365,60,_T("UVWX"));
    dc.TextOut(450,60,_T("YZ"));
    

    // 设置旧字体
    dc.SelectObject(pOldFont);

}
void CLanguageDialog::OnCommand(UINT nID)
{
    // 保存临时按钮名称
    CString strWindowName;
    
    // 禁止按钮
    GetDlgItem(nID)->EnableWindow(FALSE);
    // 设置旧ID为可以点击状态
    GetDlgItem(m_nOldID)->EnableWindow(TRUE);
   

    // 获取名称,
    GetDlgItem(nID)->GetWindowText(strWindowName);
    // 设置到按钮中
    m_pButton->SetWindowText(strWindowName);
    // 设置到提示框中
    m_pView->GetDlgItem(IDC_TYPE)->SetWindowText(strWindowName);

    // 根据ID复制语言类型
    // 判断是否为输入的语言对象
    if ( m_bIsFront == TRUE)
    {

        // 判断是否是自动判断
        if ( m_nOldID != 0x10B)
        { // 解除禁止
            m_pMutexObject->GetDlgItem(m_nOldID)->EnableWindow(TRUE);
        }

        // 判断是否是 自动判断ID
        if (nID!=0x10B)
        {// 不是才发送 向同类对象发送互斥操作
            m_pMutexObject->GetDlgItem(nID)->EnableWindow(FALSE);
        }

        // 设置语言字符串
        CTranslateView::strPreLanguage = GetLanguagText(nID);
    }else
    {
        // 判断是否为单条
        // 判断是否为自动判断
        if( nID!=0x10B )
        {
            // 设置翻译后的语言
            m_pView->m_strLanguage = GetLanguagText(nID);
            
        }
    }


    // 保存为旧ID
    m_nOldID = nID;
    // 隐藏窗口
    ShowWindow(SW_HIDE);
}

wchar_t* CLanguageDialog::GetLanguagText(UINT nID)
{


    // 阿拉伯语
    if(nID == 0xF0 )
        return L"ara";
    // 爱沙尼亚语
    else if ( nID == 0xF1 )
        return L"est";
    // 保加利亚语
    else if ( nID == 0xF2 )
        return L"bul";
    // 波兰语
    else if ( nID == 0xF3 )
        return L"pl";
    // 丹麦语
    else if( nID == 0xF4 )
        return L"dan";
    // 德语
    else if( nID == 0xF5 )
        return L"de";
    // 俄语
    else if( nID == 0xF6 )
        return L"ru";
    // 法语
    else if( nID == 0xF7 )
        return L"fra";
    // 芬兰语
    else if( nID == 0xF8 )
        return L"fin";
    // 韩语
    else if( nID == 0xF9 )
        return L"kor";
    // 荷兰语
    else if( nID == 0xFA )
        return L"nl";
    // 捷克语
    else if( nID == 0xFB )
        return L"cs";
    // 罗马尼亚语
    else if( nID == 0xFC )
        return L"rom";
    // 葡萄牙语
    else if( nID == 0xFD )
        return L"pt";
    // 日语
    else if( nID == 0xFE )
        return L"jp";
    // 瑞典语
    else if( nID == 0xFF )
        return L"swe";
    // 斯洛文尼亚语
    else if( nID == 0x100 )
        return L"slo";
    // 泰语
    else if( nID == 0x101 )
        return L"th";
    // 文言文
    else if( nID == 0x102 )
        return L"wyw";
    // 西班牙语
    else if( nID == 0x103 )
        return L"spa";
    // 希腊语
    else if( nID == 0x104 )
        return L"el";
    // 匈牙利语
    else if ( nID == 0x105 )
        return L"hu";
    // 中文
    else if ( nID == 0x106 )
        return L"zh";
    // 英语
    else if ( nID == 0x107 )
        return L"en";
    // 意大利语
    else if ( nID == 0x108 )
        return L"it";
    // 粤语
    else if ( nID == 0x109 )
        return L"yue";
    // 中文繁体
    else if ( nID == 0x10A )
        return L"cht";
    // 自动检测
    else 
        return L"auto";
}

void CLanguageDialog::OnSetFocus(CWnd* pOldWnd)
{
    CDialog::OnSetFocus(pOldWnd);

    // TODO: 在此处添加消息处理程序代码
}

void CLanguageDialog::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值

    CDialog::OnNcLButtonDown(nHitTest, point);
}

void CLanguageDialog::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
    CDialog::OnActivate(nState, pWndOther, bMinimized);
    // 没有输入焦点
    if( WA_INACTIVE == nState)
    {
        // 隐藏窗口
        ShowWindow(SW_HIDE);
    }
}
