// AreSet.cpp : implementation file
//

#include "stdafx.h"
#include "MUL.h"
#include "AreSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAreSet dialog


CAreSet::CAreSet(CWnd* pParent /*=NULL*/)
	: CDialog(CAreSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAreSet)
	m_nHigh = 0;
	m_nWidth = 0;
	//}}AFX_DATA_INIT
}


void CAreSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAreSet)
	DDX_Control(pDX, IDC_PAGEWIDTH, m_strPageWidth);
	DDX_Control(pDX, IDC_PAGEHIGH, m_strPageHigh);
	DDX_Text(pDX, IDC_WORKARE_HIGH, m_nHigh);
	DDV_MinMaxUInt(pDX, m_nHigh,MinHigh,MaxHigh );//5, 100);
	DDX_Text(pDX, IDC_WORKARE_WIDTH, m_nWidth);
	DDV_MinMaxUInt(pDX, m_nWidth, MinWidth,MaxWidth);//12, 16);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAreSet, CDialog)
	//{{AFX_MSG_MAP(CAreSet)
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAreSet message handlers

int CAreSet::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_nWidth=MinWidth;
	m_nHigh=MinHigh;
	return 0;
}

void CAreSet::InitData(UINT x1, UINT x2, UINT y1, UINT y2)
{
	MinWidth=x1;
	MaxWidth=x2;
	MinHigh=y1;
	MaxHigh=y2;
}

void CAreSet::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	CString str1,str2;
	str1.Format("(%d至%d之间)",MinWidth,MaxWidth);
	str2.Format("(%d至%d之间)",MinHigh,MaxHigh);
	m_strPageWidth.SetWindowText(str1);
	m_strPageHigh.SetWindowText(str2);
}
