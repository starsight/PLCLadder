// MULView.h : interface of the CMULView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MULVIEW_H__AF53504F_B01D_11D4_8B78_5254AB1F6EC3__INCLUDED_)
#define AFX_MULVIEW_H__AF53504F_B01D_11D4_8B78_5254AB1F6EC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMULView : public CEditView
{
protected: // create from serialization only
	CMULView();
	DECLARE_DYNCREATE(CMULView)

// Attributes
public:
	CMULDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMULView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMULView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMULView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MULView.cpp
inline CMULDoc* CMULView::GetDocument()
   { return (CMULDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULVIEW_H__AF53504F_B01D_11D4_8B78_5254AB1F6EC3__INCLUDED_)
