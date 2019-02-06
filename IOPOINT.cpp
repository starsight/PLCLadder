//FILE:iopoint.CPP
#include "stdafx.h"
#include "iopoint.h"
//extern int CurrentCols;
extern FILE *fp;
extern int CurH;
extern int CurW;
extern CString filename;

IMPLEMENT_SERIAL(CIO,CObject,1)

CIO::CIO()
{
	name="";
	addr="";
	code="";
	Rows=0;
	Cols=0;
	flag=0;
	fiveflag=0;
	xpoint=0;
	ypoint=0;
}

/*
	IOPOINT 判断无件地址是否有效
*/
int IOPOINT::testaddr()
{
	char ch;
    if ((addr.GetLength()!=4) 
		|| addr[2]>'7' || addr[3]>'7')
       return 1;
    else
    {
		ch=addr[0];
		switch (ch)
		{
		case 'X':
				if (addr<"X000" || addr>"X527")
					return 1;
				else
					break;	
		case 'Y':
				if (addr<"Y000" || addr>"Y647")
					return 1;
				else
					break;
		case 'M':
				if (addr<"M000" || addr>"M977")
					return 1;
				else
					break;
		case 'C':
				if (addr<"C060" || addr>"C067" &&	addr>"C460"
						|| addr>"C467")
					return 1;
				else
					break;
		case 'T':
				if (!((addr>="T050" && addr<="T057") 
					||(addr>="T450" && addr<="T457") 
					||(addr>="T550" && addr<="T557") 
					||(addr>="T650" && addr<="T657") 
					||(addr>="T700" && addr<="T777")))
					return 1;
				else 
					break;
		default:
				return 1;
		}
	return 0;
	}
}

void IOPOINT::changeimg(int x,int y,CDC *pDC)
{
    int x1,y1,x2,y2;
	if (down!=NULL)
	   {
		x1=x+::CurW;
	   y1=y+::CurH-10;
	   x2=x1;
	   y2=y1+::CurH;
	   pDC->MoveTo(x1,y1);
	   pDC->LineTo(x2,y2);
	   if (down->up!=NULL)
	      {
	       x1=x;
	       x2=x1;
	       pDC->MoveTo(x1,y1);
		   pDC->LineTo(x2,y2);
	      }

	   }
	if (up!=NULL)
	   {
	   x1=x;
	   y1=y+::CurH-10;
	   x2=x1;
	   y2=y1-::CurH;
	   pDC->MoveTo(x1,y1);
	   pDC->LineTo(x2,y2);
	   if (up->down!=NULL)
	      {
		   x1=x+::CurW;
	      x2=x1;
		  pDC->MoveTo(x1,y1);
		  pDC->LineTo(x2,y2);
	      }
	   }
	if (fiveflag==5)
	{
		x1=x+::CurW;
		y1=y+::CurH-10;
		x2=x1;
		y2=y1-::CurH;
	   pDC->MoveTo(x1,y1);
	   pDC->LineTo(x2,y2);
	}
		
}

void LD::put_img(int x,int y,CDC *pDC)
{
	int x1,y1;
	x1=x;
	y1=y+::CurH-10;
	pDC->MoveTo(x1,y1);
	x1=x1+20;
	pDC->LineTo(x1,y1);
	pDC->MoveTo(x1,y1-10);
	y1=y+::CurH;
	pDC->LineTo(x1,y1);
	x1=x1+20;
	pDC->MoveTo(x1,y1);
	pDC->LineTo(x1,y1-20);
	pDC->MoveTo(x1,y1-10);
	pDC->LineTo(x+::CurW,y1-10);

}
void LD::print(int x,int y,CDC *pDC)
{
	put_img(x,y,pDC);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextAlign(TA_CENTER+TA_BOTTOM);
	pDC->TextOut(x+::CurW/2,y+40,name);
	pDC->TextOut(x+::CurW/2,y+60,addr);
	changeimg(x,y,pDC);
}

