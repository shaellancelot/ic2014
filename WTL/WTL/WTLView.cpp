// WTLView.cpp : implementation of the CWTLView class
//
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
  
#include "resource.h"

#include "WTLView.h"

BOOL CWTLView::PreTranslateMessage(MSG* pMsg)
{
	pMsg;
	return FALSE;
}

LRESULT CWTLView::OnClose( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled )
{
	return OnFileExit( 0, 0, NULL, bHandled );
}

void CWTLView::DoPaint( CDCHandle dc )
{
	::GetWindowRect( m_hWnd, windowRect );			// 获取窗口位置及大小
	::GetClientRect( m_hWnd, clientRect );			// 获取用户区域大小 

	CPen NewPen;									// 创建画笔
	NewPen.CreatePen( PS_SOLID, 2, RGB(0,0,0) );	
	
	CBrush NewBrush;								// 创建画刷
	LOGBRUSH b;
	b.lbStyle = BS_HOLLOW;
	b.lbColor = RGB(255,0,0);
	b.lbHatch =	HS_BDIAGONAL;
	NewBrush.CreateBrushIndirect( &b);
 
    //dc.SaveDC();
 	
	// 设置背景颜色
    dc.SetBkColor ( RGB(255,255,255) );
	dc.ExtTextOut ( 0, 0, ETO_OPAQUE, clientRect, "", 0, NULL );
	// 添加画笔和画刷
	dc.SelectPen( NewPen );
	dc.SelectBrush( NewBrush );
	// 绘制直线
	for(int i=0;i<pDoc->GetLine()->GetSize();i++)
	{
		WTL::CPoint start,end;
		start = pDoc->GetLine()->GetData()[i].startPoint;
		end = pDoc->GetLine()->GetData()[i].endPoint;
		dc.MoveTo( start );
		dc.LineTo( end );
	}
	// 绘制椭圆
	for(int i=0;i<pDoc->GetEllipse()->GetSize();i++)
	{
		int left,top,right,bottom;
		left = pDoc->GetEllipse()->GetData()[i].left;
		top = pDoc->GetEllipse()->GetData()[i].top;
		right = pDoc->GetEllipse()->GetData()[i].right;
		bottom = pDoc->GetEllipse()->GetData()[i].bottom;
		dc.Ellipse( left, top, right, bottom );
	}
	// 动态效果
	if( bLeftButtonDown )
	{
		switch( nEditType )
		{
		case 0:
			break;
		case 1:// line
			dc.MoveTo( lineStartPoint );
			dc.LineTo( cursorPoint.x-windowRect.left, cursorPoint.y-windowRect.top );
			break;
		case 2:// ellipse
			dc.Ellipse( lineStartPoint.x, lineStartPoint.y, cursorPoint.x-windowRect.left, cursorPoint.y-windowRect.top );
			break;
		case 3:// rectangle
			break;
		default:
			break;
		}
	}
	dc.BeginPath();
	dc.MoveTo(0,0);
	dc.LineTo(cursorPoint.x-windowRect.left, cursorPoint.y-windowRect.top);
	dc.LineTo(0,200);
	dc.EndPath();
	//dc.StrokeAndFillPath();
    //dc.RestoreDC(-1);
	
}

LRESULT CWTLView::OnLeftButtonDown( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled )
{	
	WTL::CPoint start( cursorPoint.x-windowRect.left, cursorPoint.y-windowRect.top );
	bLeftButtonDown = true;
	switch( nEditType )
	{
	case 0:
		break;
	case 1:// line
		lineStartPoint = start;
		break;
	case 2:// ellipse
		lineStartPoint = start;
		break;
	case 3:// rectangle
		break;
	default:
		break;
	}
	return 0L;
}

LRESULT CWTLView::OnLeftButtonUp( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	WTL::CPoint end( cursorPoint.x-windowRect.left, cursorPoint.y-windowRect.top );
	bLeftButtonDown = false;
	switch( nEditType )
	{
	case 0:
		break;
	case 1:// line 		
		pDoc->SetLine( lineStartPoint , end );
		break;
	case 2:// ellipse
		pDoc->SetEllipse( lineStartPoint.x, lineStartPoint.y, end.x, end.y );
		break;
	case 3:// rectangle
		break;
	default:
		break;
	}
	return 0L;
}

