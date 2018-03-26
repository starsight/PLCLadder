// LADView.cpp : implementation file
//

#include "stdafx.h"
#include "MUL.h"
#include "LADDoc.h"
#include "LADView.h"
#include "AreSet.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//extern int CurrentCols;
//extern int CurrentRows;
extern int MaxRows;
extern int MaxCols;
extern int CurH;
extern int CurW;
/////////////////////////////////////////////////////////////////////////////
// CLADView

IMPLEMENT_DYNCREATE(CLADView, CScrollView)

CLADView::CLADView()
{
	m_pMemDc=new CDC;
	m_pBitmap=new CBitmap;
	OnSelectDrawType(ID_DRAW_FREE);
}

CLADView::~CLADView()
{
}


BEGIN_MESSAGE_MAP(CLADView, CScrollView)
	//{{AFX_MSG_MAP(CLADView)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_OPTION_WORKARE, OnOptionWorkare)
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_MOUSE,OnUpdateMousePos)
	ON_COMMAND_RANGE(ID_DRAW_FREE,ID_DRAW_ERASE,OnSelectDrawType)
	ON_UPDATE_COMMAND_UI_RANGE(ID_DRAW_FREE,ID_DRAW_ERASE,OnUpdateSelectDrawType)
	ON_COMMAND_RANGE(ID_SELECT_SET,ID_SELECT_END,OnSelectWordType)
	ON_UPDATE_COMMAND_UI_RANGE(ID_SELECT_SET,ID_SELECT_END,UpdateWordType)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLADView drawing

void CLADView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CLADDoc*pDoc=GetDocument();
	ASSERT(pDoc);

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	
	sign=FALSE;

	if (pDoc->OpenFlag)
	{
		MinWidth=pDoc->Cols;
		MinHigh=pDoc->Rows;
	}
	else
	{
		MinWidth=(GetSystemMetrics(SM_CXSCREEN)-57)/::CurW;
		MinHigh=GetSystemMetrics(SM_CYSCREEN)/::CurH;
	}
	if (MinWidth>(UINT)::MaxCols)
		MinWidth=::MaxCols;
 	
	CurrentCols=MinWidth;
	CurrentRows=MinHigh;
	pDoc->SetRowCol(CurrentRows,CurrentCols);

	m_nAreHigh=::CurH*MinHigh;
	m_nAreWidth=::CurW*MinWidth+50;
	//m_nCols=m_nAreWidth;
	sizeTotal.cx = m_nAreWidth+7;
	sizeTotal.cy =m_nAreHigh;
	SetScrollSizes(MM_TEXT, sizeTotal,CSize(600,400),CSize(60,80));
	
	CDC *pDC=GetDC();
	m_pMemDc->CreateCompatibleDC(pDC);
	m_pBitmap->CreateCompatibleBitmap(pDC,
		::MaxCols*::CurW+51,
		::MaxRows*::CurH);
	m_pOldBitmap=m_pMemDc->SelectObject(m_pBitmap);
	CFont myFont;
	myFont.CreateFont(12,
					  0,
					  0,
					  0,
					  FW_NORMAL,
					  FALSE,
					  FALSE,
					  FALSE,
					  GB2312_CHARSET,
					  OUT_DEFAULT_PRECIS,
					  CLIP_DEFAULT_PRECIS,
					  DEFAULT_QUALITY,
					  DEFAULT_PITCH|FF_MODERN,
					  "宋体");
	m_pMemDc->SelectObject(&myFont);
	m_pMemDc->SetTextColor(RGB(0,0,0));
	CPen drawpen;
	drawpen.CreateStockObject(BLACK_PEN);
	m_pMemDc->SelectObject(&drawpen);
	ReleaseDC(pDC);

	OnInitialWorkare();

	if (pDoc->OpenFlag)
		pDoc->UpdateWorkare(m_pMemDc);
}
void CLADView::OnDraw(CDC* pDC)
{
	CLADDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	CRect workare;
	this->GetClientRect(&workare);
	CPoint workare_start=this->GetScrollPosition();
	pDC->BitBlt(workare_start.x,workare_start.y,
		workare.BottomRight().x,workare.BottomRight().y,
		m_pMemDc,workare_start.x,workare_start.y,SRCCOPY);
}

/////////////////////////////////////////////////////////////////////////////
// CLADView diagnostics

#ifdef _DEBUG
void CLADView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CLADView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLADView message handlers

