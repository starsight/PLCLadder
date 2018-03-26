#if !defined(AFX_POINTSET_H__6BB5A7A1_B164_11D4_8B78_5254AB1F6EC3__INCLUDED_)
#define AFX_POINTSET_H__6BB5A7A1_B164_11D4_8B78_5254AB1F6EC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PointSet.h : header file
//
class IOPOINT;
/////////////////////////////////////////////////////////////////////////////
// CPointSet dialog

class CPointSet : public CDialog
{
// Construction
public:
	IOPOINT * m_pPoint;
	int m_nType;
	CPointSet(IOPOINT *point,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPointSet)
	enum { IDD = IDD_POINTSET };
	CString	m_strAddr;
	CString	m_Caption;
	CString	m_strName;
	CString	m_strNote;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPointSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPointSet)
	afx_msg void OnChangeAddr();
	afx_msg void OnClose();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POINTSET_H__6BB5A7A1_B164_11D4_8B78_5254AB1F6EC3__INCLUDED_)