void LDI::put_img(int x,int y,CDC *pDC)
{
	int x1,y1;
	x1=x;
	y1=y+::CurH-10;
	pDC->MoveTo(x1,y1);
	x1=x1+20;
	pDC->LineTo(x1,y1);
	pDC->MoveTo(x1,y1-10);
	y1=y+::CurH;
	pDC->LineTo(x1,y1);
	x1=x1+20;
	pDC->MoveTo(x1,y1);
	pDC->LineTo(x1,y1-20);
	pDC->MoveTo(x1,y1-10);
	pDC->LineTo(x+::CurW,y1-10);
	pDC->MoveTo(x1-3,y1-17);
	pDC->LineTo(x1-17,y1-3);

}
void LDI::print(int x,int y,CDC *pDC)
{
	put_img(x,y,pDC);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextAlign(TA_CENTER+TA_BOTTOM);
	pDC->TextOut(x+::CurW/2,y+40,name);
	pDC->TextOut(x+::CurW/2,y+60,addr);
	changeimg(x,y,pDC);
}
void OR::put_img(int x,int y,CDC *pDC)
{
	int x1,y1;
	x1=x;
	pDC->MoveTo(x1,y-10);
	y1=y+::CurH-10;
	pDC->LineTo(x1,y1);
	x1=x1+20;
	pDC->LineTo(x1,y1);
	pDC->MoveTo(x1,y1-10);
	y1=y+::CurH;
	pDC->LineTo(x1,y1);
	x1=x1+20;
	pDC->MoveTo(x1,y1);
	pDC->LineTo(x1,y1-20);
	pDC->MoveTo(x1,y1-10);
	pDC->LineTo(x+::CurW,y1-10);
	pDC->LineTo(x+::CurW,y-10);
}
void OR::print(int x,int y,CDC *pDC)
{
	put_img(x,y,pDC);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextAlign(TA_CENTER+TA_BOTTOM);
	pDC->TextOut(x+::CurW/2,y+40,name);
	pDC->TextOut(x+::CurW/2,y+60,addr);
	changeimg(x,y,pDC);
}
void ORI::put_img(int x,int y,CDC *pDC)
{
	int x1,y1;
	x1=x;
	pDC->MoveTo(x1,y-10);
	y1=y+::CurH-10;
	pDC->LineTo(x1,y1);
	x1=x1+20;
	pDC->LineTo(x1,y1);
	pDC->MoveTo(x1,y1-10);
	y1=y+::CurH;
	pDC->LineTo(x1,y1);
	x1=x1+20;
	pDC->MoveTo(x1,y1);
	pDC->LineTo(x1,y1-20);
	pDC->MoveTo(x1,y1-10);
	pDC->LineTo(x+::CurW,y1-10);
	pDC->MoveTo(x1-3,y1-17);
	pDC->LineTo(x1-17,y1-3);
	pDC->MoveTo(x+::CurW,y1-10);
	pDC->LineTo(x+::CurW,y-10);
}
void ORI::print(int x,int y,CDC *pDC)
{
	put_img(x,y,pDC);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextAlign(TA_CENTER+TA_BOTTOM);
	pDC->TextOut(x+::CurW/2,y+40,name);
	pDC->TextOut(x+::CurW/2,y+60,addr);
	changeimg(x,y,pDC);
}
void HOR::print(int x,int y,CDC *pDC)
{
	pDC->MoveTo(x,y+::CurH-10);
	pDC->LineTo(x+::CurW,y+::CurH-10);
    changeimg(x,y,pDC);
}

int HOR::testaddr()
{
   return 0;
}

void ERECT::print(int x,int y,CDC *pDC)
{
	pDC->MoveTo(x+::CurW,y-10);
	pDC->LineTo(x+::CurW,y+::CurH-10);
}

void OUTPOINT::put_img(int x,int y,CDC *pDC)
{
	int x1,y1;
	x1=x+21;
	y1=y+::CurH-10;
	pDC->MoveTo(x,y1);
	pDC->LineTo(x1,y1);
	CRect rcEllipse(x1,y1-9,x1+18,y1+9);
	pDC->SelectStockObject(NULL_BRUSH);
	pDC->Ellipse(rcEllipse);
	pDC->MoveTo(x1+18,y1);
	pDC->LineTo(x+::CurW,y1);
}

void OUTPOINT::print(int x,int y,CDC *pDC)
{
	put_img(x,y,pDC);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextAlign(TA_CENTER+TA_BOTTOM);
	pDC->TextOut(x+::CurW/2,y+40,name);
	pDC->TextOut(x+::CurW/2,y+60,addr);
	changeimg(x,y,pDC);
}

