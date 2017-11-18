#pragma once


// #import "c:\\windows\system32\\winhttp.dll" no_namespace 
#import "c:\\windows\system32\\winhttpcom.dll" no_namespace 

// CTranslateView 窗体视图

class CTranslateView : public CFormView
{
	DECLARE_DYNCREATE(CTranslateView)

public:
    CTranslateView( );
	CTranslateView( CString Title,CString Language,BOOL IsWrite = FALSE);           // 动态创建所使用的受保护的构造函数
	virtual ~CTranslateView();
public:
    // 翻译并显示在EDIT中
    void Translate( );
public:

    // 显示在上面的标题
    CString m_strTitle;
    // 需要翻译的语言
    CString m_strLanguage;
    // 是否可以输入内容
    BOOL m_bIsWrite;
public:
    // 需要翻译的字符串
    static CString strText;
    // 需要翻译字符串的语言
    static CString strPreLanguage;
    
    size_t g_f_wctou8(char * dest_str, const wchar_t src_wchar);
public:
	enum { IDD = IDD_TEXT };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
    virtual void OnInitialUpdate();

private:
	IWinHttpRequestPtr m_pHttpReq;

};


