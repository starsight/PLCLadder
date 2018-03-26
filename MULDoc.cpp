// MULDoc.cpp : implementation of the CMULDoc class
//

#include "stdafx.h"
#include "MUL.h"
#include "Syntax.h"
#include "MULDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern int MaxRows;
extern int MaxCols;
/////////////////////////////////////////////////////////////////////////////
// CMULDoc

IMPLEMENT_DYNCREATE(CMULDoc, CDocument)

BEGIN_MESSAGE_MAP(CMULDoc, CDocument)
	//{{AFX_MSG_MAP(CMULDoc)
	ON_COMMAND(ID_COMPILE_INSTR, OnCompileInstr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMULDoc construction/destruction

CMULDoc::CMULDoc()
{
	// TODO: add one-time construction code here
	err_dlg=NULL;
	Rows=0;
	Cols=0;
}

CMULDoc::~CMULDoc()
{
	Code_Array.RemoveAll();
	Addr_Array.RemoveAll();
	Name_Array.RemoveAll();
}

BOOL CMULDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMULDoc serialization

void CMULDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CMULDoc diagnostics

#ifdef _DEBUG
void CMULDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMULDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMULDoc commands

void CMULDoc::ArrayInit()
{
	Code_Array.RemoveAll();
	Addr_Array.RemoveAll();
	Name_Array.RemoveAll();
}


CPoint CMULDoc::transfer()
{
	int x,y;
	int maxx,maxy;
	int start;
	int j;
	POINTINFO temp;
	CPoint result;
	CPoint value;

	x=0;
	y=0;
	maxx=0;
	maxy=0;
	
	seat.SetAt(m_nstep,CPoint(y,x));
	m_nstep++;
	while (m_nstep<m_nCodecount)
	{
		temp=Code_Array.GetAt(m_nstep);
		switch(temp.code)
		{
		case 0:
			seat.SetAt(m_nstep,CPoint(-3,-3));
			m_nstep++;
			return (CPoint(y,maxy));
		case 1:
		case 2:
			start=m_nstep;
			result=transfer();
			if (m_nstep>=m_nCodecount)
				return (CPoint(y,maxy));
			if (Code_Array.GetAt(m_nstep).code==7) 
			{
				maxx++;
				for (j=start;j<m_nstep;j++)
				{
					value=seat.GetAt(j);
					if (value.y!=-1 && value.y!=-2)
					{
						value.y+=maxx;
						value.x+=y;
						seat.SetAt(j,value);
					}
				}
				maxx+=result.x;
				if (maxy<result.y)
					maxy=result.y;
			}
			if (Code_Array.GetAt(m_nstep).code==8)
			{
				maxy++;
				for (j=start;j<m_nstep;j++)
				{
					value=seat.GetAt(j);
					if (value.x!=-1 && value.x!=-2)
					{
						value.x+=maxy;
						seat.SetAt(j,value);
					}
				}
				maxy+=result.y;
				if (maxx<result.x)
					maxx=result.x;
			}
			break;
		case 3:
		case 4:
			maxy++;
			seat.SetAt(m_nstep,CPoint(maxy,x));
			break;
		case 5:
		case 6:
			maxx++;
			seat.SetAt(m_nstep,CPoint(y,maxx));
			break;
		case 7:
			seat.SetAt(m_nstep,CPoint(-1,-1));
			return(CPoint(maxx,maxy));
		case 8:
			seat.SetAt(m_nstep,CPoint(-2,-2));
			return(CPoint(maxx,maxy));
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
		case 21:
			seat.SetAt(m_nstep,CPoint(y,maxx+1));
			y++;
			break;
		default:
			break;
		}
		m_nstep++;
	}
	return (CPoint(y,maxy));
}

int CMULDoc::CodeToSeat()
{
	CString str;
	int errflag;
	int j;
	seat.RemoveAll();
	m_nCodecount=Code_Array.GetSize();
	for (j=0;j<m_nCodecount;j++)
		seat.Add(CPoint(0,0));

	errflag=0;
	try{

		CPoint result;
		CPoint temp;
		m_nstep=0;
		int row=0;
		int startpoint;
		while (m_nstep<m_nCodecount)
		{
			startpoint=m_nstep;
			result=transfer();
			for (int j=startpoint;j<m_nstep;j++)
			{
				temp=seat.GetAt(j);
				if (temp.x!=-1 && temp.x!=-2 && temp.x!=-3)
				temp.x+=row;
				seat.SetAt(j,temp);
			}
			if (result.x>result.y)
				row+=result.x;
			else
				row+=result.y+1;
		}
	}
	catch(...)
	{
		errflag=1;
		POSITION pos=this->GetFirstViewPosition();
		CView * pView=this->GetNextView(pos);
		pView->MessageBox("将指令转换成结点地址时出错！请与开发商联系。",
			"编译出错",MB_ICONERROR|MB_OK);
	}
/*	for (j=0;j<m_nCodecount;j++)
	{
		CPoint point;
		point=seat.GetAt(j);
		str.Format("row=%d\ncol=%d",point.x,point.y);
		AfxMessageBox(str);
	}*/
	return errflag;
}

CPoint CMULDoc::GetRowCol()
{
	int rows;
	int cols;
	CPoint temp;
	rows=10;
	cols=12;
	for (int i=0;i<seat.GetSize();i++)
	{
		temp=seat.GetAt(i);
		if (temp.x+1>rows)
			rows=temp.x+1;
		if (temp.y+1>cols)
			cols=temp.y+1;
	}
	return (CPoint(rows,cols));
}

void CMULDoc::AddERECT(int row, int col)
{
	IOPOINT *point;
	do
	{
		point=new ERECT;
		point->setfiveflag(5);
		point->setcode("ERECT");
		point->setwhere(row,col);
		m_mPlc.insert_point(point);
		row--;
	}while(row>0 && (!m_mPlc.testpoint(row,col) 
		|| (m_mPlc.testpoint(row,col) 
		&& m_mPlc.getpoint(row,col)->getflag()==0
		&& m_mPlc.getpoint(row,col)->getfiveflag()!=5)));
}

void CMULDoc::AddHOR(int row, int col, int count)
{
	IOPOINT *point;
	for (int i=0;i<count;i++)
	{
		point=new HOR;
		point->setflag(6);
		point->setcode("HOR");
		point->setwhere(row,col+i);
		m_mPlc.insert_point(point);
	}
}

int CMULDoc::FindPort(int i,CPoint &point1, CPoint &point2)
{
	int count;
	POINTINFO temp;
	CPoint point_temp;
	count=0;
	point2=CPoint(0,0);
	while (count!=1)
	{
		temp=Code_Array.GetAt(i);
		if (temp.code==7 || temp.code==8)
			count--;
		else
		{
			point_temp=seat.GetAt(i);
			if (point_temp.y>point2.y)
				point2=point_temp;
		}
		if (temp.code==1 || temp.code==2)
			count++;
		i--;
	}
	point1=seat.GetAt(++i);
	return i;
}

int CMULDoc::preCompile(CString &errMessage)
{
	CString CodeSet[20]={
		";***","LD","LDI","OR","ORI","AND","ANI","ANB","ORB","OUT",
		"SET","RST","S","R","MC","MCR","CJP","EJP","PLS","END"};

	char  line[255];
	CString code;
	CString addr;
	CString name;
	FILE  *stream;
	CString fname;
	int result;

	ArrayInit();
	result=0;

	fname=this->GetPathName();
	if( (stream = fopen( fname, "r" )) != NULL )  
	{
		POINTINFO Info_Temp;
		BOOL HaveFlag;
		BOOL errFlag;
		CString errmsg;
		int count=1;
		int lcount=0;
		int bcount=0;
		int dcount=0;
		int i;

		while( fgets( line, 250, stream ) != NULL)         
		{
			HaveFlag=TRUE;
			errFlag=FALSE;

			code.GetBuffer(255);
			addr.GetBuffer(255);
			name.GetBuffer(255);

			sscanf(line,"%s %s %s",code,addr,name);

			code.ReleaseBuffer(4);
			addr.ReleaseBuffer(4);
			name.ReleaseBuffer(9);
 
			if (code!="")
			{
				code.MakeUpper();
				for (i=0;i<20;i++)
				{
					if (code==CodeSet[i]) 
					{
						Info_Temp.code=i;
						if (i==1 || i==2)
							lcount++;
						if (i==7 || i==8)
							bcount++;
						if (i==0)
						{	
							dcount++;

							if (!(lcount==0 && bcount==0) && lcount!=bcount+1)
							{
								result=1;
								errmsg.Format("第 %d 程序段LD，ANB不匹配!",dcount);
								errMessage+=errmsg;
							}
							lcount=0;
							bcount=0;
						}
						break;
					}
				}
				if (i==20)
				{
					if (code.GetAt(0)=='K')
						Info_Temp.code=20;
					else if (code.GetAt(0)=='F')
						Info_Temp.code=21;
					else if (code.GetAt(0)!=';')
					{
						HaveFlag=FALSE;
						errFlag=TRUE;
					}
					else 
						HaveFlag=FALSE;
				}
				if (HaveFlag)
				{
					if (name!="")
					{
						name=name.Right(name.GetLength()-1);
						name.TrimRight();
					}
					if (name!="")
						Info_Temp.name=Name_Array.Add(name);
					else
						Info_Temp.name=-1;					
					if (Info_Temp.code==20 || Info_Temp.code==21)
						Info_Temp.addr=Addr_Array.Add(code);
					else if (addr.GetAt(0)!=';' && addr!="")
							Info_Temp.addr=Addr_Array.Add(addr);
						else 
							Info_Temp.addr=-1;

					Code_Array.Add(Info_Temp);
				}
				if (errFlag)
				{
					errmsg.Format("第%d行语句错误!\r\n",count);
					errMessage+=errmsg;
					result=1;
				}
			}
			code="";
			addr="";
			name="";
			count++;
		}
		fclose( stream ); 
		if (!(lcount==0 && bcount==0) && lcount!=bcount+1)
		{
			result=1;
			errmsg.Format("程序中LD，ANB不匹配!");
			errMessage+=errmsg;
		}
	}
	if (result==0)
		result=CodeToSeat();
	return result;
}

int CMULDoc::Compile(CString &errMessage)
{
	int errflag;
	int HORcount;
	int next;
	int row;
	int col;
	int insertflag;
	CString str;
	IOPOINT *point;
	IOPOINT *temp;
	CPoint point_seat;
	CPoint curbegin;
	CPoint curend;
	CPoint prebegin;
	CPoint preend;
	POINTINFO code_info;
	CString errmsg;
	errflag=0;
	errflag=preCompile(errMessage);
	if (errflag)
		return errflag;

	CPoint cpoint=GetRowCol();
	if (cpoint.x>::MaxRows || cpoint.y>::MaxCols)
	{
		errflag=1;
		errmsg.Format("程序太大，页面画不下!\r\n\r\n页面最大可画100行梯形图，\r\n每行16个元器件!\r\n\r\n请将程序分解后再编译!");
		errMessage+=errmsg;
		return errflag;
	}
	Rows=cpoint.x;
	Cols=cpoint.y;
	m_mPlc.newfile();
	m_mPlc.SetRowCol(Rows,Cols);
	for (int i=0;i<m_nCodecount;i++)
	{
		insertflag=1;
		code_info=Code_Array.GetAt(i);
		point_seat=seat.GetAt(i);
		row=point_seat.x;
		col=point_seat.y;
		switch(code_info.code)
		{
		case 1:
			point=new LD;
			point->setcode("LD");
			point->setflag(1);
			point->setwhere(row,col);
			break;
		case 2:
			point=new LDI;
			point->setcode("LDI");
			point->setflag(2);
			point->setwhere(row,col);
			break;
		case 3:
		case 4:
			next=FindPort(i-1,curbegin,curend);
			if (curend.y>curbegin.y)
			{
				HORcount=curend.y-curbegin.y;
				AddHOR(row,col+1,HORcount);
				if (col>0)
					AddERECT(row,col-1);
				AddERECT(row,curend.y);
				if (code_info.code==3)
				{
					point=new LD;
					point->setcode("LD");
					point->setflag(1);
				}
				else
				{
					point=new LDI;
					point->setcode("LDI");
					point->setflag(2);
				}
				point->setwhere(row,col);
			}
			else
			{
				point=new OR;
				point->setcode("OR");
				point->setflag(3);
				point->setwhere(row,col);
				if (col>0)
				{
					temp=new ERECT;
					temp->setfiveflag(5);
					temp->setcode("ERECT");
					temp->setwhere(row,col-1);
					m_mPlc.insert_point(temp);
				}
				if (col<Cols)
				{
					temp=new ERECT;
					temp->setfiveflag(5);
					temp->setcode("ERECT");
					temp->setwhere(row,col);
					m_mPlc.insert_point(temp);
				}
			}
			break;
		case 5:
			point=new LD;
			point->setcode("LD");
			point->setflag(1);
			point->setwhere(row,col);
			//MakeUpHOR(row,col-1);
			break;
		case 6:
			point=new LDI;
			point->setcode("LDI");
			point->setflag(2);
			point->setwhere(row,col);
			//MakeUpHOR(row,col-1);
			break;
		case 8:
			insertflag=0;
			next=FindPort(i-1,curbegin,curend);
			next=FindPort(next-1,prebegin,preend);
			curend.x=curbegin.x;
			preend.x=prebegin.x;
			if (preend.y>curend.y)
			{
				HORcount=preend.y-curend.y;
				AddHOR(curend.x,curend.y+1,HORcount);
				curend.y=preend.y;
			}
			else if (curend.y>preend.y)
			{
				HORcount=curend.y-preend.y;
				AddHOR(preend.x,preend.y+1,HORcount);
			}
			if (curbegin.y>0)
				AddERECT(curbegin.x,curbegin.y-1);
			AddERECT(curend.x,curend.y);
			break;
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
		case 21:
			if (i<(m_nCodecount-1) && Code_Array.GetAt(i+1).code>0)
			{
				temp=new ERECT;
				temp->setcode("ERECT");
				temp->setfiveflag(5);
				temp->setwhere(row+1,col-1);
				m_mPlc.insert_point(temp);
			}
			while (col<Cols-1)
			{
				temp=new HOR;
				temp->setcode("HOR");
				temp->setflag(6);
				temp->setwhere(row,col);
				m_mPlc.insert_point(temp);
				col++;
			}
			if (code_info.code==9)
			{
				point=new OUTPOINT;
				point->setcode("OUT");
				point->setflag(7);
			}
			else
			{
				point=new ADDTION;
				switch(code_info.code)
				{
				case 10:
					point->setcode("SET");
					point->setflag(8);
					break;
				case 11:
					point->setcode("RST");
					point->setflag(18);
					break;
				case 12:
					point->setcode("S");
					point->setflag(9);
					break;
				case 13:
					point->setcode("R");
					point->setflag(19);
					break;
				case 14:
					point->setcode("MC");
					point->setflag(10);
					break;
				case 15:
					point->setcode("MCR");
					point->setflag(11);
					break;
				case 18:
					point->setcode("PLS");
					point->setflag(14);
					break;
				case 19:
					point->setcode("END");
					point->setflag(15);
					break;
				case 20:
					point->setflag(12);
					break;
				case 21:
					point->setflag(13);
					break;
				default:
					break;
				}
			}
			point->setwhere(row,col);
			break;
		default:
			insertflag=0;
		}
		if (insertflag)
		{
			if (code_info.addr>=0)
			{
				str=Addr_Array.GetAt(code_info.addr);
				point->setaddr(str);
				if (point->testaddr())
				{
					errflag=1;
					point->setaddr("");
					errmsg.Format("第 %d 行语句的地址不对!\r\n",i+1);
					errMessage+=errmsg;
				}
				else if (point->getflag()==12 || point->getflag()==13)
				{
					point->setcode(str);
					point->setaddr("");
				}
			}
			if (code_info.name>=0)
			{
				str=Name_Array.GetAt(code_info.name);
				point->setname(str);
			}
			m_mPlc.insert_point(point);
		}
	}
	return errflag;
}

void CMULDoc::MakeUpHOR(int row, int col)
{
	int count;
	IOPOINT *point;
	count=0;
	while(col>0)
	{
		point=m_mPlc.getpoint(row,col);
		if (point==NULL || point->getflag()==0)
			count++;
		else
			break;
		col--;
	}
	AddHOR(row,col,count);
}

void CMULDoc::OnCompileInstr() 
{
	// TODO: Add your command handler code here
	CFile LadFile;
	int errflag;
	CString pathname=this->GetPathName();
	if (pathname=="")
	{
		AfxMessageBox("请先保存文件，再进行编译！");
		return ;
	}
	this->OnSaveDocument(pathname);
	CString fname=pathname+this->GetTitle();
	int i=fname.Find('.');
	if (i!=-1)
		fname=fname.Mid(0,i);
	fname+=".lad";
	if (!LadFile.Open(fname,CFile::modeCreate|CFile::modeWrite))
		AfxMessageBox("Unable to open file");
	else
	{
		CArchive LadArchive(&LadFile,CArchive::store);
		CString compilemsg;
		try{
			if ((errflag=Compile(compilemsg))==0)
				compilemsg.Format("编译成功!");
			if (err_dlg)
			{
				err_dlg->Refresh(compilemsg);
				err_dlg->ShowWindow(SW_RESTORE);
			}
			else
			{
				err_dlg=new CSyntax(compilemsg,AfxGetMainWnd());
				err_dlg->CenterWindow();
				err_dlg->ShowWindow(SW_SHOW);
			}
			
			err_dlg->UpdateData(FALSE);
		}
		catch(...)
		{
			POSITION pos=this->GetFirstViewPosition();
			CView * pView=this->GetNextView(pos);
			pView->MessageBox("PLC程序编写错误！\n可能有逻辑错误！","编译出错",MB_ICONERROR|MB_OK);
		}

		if (!errflag)
		{
			CIO *point;
			IOPOINT *temp;
			CObArray m_pointArray;

			try{
				if (m_pointArray.GetSize()>0)
				{
					int total=m_pointArray.GetSize();
					for (int j=0;j<total;j++)
						delete m_pointArray.GetAt(j);
					m_pointArray.RemoveAll();
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
					for(int j=0;j<Cols;j++)
					{
						if (m_mPlc.testpoint(i,j))
						{
							CString str;
							point=new CIO;
							temp=m_mPlc.getpoint(i,j);
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
				m_pointArray.Serialize(LadArchive);
				LadArchive.Flush();
				LadArchive.Close();
			}
			catch(...)
			{
				POSITION pos=this->GetFirstViewPosition();
				CView * pView=this->GetNextView(pos);
				pView->MessageBox("LAD文件建立错误！","编译出错",MB_ICONERROR|MB_OK);
			}
		}
	}
}




