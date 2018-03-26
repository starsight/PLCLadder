#if !defined(AFX_ARESET_H__6BB5A7A3_B164_11D4_8B78_5254AB1F6EC3__INCLUDED_)
#define AFX_ARESET_H__6BB5A7A3_B164_11D4_8B78_5254AB1F6EC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AreSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAreSet dialog

class CAreSet : public CDialog
{
// Construction
public:
	UINT MinWidth;
	UINT MinHigh;
	UINT MaxWidth;
	UINT MaxHigh;
	void InitData(UINT x1,UINT x2,UINT y1,UINT y2);
	CAreSet(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAreSet)
	enum { IDD = IDD_WORKARESET };
	CStatic	m_strPageWidth;
	CStatic	m_strPageHigh;
	UINT	m_nHigh;
	UINT	m_nWidth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAreSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAreSet)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARESET_H__6BB5A7A3_B164_11D4_8B78_5254AB1F6EC3__INCLUDED_)
