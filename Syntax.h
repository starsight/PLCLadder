#if !defined(AFX_SYNTAX_H__6BB5A7A2_B164_11D4_8B78_5254AB1F6EC3__INCLUDED_)
#define AFX_SYNTAX_H__6BB5A7A2_B164_11D4_8B78_5254AB1F6EC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Syntax.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSyntax dialog

class CSyntax : public CDialog
{
// Construction
public:
	void Refresh(CString str);
	CSyntax(CString str,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSyntax)
	enum { IDD = IDD_SYNTAX };
	CString	m_strList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSyntax)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSyntax)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYNTAX_H__6BB5A7A2_B164_11D4_8B78_5254AB1F6EC3__INCLUDED_)
