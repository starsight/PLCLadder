// Syntax.cpp : implementation file
//

#include "stdafx.h"
#include "MUL.h"
#include "Syntax.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSyntax dialog


CSyntax::CSyntax(CString str,CWnd* pParent /*=NULL*/)
	: CDialog(CSyntax::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSyntax)
	m_strList = _T("");
	//}}AFX_DATA_INIT
	if (!this->Create(CSyntax::IDD,pParent))
		AfxMessageBox("不能建立编译对话框!");
	m_strList=str;
}


void CSyntax::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSyntax)
	DDX_Text(pDX, IDC_COMPILE, m_strList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSyntax, CDialog)
	//{{AFX_MSG_MAP(CSyntax)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSyntax message handlers

void CSyntax::Refresh(CString str)
{
	m_strList=str;
}
