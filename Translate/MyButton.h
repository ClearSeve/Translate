#pragma once


// CMyButton

class CMyButton : public CButton
{
	DECLARE_DYNAMIC(CMyButton)

public:
	CMyButton();
	virtual ~CMyButton();
public:
    // 保存了鼠标是否在按钮上面
    BOOL m_bMouseOver;
protected:
	DECLARE_MESSAGE_MAP()
    virtual void PreSubclassWindow();
    LRESULT OnMouseLeave(WPARAM wParam,LPARAM lParam);
public:
    virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};


