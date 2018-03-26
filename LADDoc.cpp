// LADDoc.cpp : implementation file
//

#include "stdafx.h"
#include "MUL.h"
//#include "Iopoint.h"
#include "PointSet.h"
#include "Syntax.h"
#include "LADDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int CurH;
extern int CurW;
extern int MaxRows;
extern int MaxCols;
extern CString filename;
/////////////////////////////////////////////////////////////////////////////
// CLADDoc

IMPLEMENT_DYNCREATE(CLADDoc, CDocument)

CLADDoc::CLADDoc()
{
   err_dlg=NULL;
   OpenFlag=FALSE;
   Rows=0;
   Cols=0;
}

BOOL CLADDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	m_mPlc.newfile();
	DeletePoints();
	return TRUE;
}

CLADDoc::~CLADDoc()
{
	delete err_dlg;
	DeletePoints();
}


BEGIN_MESSAGE_MAP(CLADDoc, CDocument)
	//{{AFX_MSG_MAP(CLADDoc)
	ON_COMMAND(ID_COMPILE_LAD, OnCompileLad)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLADDoc diagnostics

#ifdef _DEBUG
void CLADDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLADDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLADDoc serialization

void CLADDoc::Serialize(CArchive& ar)
{
	CArchiveException fileexception;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		CIO *point;
		IOPOINT *temp;

		if (m_pointArray.GetSize()>0)
		{
			DeletePoints();
		}

		point=new CIO;
		point->name="";
		point->addr="";
		point->code="";
		point->Rows=Rows;
		point->Cols=Cols;
		point->flag=0;
		point->fiveflag=0;
		point->xpoint=0;
		point->ypoint=0;
		m_pointArray.Add(point);

		for (int i=0;i<Rows;i++)
		{
			for(int j=0;j<Cols;j++)
			{
				if (m_mPlc.point_array[i][j]!=NULL)
				{
					CString str;
					point=new CIO;
					temp=m_mPlc.point_array[i][j];
					temp->getname(&str);
					point->name=str;
					temp->getaddr(&str);
					point->addr=str;
					temp->getcode(&str);
					point->code=str;
					point->Rows=Rows;
					point->Cols=Cols;
					point->flag=temp->getflag();
					point->fiveflag=temp->getfiveflag();
					point->xpoint=temp->getxpoint();
					point->ypoint=temp->getypoint();
					m_pointArray.Add(point);
				}
			}
		}
		m_pointArray.Serialize(ar);
		this->SetModifiedFlag(FALSE);
	}
	else
	{
		// TODO: add loading code here
		BOOL flag;
		IOPOINT *p;
		CIO * io;
		m_pointArray.Serialize(ar);

		//第一个是CIO所以从1开始
		for (int n=1;n<m_pointArray.GetSize();n++)
		{
			io=(CIO*)m_pointArray.GetAt(n);
			flag=TRUE;
			switch (io->flag)
			{
			case 0:
					if (io->fiveflag==5)
					{
						p=new ERECT;
						p->setfiveflag(5);
					}
					else
						flag=FALSE;
					break;
			case 1:
					p=new LD;
					break;
			case 2:
					p=new LDI;
					break;
			case 3:
					p=new OR;
					break;
			case 4:
					p=new ORI;
					break;
			case 6:
					p=new HOR;
					break;
			case 7:
					p=new OUTPOINT;
					break;
			default:
					p=new ADDTION;
					break;
			}
			if (flag)
			{
				p->setname(io->name);
				p->setaddr(io->addr);
				p->setcode(io->code);
				p->setflag(io->flag);
				p->setwhere(io->xpoint,io->ypoint);
				m_mPlc.insert_point(p);
				if (io->flag!=0 && io->fiveflag==5)
				{
					p=new ERECT;
					p->setfiveflag(5);
					p->setwhere(io->xpoint,io->ypoint);
					m_mPlc.insert_point(p);
				}
			}
		}
		io=(CIO*)m_pointArray.GetAt(0);
		SetRowCol(io->Rows,io->Cols);
		OpenFlag=TRUE;
	}
	
}

/////////////////////////////////////////////////////////////////////////////
// CLADDoc commands