CLADDoc* CLADView::GetDocument()
{
	return (CLADDoc*)m_pDocument;
}

void CLADView::OnUpdateMousePos(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CLADView::LINE(CPoint ptFrom, CPoint ptTo)
{
    CLADDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int x1,y1,m,i;
	if (ptFrom.x==ptTo.x)
	{
		x1=ptFrom.x-::CurW;
		if (x1>=50)
		{
			if (ptFrom.y>ptTo.y)
				y1=ptTo.y;
			else
				y1=ptFrom.y;
			y1+=10;
			m=(abs(ptFrom.y-ptTo.y))/::CurH;
			for(i=0;i<m;i++)
			{
				pDoc->Process(51,x1,y1,m_pMemDc);
				y1+=::CurH;
			}
		}
	}
	if (ptFrom.y==ptTo.y)
	{
		y1=ptFrom.y-70;
		if (ptFrom.x>ptTo.x)
			x1=ptTo.x;
		else
			x1=ptFrom.x;
		m=(abs(ptFrom.x-ptTo.x))/::CurW;
		for(i=0;i<m;i++)
		{
			pDoc->Process(52,x1,y1,m_pMemDc);
			x1+=::CurW;
		}
	}
	this->Invalidate(FALSE);
}


void CLADView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CScrollView::OnBeginPrinting(pDC, pInfo);
}

void CLADView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CScrollView::OnEndPrinting(pDC, pInfo);
}

BOOL CLADView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	// TODO: call DoPreparePrinting to invoke the Print dialog box
	
	return CScrollView::DoPreparePrinting(pInfo);
}

void CLADView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CLADDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);	
	CPoint drawseat;
	drawseat=this->GetScrollPosition();
	drawseat.x+=point.x;
	if (drawseat.x>50 && m_nDrawType==0)
	{
		drawseat.y+=point.y;
		pDoc->ReDraw(drawseat.x,drawseat.y,
			m_pMemDc);
		this->Invalidate(FALSE);
	}
	CScrollView::OnLButtonDblClk(nFlags, point);
}

void CLADView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CLADDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	SetCapture();
	
	if (point.x>50 && point.x<m_nAreWidth && m_nDrawType>0)
	{
		CPoint drawseat;
		drawseat=this->GetScrollPosition();
		drawseat+=point;
        drawseat.x=((drawseat.x-50)/::CurW)*::CurW+50;
		drawseat.y=(drawseat.y/::CurH)*::CurH;
		m_pFrom=drawseat;
		if (m_nDrawType==5)
		{
			sign=TRUE;
			m_pFrom=drawseat;
			m_pFrom.y+=70;
			m_pTo=m_pFrom;
		}
		else
		{
	   	pDoc->Process(m_nDrawType,drawseat.x,drawseat.y,
			m_pMemDc);
		this->Invalidate(FALSE);
		}

		CScrollView::OnLButtonDown(nFlags, point);
	}
}

void CLADView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_nDrawType==5)
	{
		CPoint drawseat;
		sign=FALSE;
		drawseat=this->GetScrollPosition();
		drawseat+=point;
		if (point.x<=50)
			drawseat.x=drawseat.x-point.x+50;
		m_pTo.x=((drawseat.x-50)/::CurW)*::CurW+50;
		m_pTo.y=(drawseat.y/::CurH)*::CurH+70;
        if(abs(m_pFrom.x-drawseat.x)<abs(m_pFrom.y-drawseat.y))
        {
	      m_pTo.x=m_pFrom.x;
		}
	    else
        {
	      m_pTo.y=m_pFrom.y;
		}
		if (m_pFrom!=m_pTo)
			LINE(m_pFrom,m_pTo);
          
    }
	ReleaseCapture();
	CScrollView::OnLButtonUp(nFlags, point);
}