void ADDTION::put_img(int x,int y,CDC *pDC)
{
	pDC->MoveTo(x,y+::CurH-10);
	pDC->LineTo(x+16,y+::CurH-10);
	pDC->MoveTo(x+21,y+::CurH-18);
	pDC->LineTo(x+16,y+::CurH-18);
	pDC->LineTo(x+16,y+::CurH-1);
	pDC->LineTo(x+21,y+::CurH-1);
	pDC->MoveTo(x+37,y+::CurH-1);
	pDC->LineTo(x+42,y+::CurH-1);
	pDC->LineTo(x+42,y+::CurH-18);
	pDC->LineTo(x+37,y+::CurH-18);
	pDC->MoveTo(x+42,y+::CurH-10);
	pDC->LineTo(x+::CurW,y+::CurH-10);

}
void ADDTION::print(int x,int y,CDC *pDC)
{
	put_img(x,y,pDC);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextAlign(TA_CENTER+TA_BOTTOM);
	pDC->TextOut(x+::CurW/2,y+40,name);
	pDC->TextOut(x+::CurW/2,y+60,addr);
	pDC->TextOut(x+30,y+77,code);
	changeimg(x,y,pDC);
}
int ADDTION::testaddr()
{
    char ch;
    int i;
    if (addr.GetLength()>4)// || strlen(name)==0)
	return 1;
    for (i=1;i<name.GetLength();i++)
	if (addr[i]>'7')
		return 1;
		switch (flag)
		{
     /************************************************************
	8--SET		9--S		10--MC		12--K
	18--RST		19--R           11--MCR         13--F
	14--PLS		15--END
     ************************************************************/
		case 8:
		case 9:
		case 18:
		case 19:  
			{
				ch=addr[0];
				switch (ch)
				{
					case 'Y':
							if (addr<"Y000" || addr>"Y647")
								return 1;
							else
								break;
					case 'M':
							if (addr<"M000" || addr>"M977")
								return 1;
							else
								break;
					case 'C':
							if (addr<"C060" || (addr>"C067" &&
								addr<"C460") || addr>"C467")
								return 1;
							else
								break;
					default:
							return 1;
				}//end of switch(ch)
				break;
		    }
		case 10:
		case 11:
		case 14:  
			{ 	
				ch=addr[0];
				switch (ch)
				{
					case 'M':
							if (addr<"M000" || addr>"M777")
								return 1;
							else
								break;
			      default:
						return 1;
				}//end of switch(ch)
				break;
			}
		case 12:  
			{
				if (addr<"K000" || addr>"K777")
					return 1;
				break;
		    }
		case 13:  
			{
				if (addr<"F670" || addr>"F673")
					return 1;
				break;
		    }
		case 15:
                break;
		default:
				return 1;
		}// switch(flag);
		return 0;
}


IOPOINT * LIST::ANBtest(IOPOINT *p)
{
	IOPOINT *q;
	IOPOINT *returnpoint=NULL;
	BOOL flag;
	flag=FALSE;
	while (p->unup!=NULL)
	{
		p=p->unup;
		q=p;
		while (q->getflag()!=0 
			&& (q->right!=NULL|| q->getfiveflag()==5))
		{
			flag=TRUE;
			if (q->undown!=NULL)
			{
				flag=FALSE;
				returnpoint=q;
				break;
		    }
			q=q->right;
		}
		if (flag)
			break;
	}
	return returnpoint;
}

IOPOINT * LIST::ANBcompile(IOPOINT *p,IOPOINT *endpoint)
{
//	IOPOINT *breakpoint;
	IOPOINT *returnpoint;
	IOPOINT *temp;
	IOPOINT point;
	int j;
	BOOL NoAnb;
//	breakpoint=p;
	j=0;
	NoAnb=TRUE;
	while(1)
	{
		if (NoAnb)
		{
			switch (p->getflag())
			{
			case 1:
					if (j>0)
						fprintf(::fp,"%s\t%s\t\t;%s\n","AND",p->addr,p->name);
					else
						fprintf(::fp,"%s\t%s\t\t;%s\n","LD",p->addr,p->name);
					j++;
					break;
			case 2:
					if (j>0)
						fprintf(::fp,"%s\t%s\t\t;%s\n","ANI",p->addr,p->name);
					else
						fprintf(::fp,"%s\t%s\t\t;%s\n","LDI",p->addr,p->name);
					j++;
					break;
			default:
					break;
			}// end of switch (p->getflag())
			p->setvisit(TRUE);
			if (p->down!=NULL)
			{
				temp=ORBtest(p,&point);
				if (temp!=NULL)
				{
					returnpoint=ORBcompile(temp);
					if (returnpoint==endpoint)
						return returnpoint;
					else if (returnpoint->down!=NULL)
					{
						temp=ORBtest(returnpoint,&point);
						if (temp!=NULL)
						{
							returnpoint=ORBcompile(temp);
							if (returnpoint==endpoint)
								return returnpoint;
						}
					}
				}
			}
			while (p->visit==TRUE)
				p=p->right;
		}// end of if (NoAnb)
		if (p->unup!=NULL)
	    {
			temp=ANBtest(p);
			if (temp!=NULL)
			{
				NoAnb=FALSE;
				returnpoint=ANBcompile(p,temp);
				if (j>0)
					fprintf(::fp,"%s\n","ANB");
				if (returnpoint->down!=NULL)
					{
						temp=ORBtest(returnpoint,&point);
						if (temp!=NULL)
						{
							returnpoint=ORBcompile(temp);
							if (returnpoint==endpoint)
								return returnpoint;
						}
					}
			}
			else
				NoAnb=TRUE;
	    }
		while (p->visit==TRUE)
			p=p->right;
	}// end of while(1)

}