void CLADDoc::erase_point(int x, int y, CDC *pDC)
{
	CBrush brush;
	brush.CreateStockObject(WHITE_BRUSH);
	CRect rect(x+1,y,x+::CurW,y+CurH+1);
    pDC->FillRect(rect,&brush);

    CPen pen;
	CPen *pOldPen;
	pen.CreateStockObject(WHITE_PEN);
	pOldPen=pDC->SelectObject(&pen);
	pDC->MoveTo(x+::CurW,y-9);
    pDC->LineTo(x+::CurW,y+::CurH-10); 
	pDC->SelectObject(pOldPen);
  
	pDC->SetPixel(x+::CurW,y+::CurH-10,RGB(0,0,0));

	
	if(x>=::CurW*(Cols-1)+50)
	{ 
		pDC->MoveTo(x+::CurW,y-9);
        pDC->LineTo(x+::CurW,y+::CurH);
	}  
	this->SetModifiedFlag();
}

void CLADDoc::insert_point(UINT pID, int x, int y, int row, int col, CDC *pDC)
{
   	int		insertflag;
	int		eraseflag;
	IOPOINT *point;

	eraseflag	= 1;
	insertflag	= 1;
	switch(pID)
	{
		case 1:
			point=new LD;
		    point->setflag(1);
		    point->setcode("LD");
		    break;
		case 2:
		    point=new LDI;
		    point->setflag(2);
		    point->setcode("LDI");
		    break;
		case 3:
			if (row>0)
			{
				point=new OR;
				point->setflag(3);
				point->setcode("OR");
			}
			else
				insertflag=0;
		    break;
	    case 4:
			if (row>0)
			{
				point=new ORI;
				point->setflag(4);
				point->setcode("ORI");
			}
			else
				insertflag=0;
		    break;
        case 51:
			eraseflag=0;
			point=new  ERECT;
		    point->setfiveflag(5);
		    point->setcode("ERECT");
		    break;
        case 52:						// HOR 为空（直连关系）
   	        point=new HOR;
			point->setflag(6);
			point->setcode("HOR");			
			break;    
	    case 6:							// OUT 指令
		    point=new OUTPOINT;				
		    point->setflag(7);
		    point->setcode("OUT");
		    break;
        case 7:
		    point=new ADDTION;
		    point->setflag(100);
		    break;
    }
    if (m_mPlc.point_array[row][col]!=NULL && eraseflag)
	{
		erase_point(x,y,pDC);
	}
	if (insertflag)
	{
		try{
			point->setwhere(row,col);
			m_mPlc.insert_point(point);
			m_mPlc.point_array[row][col]->print(x,y,pDC);	
			if (pID==3|| pID==4)
			{
				point=new ERECT;
				point->setfiveflag(5);
				point->setwhere(row,col);
				m_mPlc.insert_point(point);
				if (col>0)
				{
					point=new ERECT;
					point->setfiveflag(5);
					point->setwhere(row,col-1);
					m_mPlc.insert_point(point);
				}
			}
		}
		catch(...)
		{
			POSITION pos=this->GetFirstViewPosition();
			CView * pView=this->GetNextView(pos);
			pView->MessageBox("可能梯形图绘制有错、或元器件设置错误\n\n请将文件保存关闭后重新打开能解决问题。\n\n若仍存在问题，请与开发商联系。","绘制出错",MB_ICONERROR|MB_OK);
		}
	}
	this->SetModifiedFlag();
}


/*
	 菜单编译 —— 生成指令
*/
void CLADDoc::OnCompileLad() 
{
	// TODO: Add your command handler code here
	CString pathname=this->GetPathName();			//  获取文件路径
	if (pathname=="")		
	{
		AfxMessageBox("请先保存文件，再进行编译！");
		return ;
	}
	this->OnSaveDocument(pathname);					// 保存文档
	::filename=pathname+this->GetTitle();
	int i=::filename.Find('.');
	if (i!=-1)
		::filename=::filename.Mid(0,i);
	::filename+=".plc";								// 保存为PLC后缀
	CString str;	
	try{
		if (!m_mPlc.compiled(str))
			str.Format("编译成功!");
		if (err_dlg)
		{
			err_dlg->Refresh(str);
			err_dlg->ShowWindow(SW_RESTORE);
		}
		else
		{
			err_dlg=new CSyntax(str,AfxGetMainWnd());
			err_dlg->CenterWindow();
			err_dlg->ShowWindow(SW_SHOW);
		}
		
		err_dlg->UpdateData(FALSE);
	}
	catch(...)
	{
		POSITION pos=this->GetFirstViewPosition();
		CView * pView=this->GetNextView(pos);
		pView->MessageBox("可能梯形图绘制有错、\n或文件不能建立","编译出错",MB_ICONERROR|MB_OK);
	}
}

