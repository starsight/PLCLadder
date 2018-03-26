#if !defined(AFX_LADVIEW_H__EC306102_B09B_11D4_8B78_5254AB1F6EC3__INCLUDED_)
#define AFX_LADVIEW_H__EC306102_B09B_11D4_8B78_5254AB1F6EC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LADView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLADView view

class CLADView : public CScrollView
{
protected:
	CLADView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CLADView)

// Attributes
public:

// Operations
public:
	void OnInitialWorkare();
	void LINE(CPoint ptFrom,CPoint ptTo);
	BOOL sign;
    CPoint m_pTo;
	CPoint m_pFrom;
    CBitmap * m_pBitmap;
	CDC * m_pMemDc;
	CBitmap * m_pOldBitmap;
	CLADDoc* GetDocument();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLADView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
protected:	
	CPoint m_nPos;
	//int m_nCurSorHigh;
	//int m_nCurSorWidth;

	void UpdateWordType(CCmdUI *pCmdUI);
	void OnSelectWordType(UINT nID);
	void OnUpdateSelectDrawType(CCmdUI *pCmdUI);
	void OnSelectDrawType(UINT nID);
	virtual ~CLADView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CLADView)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnOptionWorkare();
	afx_msg void OnUpdateMousePos(CCmdUI *pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int CurrentCols;
	int CurrentRows;
	UINT m_nDrawType;
	UINT m_nWordType;
	int m_nAreWidth;
	int m_nAreHigh;
//	UINT MaxHigh;
//	UINT MaxWidth;
	UINT MinHigh;
	UINT MinWidth;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LADVIEW_H__EC306102_B09B_11D4_8B78_5254AB1F6EC3__INCLUDED_)