IOPOINT * LIST::ORBtest(IOPOINT *p,IOPOINT *q)
{
	q=p->down;
	do
	{
		p=p->down;
		while ((q->left!=NULL)
				&& (q->left->getflag()!=0)
				&& (q->getfiveflag()!=9)
				&& (q->left->visit!=TRUE))
			q=q->left;
		if (((q->up!=NULL)||(q->getypoint()==0))
				&&(q->visit==0)
				&&(q->getflag()!=0))
			return p;
	
		q=q->down;
	}while (q!=NULL);
	p=NULL;
	return p;
}

IOPOINT * LIST::ORBcompile(IOPOINT *p)
{
	IOPOINT *breakpoint;
	IOPOINT *result;
	IOPOINT point;
	IOPOINT *q,*returnpoint;
	IOPOINT *temp;
//	int m;
	int i,j;
	BOOL NoAnb;
	i=0;
	j=1;
	q=p;
	NoAnb=TRUE;
	if (q->getflag()!=6)
	     i++;
	while ((q->left!=NULL)&&(q->left->getflag()!=0)
			&& (q->getfiveflag()!=9) && (q->left->visit!=TRUE))
	{
		q=q->left;
		if (q->getflag()!=6)
			i++;
	}
	returnpoint=p;
	result=p;
	breakpoint=q;
	while(1)
    {
		if (NoAnb)
		{
			switch (q->getflag())
			{
			case 1:
					if (i>1)
					{
						if (j==1)
							fprintf(::fp,"%s\t%s\t\t;%s\n",q->code,q->addr,q->name);
						else
							fprintf(::fp,"%s\t%s\t\t;%s\n","AND",q->addr,q->name);
						j++;
					}
					else
						fprintf(::fp,"%s\t%s\t\t;%s\n","OR",q->addr,q->name);
					break;
			case 2:
					if (i>1)
					{
						if (j==1)
							fprintf(::fp,"%s\t%s\t\t;%s\n",q->code,q->addr,q->name);
						else
							fprintf(::fp,"%s\t%s\t\t;%s\n","ANI",q->addr,q->name);
						j++;
					}
					else
						fprintf(::fp,"%s\t%s\t\t;%s\n","ORI",q->addr,q->name);
					break;
			case 3:
			case 4:
					fprintf(::fp,"%s\t%s\t\t;%s\n",q->code,q->addr,q->name);
			default:
					break;
			}//end of switch (q->getflag())
			q->setvisit(TRUE);
			if (q==p && j>1)
				fprintf(::fp,"%s\n","ORB");
			
			if (q->down!=NULL)
			{
				if (q!=p)
				{
					temp=ORBtest(q,&point);
					if (temp!=NULL)
						result=ORBcompile(temp);
				}
				if (q==p)
				{
					temp=ORBtest(q,&point);
					if (temp!=NULL && breakpoint->getypoint()==point.getypoint())
						returnpoint=ORBcompile(temp);
				}
			}
			if (q==p)
				break;
			else
				q=q->right;
		}// end of if (NoAnb)
		if (q->unup!=NULL)
		{
			temp=ANBtest(q);
			if (temp!=NULL)
			{
				NoAnb=0;
				result=ANBcompile(q,temp);
				if (j>1)
				fprintf(::fp,"%s\n","ANB");
				
				while (q->visit==TRUE)
					if (q==p)
						break;
					else
						q=q->right;
				if (q==p && q->visit==TRUE)
				{
					if (j>1)
						fprintf(::fp,"%s\n","ORB");
					if (result->down!=NULL)
					{
						temp=ORBtest(result,&point);
						if (temp!=NULL && breakpoint->getypoint()==point.getypoint())
							returnpoint=ORBcompile(temp);
					}
					break;
				}
			}// end of (m!=0)
			else
				NoAnb=1;
		}//end of if (q->unup!=NULL)
     }//end of while (1); (q!=p)

     return returnpoint;
}