void CLADView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CPoint m_endpoint;
    CPoint pos;
	CPoint rcClient;
	pos=GetScrollPosition();
	rcClient=pos+point;
	if (point.x>50)
	{
		CString strMousePosition;
		m_nPos.x=(rcClient.x-50)/::CurW+1;
		m_nPos.y=rcClient.y/::CurH+1;
		strMousePosition.Format(" Ln %d,Col %d",
			m_nPos.y,m_nPos.x);
		CMainFrame *pMainFrame=(CMainFrame*)AfxGetMainWnd();
		pMainFrame->SetMousePosText(strMousePosition);
	}
	else
		rcClient.x=rcClient.x-point.x+50;
	
	if (m_nDrawType==5 && sign)
	{
		CDC *pDC;
		pDC=this->GetDC();
		CRect rect(m_pFrom,m_pTo);	
		rect.NormalizeRect();
		rect.InflateRect(1,1);
        CPoint temp1;
		temp1.x=rect.left-pos.x;
		temp1.y=rect.top-pos.y;
		pDC->BitBlt(temp1.x,temp1.y,rect.Width(),rect.Height(),
		    m_pMemDc,rect.left,rect.top,SRCCOPY);
		m_endpoint.x=((rcClient.x-50)/::CurW)*::CurW+50;
		m_endpoint.y=(rcClient.y/::CurH)*::CurH+70;
		if(abs(m_pFrom.x-rcClient.x)<abs(m_pFrom.y-rcClient.y))
			m_endpoint.x=m_pFrom.x;
		else
			m_endpoint.y=m_pFrom.y;
		temp1=m_pFrom-pos;
		CPoint temp2=m_endpoint-pos;
		pDC->MoveTo(temp1);
		pDC->LineTo(temp2);
		m_pTo=m_endpoint;
		ReleaseDC(pDC); 
	}
      
	CScrollView::OnMouseMove(nFlags, point);
}

BOOL CLADView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	switch(m_nDrawType)
	{
	case 1:
		::SetCursor(AfxGetApp()->LoadCursor(IDC_LD));
		break;
	case 2:
		::SetCursor(AfxGetApp()->LoadCursor(IDC_LDI));
		break;
	case 3:
		::SetCursor(AfxGetApp()->LoadCursor(IDC_OR));
		break;
	case 4:
		::SetCursor(AfxGetApp()->LoadCursor(IDC_ORI));
		break;
	case 5:
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
		break;
	case 6:
		::SetCursor(AfxGetApp()->LoadCursor(IDC_OUT));
		break;
	case 7:
		::SetCursor(AfxGetApp()->LoadCursor(IDC_ADDITION));
		break;
	default:
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
		break;
	}
	return TRUE;
	//return CScrollView::OnSetCursor(pWnd, nHitTest, message);
}

void CLADView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
		CRect rect;
	AfxGetMainWnd()->GetWindowRect(&rect);
	rect.left=point.x-rect.left;
	if( rect.left>50)//m_nDrawType==7 &&
    {	
		CLADDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		int row,col;
		row=m_nPos.y-1;
		col=m_nPos.x-1;
	    int pointype;
		pointype=pDoc->TestPointType(row,col);
		if (pointype==2)
		{
			CMenu menu;
			menu.LoadMenu(IDR_ITEMMENU);
			CMenu *pContexMenu=menu.GetSubMenu(0);
			pContexMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON,
			point.x,point.y,AfxGetMainWnd());
		}
	}
}

void CLADView::OnOptionWorkare() 
{
	// TODO: Add your command handler code here
	CLADDoc* pDoc=GetDocument();
	ASSERT(pDoc);
	CAreSet dlgAreSet(this);
	MinWidth=(GetSystemMetrics(SM_CXSCREEN)-57)/::CurW;
	if (MinWidth>(UINT)::MaxCols)
		MinWidth=::MaxCols;
	MinHigh=GetSystemMetrics(SM_CYSCREEN)/::CurH;
	dlgAreSet.InitData(MinWidth,(UINT)::MaxCols,MinHigh,(UINT)::MaxRows);
	int nRetCode=dlgAreSet.DoModal();
	if (nRetCode==IDOK)
	{
		CWaitCursor wait;
		m_nAreHigh=dlgAreSet.m_nHigh ;
		CurrentRows=m_nAreHigh;
		m_nAreWidth=dlgAreSet.m_nWidth;
		CurrentCols=m_nAreWidth;
		m_nAreHigh*=::CurH;
		m_nAreWidth*=::CurW;
		m_nAreWidth+=50;
		CSize sizeTotal;
		sizeTotal.cx = m_nAreWidth+7;
		sizeTotal.cy =m_nAreHigh;
		SetScrollSizes(MM_TEXT, sizeTotal,CSize(600,400),CSize(60,80));
		OnInitialWorkare();
		pDoc->SetRowCol(CurrentRows,CurrentCols);
		pDoc->UpdateWorkare(m_pMemDc);
	}
}

