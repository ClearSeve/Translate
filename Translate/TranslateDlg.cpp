
// TranslateDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Translate.h"
#include "TranslateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTranslateDlg 对话框




CTranslateDlg::CTranslateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTranslateDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CTranslateDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_FRONT, m_wndFront);
    DDX_Control(pDX, IDC_BEHIND, m_wndBehind);
}

BEGIN_MESSAGE_MAP(CTranslateDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_FRONT, &CTranslateDlg::OnBnClickedFront)
    ON_WM_MOVE()
    ON_WM_DESTROY()
    ON_BN_CLICKED(IDC_TRANSLATE, &CTranslateDlg::OnBnClickedTranslate)
    ON_BN_CLICKED(IDC_BEHIND, &CTranslateDlg::OnBnClickedBehind)
    
END_MESSAGE_MAP()


// CTranslateDlg 消息处理程序

BOOL CTranslateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标



    // 创建视图对象
    m_pFrontView = new CTranslateView(_T("自动检测"),_T("auto"),TRUE);
	// 创建视图
    m_pFrontView->Create(L"",L"",WS_CHILD|WS_VISIBLE,CRect(10,50,440,500),this,NULL,NULL);
    m_pFrontView->OnInitialUpdate();
    // 创建视图对象
    m_pArrayView[0] = new CTranslateView(_T("英语"),_T("en"));
    // 创建视图
     m_pArrayView[0]->Create(L"",L"",WS_CHILD|WS_VISIBLE,CRect(440,50,1100,500),this,NULL,NULL);
     m_pArrayView[0]->OnInitialUpdate();

     // 创建窗口对象(翻译前的语言选择)
     m_pFrontLonguage = new CLanguageDialog(&m_wndFront,m_pFrontView,TRUE);
     // 创建窗口
     m_pFrontLonguage->Create(IDD_TRANSLATEDIALOG);



     // 创建窗口对象(翻译后的语言选择)
     m_pBehindLonguage = new CLanguageDialog(&m_wndBehind,m_pArrayView[0],FALSE);
     // 创建窗口
     m_pBehindLonguage->Create(IDD_TRANSLATEDIALOG);
     // 显示窗口
    
     // 互相传递互斥对象
     m_pFrontLonguage->m_pMutexObject = m_pBehindLonguage;


     // 设置默认前按钮名称
     m_wndFront.SetWindowText(_T("自动检测"));
     // 设置默认后按钮名称
    m_wndBehind.SetWindowText(_T("英语"));



    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTranslateDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTranslateDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTranslateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 点击按钮(翻译前)语言选择
void CTranslateDlg::OnBnClickedFront()
{
    
    // 保存对话框的位置
    CRect DialogRect;
    // 获取对话框的位置
    GetDlgItem(IDC_FRONT)->GetWindowRect(&DialogRect);
    // 设置窗口位置
    m_pFrontLonguage->SetWindowPos(NULL,DialogRect.left,DialogRect.bottom,0,0,SWP_NOSIZE);

    // 设置输入焦点
    
    

    // 显示窗口
    
    m_pFrontLonguage->SetFocus();
    
    m_pFrontLonguage->ShowWindow(SW_SHOW);
    
    
    m_pFrontLonguage->UpdateWindow();
    m_pFrontLonguage->SetActiveWindow();
    
        
    
}

// 点击按钮(需要翻译成的语言)语言选择
void CTranslateDlg::OnBnClickedBehind()
{
    // 保存对话框的位置
    CRect DialogRect;
    // 获取对话框的位置
    GetDlgItem(IDC_BEHIND)->GetWindowRect(&DialogRect);
    // 设置窗口位置
    m_pBehindLonguage->SetWindowPos(NULL,DialogRect.left,DialogRect.bottom,0,0,SWP_NOSIZE);
    // 设置输入焦点
    
    
    
    m_pBehindLonguage->SetFocus();
    // 显示窗口
    m_pBehindLonguage->ShowWindow(SW_SHOW);
    m_pBehindLonguage->SetActiveWindow();
   
    
}





void CTranslateDlg::OnMove(int x, int y)
{
    CDialog::OnMove(x, y);

    //// 保存对话框的位置
    //CRect DialogRect;
    //// 获取对话框的位置
    //GetDlgItem(IDC_FRONT)->GetWindowRect(&DialogRect);
    //// 设置窗口位置
    //m_pDialog->SetWindowPos(NULL,DialogRect.left,DialogRect.bottom,0,0,SWP_NOSIZE);

    
    
}

BOOL CTranslateDlg::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
    // TODO: 在此添加专用代码和/或调用基类

    return CDialog::Create(lpszTemplateName, pParentWnd);
}

void CTranslateDlg::OnDestroy()
{
    CDialog::OnDestroy();

    // 销毁翻译语言对话框
    m_pFrontLonguage->DestroyWindow();
    
    // 销毁子对话框
    

}

void CTranslateDlg::OnBnClickedTranslate()
{
    // 获取窗口内容
    m_pFrontView->GetDlgItem(IDC_EDIT)->GetWindowText(CTranslateView::strText);
    // 翻译
    m_pArrayView[0]->Translate();
}



BOOL CTranslateDlg::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
    return CDialog::OnWndMsg(message, wParam, lParam, pResult);
}


