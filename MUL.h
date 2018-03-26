// MUL.h : main header file for the MUL application
//

#if !defined(AFX_MUL_H__AF535045_B01D_11D4_8B78_5254AB1F6EC3__INCLUDED_)
#define AFX_MUL_H__AF535045_B01D_11D4_8B78_5254AB1F6EC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMULApp:
// See MUL.cpp for the implementation of this class
//
struct POINTINFO
{
	int code;
	int addr;
	int name;
};
class CMULApp : public CWinApp
{
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CMULApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMULApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMULApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MUL_H__AF535045_B01D_11D4_8B78_5254AB1F6EC3__INCLUDED_)