BOOL CLADView::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	AfxGetApp()->BeginWaitCursor();
	return CScrollView::PreCreateWindow(cs);
}

void CLADView::OnInitialWorkare()
{
	CWaitCursor wait;
  	CBrush brush;
	brush.CreateStockObject(WHITE_BRUSH);
	CRect m_cWorkare(-1,-1,::MaxCols*::CurW+50,
		::MaxRows*::CurH);//MaxWidth,MaxHigh);
	m_pMemDc->FillRect(m_cWorkare,&brush);

	m_pMemDc->MoveTo(50,0);
	m_pMemDc->LineTo(50,m_nAreHigh);
	m_pMemDc->MoveTo(m_nAreWidth,m_nAreHigh);
	m_pMemDc->LineTo(m_nAreWidth,0);
	
	for (int i=::CurW+50;i<m_nAreWidth;i+=::CurW)
		for (int j=::CurH;j<m_nAreHigh;j+=::CurH)
			m_pMemDc->SetPixel(i,j-10,1);
	Invalidate(FALSE);
}

void CLADView::OnSelectDrawType(UINT nID)
{
	ASSERT(nID>=ID_DRAW_FREE && nID<=ID_DRAW_ERASE);
	m_nDrawType=nID-ID_DRAW_FREE;

}

void CLADView::OnUpdateSelectDrawType(CCmdUI *pCmdUI)
{

	UINT nID=pCmdUI->m_nID-ID_DRAW_FREE;
	if (nID==m_nDrawType)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CLADView::OnSelectWordType(UINT nID)
{
    ASSERT(nID>=ID_SELECT_SET && nID<=ID_SELECT_END);
	m_nWordType=nID-ID_SELECT_SET;
	CLADDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc); 
    int row,col;
	CString str;
	int flag;
	row=m_nPos.y-1;
	col=m_nPos.x-1;
	switch(m_nWordType)
	{
	case 0:
		flag=8;
		str="SET";
		break;
	case 1:
		flag=18;
		str="RST";
		break;
	case  2:
		flag=9;
		str="S";
		break;
	case  3:
		flag=19;
		str="R";
		break;
	case  4:
		flag=10;
		str="MC";
	    break;
	case  5:
		flag=11;
		str="MCR";
		break;
	case  6:
		flag=12;
		str="K";
		break;
	case  7:
		flag=13;
		str="F";
		break;
	case  10:
		flag=14;
		str="PLS";
		break;
	case  11:
		flag=15;
		str="END";
		break;
	case  8:
	case  9:
		flag=100;
		str="";
		break;
	}
	pDoc->SetAddition(row,col,flag,str);
	CPoint point;
	point.x=col*::CurW+80;
	point.y=row*::CurH+76;
	CBrush  brush;
	CBrush  *pOldBrush=NULL; 
	brush.CreateStockObject(WHITE_BRUSH);
	pOldBrush=m_pMemDc->SelectObject(&brush);
	CRect rect(point.x-13,point.y-11,point.x+12,point.y);
	m_pMemDc->FillRect(rect,&brush);
	m_pMemDc->SelectObject(pOldBrush);
	m_pMemDc->TextOut(point.x,point.y,str);
	this->Invalidate(FALSE);
	
}

void CLADView::UpdateWordType(CCmdUI *pCmdUI)
{
	UINT nID1=pCmdUI->m_nID-ID_SELECT_SET;
	if (nID1==m_nWordType)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);  
}

void CLADView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class
	AfxGetApp()->EndWaitCursor();
	CScrollView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CLADView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	int nWidth;
	int nHeight;
	
	//pDC->SetMapMode(MM_LOMETRIC);
	CRect m_rcPrintRect;
	
	if (pInfo) m_rcPrintRect=pInfo->m_rectDraw;

	double dWidthRatio=(double)m_rcPrintRect.Height()/
						(double)m_rcPrintRect.Width();
	
	nWidth=m_nAreWidth+7;//MaxWidth*m_nCurSorWidth+57
	nHeight=(int)(nWidth*dWidthRatio);
	
	int result=pDC->StretchBlt(m_rcPrintRect.TopLeft().x,m_rcPrintRect.TopLeft().y,
		m_rcPrintRect.Width(),m_rcPrintRect.Height(),m_pMemDc,0,0,nWidth,
		nHeight,SRCCOPY);
	//CScrollView::OnPrint(pDC, pInfo);
}
