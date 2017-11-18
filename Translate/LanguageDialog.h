#pragma once

#include "PreButton.h"
#include "TranslateView.h"
// CLanguageDialog 对话框

class CLanguageDialog : public CDialog
{
	DECLARE_DYNAMIC(CLanguageDialog)
    CBrush   m_brush;
public:
	CLanguageDialog(CWnd* pParent = NULL);   // 标准构造函数
    CLanguageDialog(CButton* pButton,CTranslateView* pView ,BOOL bIsFront,  CWnd* pParent = NULL);
	virtual ~CLanguageDialog();
    // 异形窗口
    CRgn m_rgn;
    // 语言选择按钮
    CButton* m_pButton;
    // 是否为翻译前的窗口类型
    BOOL m_bIsFront;
    // 自动检测
    CPreButton m_wndAutoBut;
    // 翻译语言
    CPreButton m_wndBut[27];
    // 旧互斥ID
    UINT m_nOldID;

    CLanguageDialog* m_pMutexObject;

    // 翻译前的视图
    CTranslateView* m_pView;
    wchar_t* GetLanguagText(UINT nID);
public:
    
// 对话框数据
	enum { IDD = IDD_TRANSLATEDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnKillFocus(CWnd* pNewWnd);
public:
    virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
    afx_msg void OnPaint();
    // 翻译前的语言处理函数
    afx_msg void OnCommand(UINT nID);

    afx_msg void OnSetFocus(CWnd* pOldWnd);
    afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
    afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
};