int LIST::compile(IOPOINT *head)
{
	IOPOINT *p;
	IOPOINT *temp;
	IOPOINT *q;
	IOPOINT *returnpoint;
	IOPOINT point;
	int flag;
	BOOL found;
	BOOL NoAnb;
	//int  r;
	int i;
	if ((fp=fopen(::filename,"a+"))==NULL)
		return 5;
	p=head;
	i=0;
	NoAnb=TRUE;
	flag=p->getflag();
	found=FALSE;
	while(1)
	{
		while ((flag<7) && (p->right!=NULL))
		{
			if (p->unup!=NULL)
			{
				temp=ANBtest(p);
				if (temp!=NULL)
				{
					NoAnb=FALSE;
					returnpoint=ANBcompile(p,temp);
					if (i>0)
					fprintf(::fp,"%s\n","ANB");
					i++;
					while (returnpoint->down!=NULL
						&& (temp=ORBtest(returnpoint,&point))!=NULL)
					{
						returnpoint=ORBcompile(temp);
					}
					while (p->visit==TRUE)
						p=p->right;
					flag=p->getflag();
				}
				else
					NoAnb=TRUE;
			}
	
			if (NoAnb)
			{
				switch (flag)
				{
				case 1:
						if (i==0)
							fprintf(::fp,"%s\t%s\t\t;%s\n",p->code,p->addr,p->name);
						else
							fprintf(::fp,"%s\t%s\t\t;%s\n","AND",p->addr,p->name);
						i++;
						break;
				case 2:
						if (i==0)
							fprintf(::fp,"%s\t%s\t\t;%s\n",p->code,p->addr,p->name);
						else
							fprintf(::fp,"%s\t%s\t\t;%s\n","ANI",p->addr,p->name);
						i++;
						break;
				default:
						break;
				}//switch(flag)
				p->setvisit(TRUE);
				if (p->down!=NULL)
				{
					temp=ORBtest(p,&point);
					if (temp!=NULL)
					{
						returnpoint=ORBcompile(temp);
				//		while (returnpoint->down!=NULL
				//			&& (temp=ORBtest(returnpoint,&point))!=NULL)
				//		{
				//			returnpoint=ORBcompile(temp);
				//		}
					}
				}
				while (p->visit==TRUE)
					p=p->right;
				flag=p->getflag();
			}//if (NoAnb)
		}//while ((flag<7) && (p->right!=NULL))
		if (flag>=7)
		{
			fprintf(fp,"%s\t%s\t\t;%s\n",p->code,p->addr,p->name);
			p->setvisit(TRUE);
		}
		do
		{
			if (p->unup!=NULL)
			{
				temp=p;
				while (temp->unup!=NULL)
				{
					temp=temp->unup;
					q=temp;
					while (q->getflag()!=0 && q->getflag()<7
							&& q->right!=NULL)
						q=q->right;
					if (q->getflag()>=7)
					{
						found=TRUE;
						break;
					}
				}
				if (found)
				{
					p=temp;
					flag=p->getflag();
					break;
				}
			}// end of if (p->unup!=NULL)
			p=p->left;
		}while(p!=NULL && p->left!=NULL);
		if (!found)
			break;
		else
			found=FALSE;
	}//end of While(1)
	fprintf(fp,"\n;***\n\n");
	fclose(fp);
	return 0;
}

PLC::PLC()
{
	newfile();
	Rows=m_nAreRow;
	Cols=m_nAreCol;
}

void PLC::newfile()
{
	UINT i,j;
	for (i=0;i<m_nAreRow;i++)
		for (j=0;j<m_nAreCol;j++)
			point_array[i][j]=NULL;
	for (i=0;i<20;i++)
		list_array[i].root=0;
}

void PLC::getstep()
{
	int i,j;
	int n;
	BOOL flag;
	for (i=0,n=0;i<Rows;i++)
    {
		flag=TRUE;
		for (j=0;j<Cols;j++)
			if ((point_array[i][j] == NULL) 
				|| (point_array[i][j]->up!=NULL && j!=0))
			{
				flag=FALSE;
				break;
			}
		if (flag)
		{
			list_array[n].root=point_array[i][0];
			n++;
		}
	}
	step=n;
}

int PLC::testpoint(int row,int col)
{
	if (point_array[row][col]==NULL) return 0;
	else return 1;
}

