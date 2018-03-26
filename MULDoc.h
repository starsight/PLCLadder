// MULDoc.h : interface of the CMULDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MULDOC_H__AF53504D_B01D_11D4_8B78_5254AB1F6EC3__INCLUDED_)
#define AFX_MULDOC_H__AF53504D_B01D_11D4_8B78_5254AB1F6EC3__INCLUDED_

#include "IOPOINT.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSyntax;

class CMULDoc : public CDocument
{
protected: // create from serialization only
	CMULDoc();
	DECLARE_DYNCREATE(CMULDoc)

// Attributes
public:
	CArray<POINTINFO,POINTINFO> Code_Array;
	CArray<CPoint,CPoint> seat;
	CStringArray Addr_Array;
	CStringArray Name_Array;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMULDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMULDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	CSyntax * err_dlg;
	void MakeUpHOR(int row,int col);
	int Compile(CString &errMessage);
	int preCompile(CString &errMessage);
	int FindPort(int i,CPoint &point1,CPoint &point2);
	void AddHOR(int row,int col,int count);
	PLC m_mPlc;
	void AddERECT(int row,int col);
	CPoint GetRowCol();
	int m_nCodecount;
	int m_nstep;
	int CodeToSeat();
	CPoint transfer();
	void ArrayInit();
	//{{AFX_MSG(CMULDoc)
	afx_msg void OnCompileInstr();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int Cols;
	int Rows;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULDOC_H__AF53504D_B01D_11D4_8B78_5254AB1F6EC3__INCLUDED_)