void CLADDoc::SetAddition(int row, int col, int flag, CString str)
{
	m_mPlc.point_array[row][col]->setflag(flag);
	m_mPlc.point_array[row][col]->setcode(str);
}


int CLADDoc::TestPointType(int row, int col)
{
    int result;
	IOPOINT *point;
	point=m_mPlc.point_array[row][col];
	if (point==NULL)
		result=0;
	else if(point->getflag()>=8)
		result=2;
		else result=1;
	return result;
}

void CLADDoc::Process(UINT pID, int x, int y, CDC *pDC)
{
	int row,col;
	row=y/::CurH;
	col=(x-50)/::CurW;
    if (pID==8)
	{
		if (m_mPlc.point_array[row][col]!=NULL)
		{
			try{
				erase_point(x,y,pDC);
				m_mPlc.remove_point(row,col);
			}
			catch(...)
			{
				POSITION pos=this->GetFirstViewPosition();
				CView * pView=this->GetNextView(pos);
				pView->MessageBox("擦除错误！可能梯形图绘制有错\n\n请将文件保存关闭后重新打开能解决问题。\n\n若仍存在问题，请与开发商联系。","擦除出错",MB_ICONERROR|MB_OK);
			}
			return;
		}
	}	
/*	if (pID>0 && pID<8)  */
	else 
	{
		if (pID==6 || pID==7)
		{
			for (int i=col;i<Cols-1;i++)
			{
				insert_point(52,x,y,row,i,pDC);
				x+=::CurW;
			}
			col=Cols-1;
		}
		insert_point(pID,x,y,row,col,pDC);
	}
}

void CLADDoc::ReDraw(int x, int y,CDC *pDC)
{
    int row,col;
	row=y/::CurH;
	col=(x-50)/::CurW;
	x=col*::CurW+50;
	y=row*::CurH;
	if (m_mPlc.point_array[row][col]!=NULL && m_mPlc.point_array[row][col]->getflag()!=6)
	{
		CPointSet dlg_PointSet(m_mPlc.point_array[row][col]);
		
		if (dlg_PointSet.DoModal()==IDOK)
		{
			int flag;
			flag=m_mPlc.point_array[row][col]->getflag();
			if (flag==12 || flag==13)
			{
				if (dlg_PointSet.m_strAddr.GetLength()!=0)
					m_mPlc.point_array[row][col]->setcode(dlg_PointSet.m_strAddr);
				m_mPlc.point_array[row][col]->setaddr("");
			}
			else
				m_mPlc.point_array[row][col]->setaddr(dlg_PointSet.m_strAddr);
			m_mPlc.point_array[row][col]->setname(dlg_PointSet.m_strName);
			erase_point(x,y,pDC);
			m_mPlc.point_array[row][col]->print(x,y,pDC);
		}
	}
}

void CLADDoc::UpdateWorkare(CDC *pDC)
{
	int startx;
	int starty;
	int i;
	for (i=0;i<Rows;i++)
	{
		int j;
		for (j=0;j<Cols;j++)
		{
			if (m_mPlc.point_array[i][j]!=NULL)
			{
				startx=j*::CurW+50;
				starty=i*::CurH;
				m_mPlc.point_array[i][j]->print(startx,starty,pDC);
			}
		}
		for (;j<::MaxCols;j++)
		{
			if (m_mPlc.point_array[i][j]!=NULL)
				m_mPlc.remove_point(i,j);
		}
	}
	for (;i<::MaxRows;i++)
		for (int n=0;n<::MaxCols;n++)
		{
			if (m_mPlc.point_array[i][n]!=NULL)
				m_mPlc.remove_point(i,n);
		}
}

void CLADDoc::SetRowCol(int row, int col)
{
	Rows=row;
	Cols=col;
	m_mPlc.SetRowCol(row,col);
}

void CLADDoc::DeletePoints()
{
	for (int i=0;i<m_pointArray.GetSize();i++)
	{
		delete m_pointArray.GetAt(i);
	}
	m_pointArray.RemoveAll();
}