void PLC::insert_point(IOPOINT *n)
{
	int i,j;
	int flag;
	IOPOINT *temp;
	i=n->getxpoint();
	j=n->getypoint();

	if (n->getfiveflag()!=5)
	{
		if (point_array[i][j]!=NULL)
		{
			flag=point_array[i][j]->getfiveflag();
			if (flag!=5 && flag!=9)
				remove_point(i,j);
			if (flag==5 || flag==9)
			{
				temp=point_array[i][j];
				n->setfiveflag(flag);
				n->left=temp->left;
				n->right=temp->right;
				n->up=temp->up;
				n->down=temp->down;
				n->unup=temp->unup;
				n->undown=temp->undown;
				if (n->up!=NULL)
					n->up->unup=n;
				if (n->unup!=NULL)
					n->unup->up=n;
				if (n->down!=NULL)
					n->down->undown=n;
				if (n->undown!=NULL)
					n->undown->down=n;
				delete (temp);
			}
		}
		point_array[i][j]=n;
		//第一列数据会与上下两列数据建立默认或关系
		if (j==0)
		{
			if ((i>0) && (point_array[i-1][j]!=NULL))
			{
				point_array[i-1][j]->unup=n;
				n->up=point_array[i-1][j];
			}
			if (point_array[i+1][j]!=NULL)
			{
				point_array[i+1][j]->up=n;
				n->unup=point_array[i+1][j];
			}
		}
		//非最后一列的节点与后一列建立关系
		if (j<Cols-1)
		{
			if (point_array[i][j+1] != NULL)
			{
				n->right=point_array[i][j+1];
				point_array[i][j+1]->left=n;
				if ((n->right->up !=NULL) 
					&& (n->right->up->left !=NULL))
				{
					n->right->up->left->down=n;
					n->undown=n->right->up->left;
				}
				if ((i>0) 
					&& (point_array[i][j+1]->getfiveflag()==9)
					&& (point_array[i-1][j]!=NULL))
				{
					point_array[i-1][j]->down=n;
					n->undown=point_array[i-1][j];
				}
			}
			if ((point_array[i+1][j+1]!=NULL)
				&& ((point_array[i+1][j+1]->up != NULL)
				|| (point_array[i+1][j+1]->getfiveflag()==9))
				&& (point_array[i+1][j+1]->left != NULL))
			{
				n->down=point_array[i+1][j];
				point_array[i+1][j]->undown=n;
			}
		}
		// 非第一列节点则与前一列建立关系
		if (j>0)
		{
			if  (point_array[i][j-1] != NULL)
			{
				n->left=point_array[i][j-1];
				point_array[i][j-1]->right=n;
				if ((n->left->down != NULL)
					&& (n->left->down->right != NULL))
				{
					point_array[i+1][j]->up=n;
					n->unup=point_array[i+1][j];
				}
				if ((i>0) && ((n->left->getfiveflag()==5)
					||(n->left->undown!=NULL))
					&& (point_array[i-1][j]!=NULL))
				{
					n->up=point_array[i-1][j];
					point_array[i-1][j]->unup=n;
				}
			}
			if ((point_array[i+1][j-1]!=NULL)
				&& ((point_array[i+1][j-1]->undown!=NULL)
				||(point_array[i+1][j-1]->getfiveflag()==5))
				&& (point_array[i+1][j]!=NULL))
			{
				n->unup=point_array[i+1][j];
				point_array[i+1][j]->up=n;
			}
			if  ((i>0) && (point_array[i-1][j-1]!=NULL)
				&& (point_array[i-1][j-1]->down != NULL)
				&& (point_array[i-1][j] != NULL))
			{
				n->up=point_array[i-1][j];
				point_array[i-1][j]->unup=n;
			}
		}  //if (j>0)
		if (point_array[i+1][j]!=NULL &&
			point_array[i+1][j]->getfiveflag()==5)
		{
			n->down=point_array[i+1][j];
			point_array[i+1][j]->undown=n;
		}
		if (point_array[i+1][j]!=NULL &&
			point_array[i+1][j]->getfiveflag()==9)
		{
			n->unup=point_array[i+1][j];
			point_array[i+1][j]->up=n;
		}
		if (point_array[i+1][j]!=NULL &&
			(point_array[i+1][j]->getflag()==3
			|| point_array[i+1][j]->getflag()==4))
		{
			n->down=point_array[i+1][j];
			point_array[i+1][j]->undown=n;
			point_array[i+1][j]->up=n;
			n->unup=point_array[i+1][j];
			if ((n->left != NULL) && (point_array[i+1][j]->left != NULL))
			{
				n->left->down=point_array[i+1][j]->left;
				point_array[i+1][j]->left->undown=n->left;
			}
			if ((n->right != NULL) && (point_array[i+1][j]->right != NULL))
			{
				point_array[i+1][j]->right->up=n->right;
				n->right->unup=point_array[i+1][j]->right;
			}
		}

	/*	if ((i>0) && ((n->getflag()==3) || (n->getflag()==4)))
		{
			if (point_array[i-1][j] != NULL)
			{
				n->up=point_array[i-1][j];
				point_array[i-1][j]->unup=n;
				point_array[i-1][j]->down=n;
				n->undown=point_array[i-1][j];
				if ((point_array[i-1][j]->left != NULL) 
					&& (n->left != NULL))
				{
					point_array[i-1][j]->left->down=n->left;
					n->left->undown=point_array[i-1][j];
				}
				if ((n->right != NULL) 
					&& (point_array[i-1][j]->right != NULL))
				{
					n->right->up=point_array[i-1][j]->right;
					point_array[i-1][j]->right->unup=n->right;
				}
			} //if (point_array[i-1][j] != NULL)
		}//if ((i>0) && ((n->getflag()==3) || (n->getflag()==4)))*/
	}//if (n->getflag()!=5)
	else
	{
		if (i>0)
		{
			if (point_array[i][j]!=NULL)
				point_array[i][j]->setfiveflag(5);
			else
				point_array[i][j]=n;
			if (j<Cols-1)
			{
				if (point_array[i][j+1]!=NULL)
				{
					if (point_array[i][j+1]->getfiveflag()!=5)
						point_array[i][j+1]->setfiveflag(9);
					point_array[i][j]->right=point_array[i][j+1];
					point_array[i][j+1]->left=point_array[i][j];
				}
				else
				{
					temp=new IOPOINT;
					temp->setwhere(i,j+1);
					temp->setfiveflag(9);
					point_array[i][j+1]=temp;
					point_array[i][j]->right=point_array[i][j+1];
					point_array[i][j+1]->left=point_array[i][j];
				}
				if ((point_array[i-1][j+1]!=NULL)
					&&(point_array[i][j]->right!=NULL))
				{
					point_array[i-1][j+1]->unup=point_array[i][j]->right;
					point_array[i][j]->right->up=point_array[i-1][j+1];
				}
			}// end of if (j<Maxcol-1)
			if (point_array[i-1][j]!=NULL)
			{
				point_array[i-1][j]->down=point_array[i][j];
				point_array[i][j]->undown=point_array[i-1][j];
			}

			if ((point_array[i+1][j]!=NULL)
				&& (point_array[i+1][j]->getfiveflag()==5))
			{
				point_array[i][j]->down=point_array[i+1][j];
				point_array[i+1][j]->undown=point_array[i][j];
				if (j<Cols)
				{
					point_array[i][j+1]->unup=point_array[i+1][j+1];
					point_array[i+1][j+1]->up=point_array[i][j+1];
				}
			}
		}//end of if (i>0)
	}//end of "if(n->getflag()!=5" else
}

