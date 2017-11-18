
// TranslateDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "LanguageDialog.h"
#include "MyButton.h"
#include "TranslateView.h"

// CTranslateDlg 对话框
class CTranslateDlg : public CDialog
{
// 构造
public:
	CTranslateDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TRANSLATE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
public:

    // 翻译前的视图
    CTranslateView* m_pFrontView;
    // 翻译后的视图
    CTranslateView* m_pArrayView[26];

    CLanguageDialog* m_pFrontLonguage;
    CLanguageDialog* m_pBehindLonguage;

    // 翻译前语言选择按钮
    CButton m_wndFront;
    // 后按钮语言选择
    CButton m_wndBehind;
    
    

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
    virtual BOOL OnInitDialog() ;
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    
    afx_msg void OnBnClickedFront();
    afx_msg void OnMove(int x, int y);
    virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
    afx_msg void OnDestroy();
    afx_msg void OnBnClickedTranslate();

protected:
    virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
public:
    
    afx_msg void OnBnClickedBehind();
};
