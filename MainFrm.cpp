// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MUL.h"

#include "MainFrm.h"
#include "Splash.h"
#include "FindText.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_COMMUN_DOWNLOAD, OnCommunDownload)
	ON_COMMAND(ID_COMMUN_UPLOAD, OnCommunUpload)
	//}}AFX_MSG_MAP
	//ON_UPDATE_COMMAND_UI(ID_INDICATOR_MOUSE,OnUpdateMousePos)
	ON_COMMAND(ID_32814, &CMainFrame::On32814)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_MOUSE,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_bDownload = TRUE;
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndDrawTool.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndDrawTool.LoadToolBar(IDR_DRAWTYPE))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.SetWindowText("系统工具");
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	m_wndDrawTool.SetWindowText("绘图工具");
	m_wndDrawTool.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndDrawTool);
	// CG: The following line was added by the Splash Screen component.
	CSplashWnd::ShowSplashScreen(this);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

/*
void CMainFrame::OnUpdateMousePos(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}*/

void CMainFrame::SetMousePosText(CString strText)
{
	int nIndex=m_wndStatusBar.CommandToIndex(ID_INDICATOR_MOUSE);
	m_wndStatusBar.SetPaneText(nIndex,strText);
	CWindowDC dc(&m_wndStatusBar);
	CSize sizeText=dc.GetTextExtent(strText);
	m_wndStatusBar.SetPaneInfo(nIndex,ID_INDICATOR_MOUSE,SBPS_NORMAL,sizeText.cx);
}



void CMainFrame::OnCommunDownload() 
{
}

void CMainFrame::OnCommunUpload() 
{
}


void CMainFrame::On32814()
{
	// TODO: 在此添加命令处理程序代码
	// MessageBox("hello");

	CFindText aboutDlg;
	aboutDlg.DoModal();
}