void PLC::remove_point(int x,int y)
{
	int i,j;
	IOPOINT *temp,*p;
	i=x;
	j=y;
	temp=point_array[i][j];
	if (temp==NULL) return;
	if (temp->getfiveflag()==9)
	{
		p=new IOPOINT;
		p->setfiveflag(9);
	    if (temp->up!=NULL)
		{
			p->up=temp->up;
			p->up->unup=p;
		}
	    if (temp->unup!=NULL)
		{
			p->unup=temp->unup;
			p->unup->up=p;
		}
	    if (temp->left!=NULL)
		{
			p->left=temp->left;
			p->left->right=p;
		}
	    point_array[i][j]=p;
	}  // if (temp->getfiveflag()==9)
	else
	{
		point_array[i][j]=NULL;
	    if (temp->left != NULL)
			temp->left->right=NULL;
	    if (temp->right != NULL)
			temp->right->left=NULL;
	    if (temp->up!=NULL)
	    {
			temp->up->unup=NULL;
			temp->up=NULL;
	    }
	    if (temp->down!=NULL)
	    {
			temp->down->undown=NULL;
			temp->down=NULL;
	    }
	    if (temp->unup!=NULL)
	    {
			temp->unup->up=NULL;
			temp->unup=NULL;
	    }
	    if (temp->undown!=NULL)
	    {
			temp->undown->down=NULL;
			temp->undown=NULL;
	    }
		if (temp->getfiveflag()==5)
		{
			if (temp->right!=NULL)//j<m_nAreCol-1)
			{
				if (temp->right->getfiveflag()!=5)
					temp->right->setfiveflag(0);
				int flag=temp->right->getflag();
				if (flag==3	|| flag==4)
					temp->right->setflag(flag-2);
				if (temp->right->up!=NULL)
				{
					temp->right->up->unup=NULL;
					temp->right->up=NULL;
				}
				if (temp->right->getflag()==0 
					&& temp->right->getfiveflag()!=5)
				{
					p=temp->right;
					if (p->unup!=NULL)
					{
						p->unup->up=NULL;
						p->unup=NULL;
					}
					if (p->down!=NULL)
					{
						p->down->undown=NULL;
						p->down=NULL;
					}
					if (p->undown!=NULL)
					{
						p->undown->down=NULL;
						p->undown=NULL;
					}
					delete p;
					point_array[i][j+1]=NULL;
				} //if (temp->right->getflag()==0)
			} // if (temp->right!=NULL)
			if (temp->left!=NULL && temp->left->getfiveflag()==5)
			{
				IOPOINT * renew;
				renew=new IOPOINT;
				renew->setfiveflag(9);
				renew->setwhere(i,j);
				insert_point(renew);
			}
		}//if (temp->getfiveflag()==5)
	}//if (temp->getfiveflag()==9)   else
	delete temp;
}
int PLC::syntax(CString &m_strlist)
{
	IOPOINT *p;
	int outflag,topflag,result,flag;
	int i,j;
	CString str;
	result=0;
//	m_list.ResetContent();
	for (i=0;i<step;i++)
    {
		outflag=0;
		topflag=0;
		p=list_array[i].root;
		for (j=0;j<Cols;j++)
		{
			flag=p->getflag();
			if (flag>=7)
			{
				outflag++;
				p=p->right;
				continue;
			}
			if (flag!=6 && outflag)
				outflag++;
			if (flag==3 || flag==4 || p->getfiveflag()==5)
				topflag++;
			p=p->right;
		}
		if (outflag!=1)
		{
			result=1;
			str.Format("第 %d 程序段输出语句错误!\r\n",i+1);
			m_strlist+=str;
		}
		if (topflag)
		{
			result=1;
			str.Format("第 %d 程序段首行含有 %d 个OR、ORI或ERECT结点!\r\n",i+1,topflag);
			m_strlist+=str;
		}
	}
	CString addr;
	int fiveflag;
	for (i=0;i<100;i++)
		for (j=0;j<Cols;j++)
		if (point_array[i][j]!=NULL)
		{
			flag=point_array[i][j]->getflag();
			fiveflag=point_array[i][j]->getfiveflag();
			point_array[i][j]->getaddr(&addr);
			
			if ((point_array[i][j]->left==NULL)
				&& (point_array[i][j]->up==NULL)
				&& (point_array[i][j]->down==NULL)
				&& (point_array[i][j]->right==NULL))
			{
				result=1;
				str.Format("第 %d 行，第 %d 列是孤立结点!\r\n",i+1,j+1);
				m_strlist+=str;
			}
			if ((flag==0 && fiveflag!=5 && fiveflag!=9)
				|| flag==100)
			{
				result=1;
				str.Format("第 %d 行，第 %d 列结点类型错误!\r\n",i+1,j+1);
				m_strlist+=str;
			}
			if (addr.GetLength()==0 && flag!=0 && flag!=6 
				&& flag!=12 && flag!=13 && flag!=15)
			{
				result=1;
				str.Format("第 %d 行，第 %d 列结点没进行元器件设置!\r\n",i+1,j+1);
				m_strlist+=str;
			}
			point_array[i][j]->getcode(&addr);
			if ((flag==12 || flag==13) && addr.GetLength()!=4)
			{
				result=1;
				str.Format("第 %d 行，第 %d 列结点F、K命令错误!\r\n",i+1,j+1);
				m_strlist+=str;
			}
		}
	return result;
}

