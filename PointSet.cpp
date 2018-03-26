// PointSet.cpp : implementation file
//

#include "stdafx.h"
#include "MUL.h"
#include "IOPOINT.h"
#include "PointSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPointSet dialog


CPointSet::CPointSet(IOPOINT *point,CWnd* pParent /*=NULL*/)
	: CDialog(CPointSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPointSet)
	m_strAddr = _T("");
	m_Caption = _T("");
	m_strName = _T("");
	m_strNote = _T("");
	//}}AFX_DATA_INIT
	m_pPoint=point;
	if (m_pPoint->getflag()==12)
	{
		m_nType=1;
		m_Caption="指令K：";
	}
	else if(m_pPoint->getflag()==13)
	{
		m_nType=2;
		m_Caption="指令F：";
	}
	else
	{
		m_nType=0;
		m_Caption="地 址：";
	}
	m_pPoint->getaddr(&m_strAddr);
	m_pPoint->getname(&m_strName);
}


void CPointSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPointSet)
	DDX_Text(pDX, IDC_ADDR, m_strAddr);
	DDV_MaxChars(pDX, m_strAddr, 4);
	DDX_Text(pDX, IDC_CAPTION, m_Caption);
	DDX_Text(pDX, IDC_NAME, m_strName);
	DDV_MaxChars(pDX, m_strName, 8);
	DDX_Text(pDX, IDC_NOTE, m_strNote);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPointSet, CDialog)
	//{{AFX_MSG_MAP(CPointSet)
	ON_EN_CHANGE(IDC_ADDR, OnChangeAddr)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPointSet message handlers

void CPointSet::OnChangeAddr() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	this->UpdateData(TRUE);
}

void CPointSet::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	delete (m_pPoint);
	CDialog::OnClose();
}

void CPointSet::OnOK() 
{
	// TODO: Add extra validation here
	if (m_pPoint!=NULL)
	{
		m_pPoint->setaddr(m_strAddr);		// 设置无件地址
		if (m_strAddr.GetLength()>0 && m_pPoint->testaddr())
		{
			if (m_nType)
				AfxMessageBox("指令错误！");
			else
				AfxMessageBox("地址错误！");
			GetDlgItem(IDC_ADDR)->SetFocus();
		}
		else
			CDialog::OnOK();
	}
}
