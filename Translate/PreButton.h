#pragma once


// CPreButton

class CPreButton : public CButton
{
	DECLARE_DYNAMIC(CPreButton)

public:
	CPreButton();
	virtual ~CPreButton();

protected:
	DECLARE_MESSAGE_MAP()
    virtual void PreSubclassWindow();
public:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnEnable(BOOL bEnable);

    afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
};