int PLC::compiled(CString &m_strlist)
{
	int i,j;
	int flag;
	CString str;
	getstep();
	flag=syntax(m_strlist);
	if (flag)
		return flag;
	if ((fp=fopen(::filename,"w+"))==NULL)
	{
		str.Format("文件%s不能建立!\r\n",::filename);
		m_strlist+=str;
        return 1;
	}
    fclose(fp);
	for (i=0;i<Rows;i++)
		for (j=0;j<Cols;j++)
			if (point_array[i][j]!=NULL)
				point_array[i][j]->setvisit(FALSE);
	for (i=0;i<step;i++)
    {
		flag=list_array[i].compile(list_array[i].root);
		if (flag)
		{
			str.Format("编译错误!\r\n");
			m_strlist+=str;
			return flag;
		}
    }
	
	int sum=0;
	for (i=0;i<Rows;i++)
		for (j=0;j<Cols;j++)
		{
			if (point_array[i][j]!=NULL)
			{
				flag=point_array[i][j]->getflag();
				if (point_array[i][j]->visit==FALSE
					&& flag!=0 && flag!=6)
				{
					str.Format("第 %d 行，第 %d 列结点没有编译!\r\n",i+1,j+1);
					m_strlist+=str;
					sum++;
					if (sum==10)
						return 1;
				}
			}
		}
	return sum;
}


void PLC::SetRowCol(int row, int col)
{
	Rows=row;
	Cols=col;
}

int PLC::getrows()
{
	return Rows;
}

int PLC::getcols()
{
	return Cols;
}

void CIO::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar<<name;
		ar<<addr;
		ar<<code;
		ar<<Rows;
		ar<<Cols;
		ar<<flag;
		ar<<fiveflag;
		ar<<xpoint;
		ar<<ypoint;
	}
	else
	{
		ar>>name;
		ar>>addr;
		ar>>code;
		ar>>Rows;
		ar>>Cols;
		ar>>flag;
		ar>>fiveflag;
		ar>>xpoint;
		ar>>ypoint;
	}
}

IOPOINT * PLC::getpoint(int row, int col)
{
	return (point_array[row][col]);
}
