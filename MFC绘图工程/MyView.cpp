// MyView.cpp : implementation of the CMyView class
//

#include "stdafx.h"
#include "My.h"
#include "math.h"
#include "MyDoc.h"
#include "MyView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyView

IMPLEMENT_DYNCREATE(CMyView, CView)

BEGIN_MESSAGE_MAP(CMyView, CView)
	//{{AFX_MSG_MAP(CMyView)
	ON_COMMAND(ID_COORDINATE_MENU, OnCoordinateMenu)
	ON_COMMAND(ID_CLEAR_MENU, OnClearMenu)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_COLOR, OnColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyView construction/destruction

CMyView::CMyView()
{
	// TODO: add construction code here
     m_color = RGB( 0, 0, 0 );
}

CMyView::~CMyView()
{
}

BOOL CMyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyView drawing

void CMyView::OnDraw(CDC* pDC)
{
	CMyDoc* pDoc = GetDocument();
	
	ASSERT_VALID(pDoc);
	

	// TODO: add draw code for native data here
	for(int i=0;i<pDoc->NcircleNum;i++)
	{
	    CPen NewPen;
        NewPen.CreatePen(PS_SOLID,1,pDoc->ACircle[i].color);//�����»���
		pDC->SelectObject(&NewPen); //���»���ѡ���豸���� 	
	    pDC->SelectStockObject(NULL_BRUSH);//���»�ˢѡ���豸����
     


	 int x=pDoc->ACircle[i].nCentreX;
	 int y=pDoc->ACircle[i].nCentreY;
	 int r=pDoc->ACircle[i].nRadius;
	 pDC->Ellipse(x-r,y-r,x+r,y+r);
	   
	}

	CString S[30];
	for(int i=0;i<min(pDoc->NcircleNum,30);i++)
	{
	 S[i].Format("��%2d��Բ:(%3d,%3d) �뾶%3d��",i+1,pDoc->ACircle[i].nCentreX,pDoc->ACircle[i].nCentreY,pDoc->ACircle[i].nRadius);
	 pDC->SetBkMode(TRANSPARENT);
	 pDC->SetTextColor(RGB(0,0,255));
	 pDC->TextOut(800,25+i*20,S[i]);
	}
	
}

/////////////////////////////////////////////////////////////////////////////
// CMyView diagnostics

#ifdef _DEBUG
void CMyView::AssertValid() const
{
	CView::AssertValid();
}

void CMyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyDoc* CMyView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyDoc)));
	return (CMyDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyView message handlers

void CMyView::OnCoordinateMenu() 
{
	// TODO: Add your command handler code here
	CMyDoc* pDoc = GetDocument();
	CString strCoord[10];
	for(int i=0;i<min(pDoc->NcircleNum,10);i++)
	{
	 strCoord[i].Format("No.%2d:x=%3d,y=%3d",i+1,pDoc->ACircle[i].nCentreX,pDoc->ACircle[i].nCentreY);

	}
	for(int i=pDoc->NcircleNum;i<10;i++)
	{
	 strCoord[i].Format("No.%2d;x=%3d,y=%3d",i+1,0,0);
	}
     MessageBox(strCoord[0]+strCoord[1]+strCoord[2]+'\n'
		 +strCoord[3]+strCoord[4]+strCoord[5]+'\n'
		 +strCoord[6]+strCoord[7]+strCoord[8]+'\n'
		 +strCoord[9],
		 "Բ������");
}

void CMyView::OnClearMenu() 
{
	// TODO: Add your command handler code here
	CMyDoc *pDoc=GetDocument();
	pDoc->NcircleNum=0;
	pDoc->UpdateAllViews(NULL);
}

void CMyView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CMyDoc *pDoc=GetDocument();
	pDoc->m_bLButtonDown=TRUE;

	if(pDoc->NcircleNum<10)
	{
	 pDoc->NcircleNum++;	
	 int  NcircleNum=pDoc->NcircleNum;
	 pDoc->ACircle[NcircleNum-1].nCentreX=point.x;
	 pDoc->ACircle[NcircleNum-1].nCentreY=point.y;
     pDoc->ACircle[NcircleNum-1].color = m_color;
	  	
	
	}
	else
	{
        pDoc->NcircleNum = 11;   //��֤���һ��Բ�����ػ�
		MessageBox("Բ����Ŀ������10","����",MB_OK);
		
	}
	
	
	

	CView::OnLButtonDown(nFlags, point);
}

void CMyView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMyDoc *pDoc=GetDocument();
	pDoc->m_bLButtonDown=FALSE;


	CView::OnLButtonUp(nFlags, point);
}

void CMyView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMyDoc *pDoc=GetDocument();

	int NcircleNum=pDoc->NcircleNum;

	if( pDoc->m_bLButtonDown == TRUE  &&  NcircleNum <= 10)
	{   
		int nCentreX,nCentreY;
		 nCentreX=pDoc->ACircle[NcircleNum-1].nCentreX;
 	     nCentreY=pDoc->ACircle[NcircleNum-1].nCentreY;
	     pDoc->ACircle[NcircleNum-1].nRadius = (int)sqrt(pow((double)nCentreX-point.x,2)+pow((double)nCentreY-point.y,2));  
		   pDoc->UpdateAllViews(NULL);
	}
	
		

	CView::OnMouseMove(nFlags, point);
}

void CMyView::OnColor() 
{
	// TODO: Add your command handler code here
	CColorDialog Dlg;
	Dlg.m_cc.Flags |=CC_RGBINIT | CC_FULLOPEN;
	  Dlg.m_cc.rgbResult=m_color;
	
	if(IDOK==Dlg.DoModal())
	{
	   m_color=Dlg.m_cc.rgbResult;
		
	}
}
