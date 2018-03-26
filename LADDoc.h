#if !defined(AFX_LADDOC_H__EC306101_B09B_11D4_8B78_5254AB1F6EC3__INCLUDED_)
#define AFX_LADDOC_H__EC306101_B09B_11D4_8B78_5254AB1F6EC3__INCLUDED_

#include "IOPOINT.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LADDoc.h : header file
//
//#include "Iopoint.h"

/////////////////////////////////////////////////////////////////////////////
// CLADDoc document
class CSyntax;

class CLADDoc : public CDocument
{
protected:
	
	CLADDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CLADDoc)

// Attributes
public:
protected:
	CObArray m_pointArray;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLADDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetRowCol(int row,int col);
	BOOL OpenFlag;
	void UpdateWorkare(CDC *pDC);
	void ReDraw(int x,int y,CDC *pDC);
	void Process(UINT pID,int x,int y,CDC *pDC);
	CSyntax * err_dlg;
	PLC  m_mPlc;
	int  TestPointType(int row,int col);
	void SetAddition(int row,int col,int flag,CString str);
	void insert_point(UINT pID,int x,int y,int row,int col,CDC *pDC);
	void erase_point(int x,int y,CDC *pDC);
	virtual ~CLADDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	void DeletePoints();
	//{{AFX_MSG(CLADDoc)
	afx_msg void OnCompileLad();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	int Cols;
	int Rows;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LADDOC_H__EC306101_B09B_11D4_8B78_5254AB1F6EC3__INCLUDED_)