LRESULT CWTLView::OnRightButtonDown( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	exit( 0 );						// 退出程序
	return 0L;
}

LRESULT CWTLView::OnMouseMove( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled )
{
	::GetCursorPos( &cursorPoint );
	if( bLeftButtonDown )
		RedrawWindow();
	return 0L;
}

LRESULT CWTLView::OnFileExit( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ )
{ 
	if( IsDocumentSave( m_hWnd, _Carbonium ) )
	{
		exit( 0 );					// 退出程序
	}
	return 0L;
}

LRESULT CWTLView::OnFileNew( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ )
{
	if(IsDocumentSave( m_hWnd, _Carbonium ))
	{
		GetDocument()->OnNew();
	}
	return 0L;						// 返回长整型
}

LRESULT CWTLView::OnFileOpen( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ )
{
	if ( IsDocumentSave( m_hWnd, _Carbonium ) )
	{
		bool bFailed;
		if (!GetDocument()->OnOpen(bFailed) && bFailed)
		{
			MessageBox(_T("Error loading file."), _Carbonium, MB_OK | MB_ICONERROR);
		}
	}
	return 0L;						// 返回长整型
}

LRESULT CWTLView::OnFileSave( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ )
{  
	HDC hDC = ::GetDC( m_hWnd );																//获取DC 
    HDC hDCMem = ::CreateCompatibleDC( hDC );													//创建兼容DC      
	HBITMAP hBitMap = ::CreateCompatibleBitmap( hDC, clientRect.Width(), clientRect.Height() );	//创建兼容位图      
	HBITMAP hOldMap = (HBITMAP)::SelectObject( hDCMem, hBitMap );								//将位图选入DC，并保存返回值        
    ::BitBlt( hDCMem, 0, 0, clientRect.Width(), clientRect.Height(), hDC, 0, 0, SRCCOPY );		//将屏幕DC的图象复制到内存DC中      
    
    CImage image;     
    image.Attach( hBitMap );     
    image.Save( _T("d:\B.jpg") );    
    image.Detach();     
    	
	bool bFailed;
	if( !GetDocument()->OnSave(bFailed) && bFailed )
	{
		// 保存失败
		TCHAR szText[MAX_PATH+1];
		const TCHAR* szName = GetDocument()->GetSZName();
		wsprintf(szText, _T("Error saving %s."), szName);
        MessageBox( szText, _Carbonium, MB_RETRYCANCEL | MB_ICONERROR );
	}

	// 选入上次的返回值  
	::SelectObject( hDCMem, hOldMap );       
    //释放      
    ::DeleteObject(hBitMap);     
    ::DeleteDC(hDCMem);     
    ::DeleteDC(hDC); 

	return 0L;
}

LRESULT CWTLView::OnFileSaveAs( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ )
{
	bool bFailed;
	if (!GetDocument()->OnSaveAs(bFailed) && bFailed)
	{
		TCHAR szText[MAX_PATH+1];
		const TCHAR* szName = GetDocument()->GetSZName();
		wsprintf(szText, _T("Error saving %s."), szName);
        
		MessageBox(szText, _Carbonium, MB_RETRYCANCEL | MB_ICONERROR);
	}
	return 0L;
}

LRESULT CWTLView::OnEditLine( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ )
{
	nEditType = 1;
	return 0L;
}

LRESULT CWTLView::OnEditEllipse( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ )
{
	nEditType = 2;
	return 0L;
}

CMyDoc* CWTLView::GetDocument() const
{
	return static_cast<CMyDoc*>( CDocumentClient::GetDocument() );
}

void CWTLView::InitVar()
{
	::GetWindowRect( m_hWnd, windowRect );			// 获取窗口位置及大小

	nEditType = 2;									// 默认图形编辑模式
	pDoc = GetDocument();							// 获取文档类指针
	bLeftButtonDown = false; 
}
