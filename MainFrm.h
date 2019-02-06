// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__AF535049_B01D_11D4_8B78_5254AB1F6EC3__INCLUDED_)
#define AFX_MAINFRM_H__AF535049_B01D_11D4_8B78_5254AB1F6EC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetMousePosText(CString strText);
	virtual ~CMainFrame();
	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CToolBar	m_wndDrawTool;
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnCommunDownload();
	afx_msg void OnCommunUpload();
	//}}AFX_MSG
	//afx_msg void OnUpdateMousePos(CCmdUI *pCmdUI);
	DECLARE_MESSAGE_MAP()

public:
	//TRUE:  обть
	//FALSEE:иоть
	BOOL m_bDownload;
	afx_msg void On32814();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__AF535049_B01D_11D4_8B78_5254AB1F6EC3__INCLUDED_)
