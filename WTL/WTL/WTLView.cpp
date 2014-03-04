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
	::GetWindowRect( m_hWnd, windowRect );			// ��ȡ����λ�ü���С
	::GetClientRect( m_hWnd, clientRect );			// ��ȡ�û������С 

	CPen NewPen;									// ��������
	NewPen.CreatePen( PS_SOLID, 2, RGB(0,0,0) );	
	
	CBrush NewBrush;								// ������ˢ
	LOGBRUSH b;
	b.lbStyle = BS_HOLLOW;
	b.lbColor = RGB(255,0,0);
	b.lbHatch =	HS_BDIAGONAL;
	NewBrush.CreateBrushIndirect( &b);
 
    //dc.SaveDC();
 	
	// ���ñ�����ɫ
    dc.SetBkColor ( RGB(255,255,255) );
	dc.ExtTextOut ( 0, 0, ETO_OPAQUE, clientRect, "", 0, NULL );
	// ��ӻ��ʺͻ�ˢ
	dc.SelectPen( NewPen );
	dc.SelectBrush( NewBrush );
	// ����ֱ��
	for(int i=0;i<pDoc->GetLine()->GetSize();i++)
	{
		WTL::CPoint start,end;
		start = pDoc->GetLine()->GetData()[i].startPoint;
		end = pDoc->GetLine()->GetData()[i].endPoint;
		dc.MoveTo( start );
		dc.LineTo( end );
	}
	// ������Բ
	for(int i=0;i<pDoc->GetEllipse()->GetSize();i++)
	{
		int left,top,right,bottom;
		left = pDoc->GetEllipse()->GetData()[i].left;
		top = pDoc->GetEllipse()->GetData()[i].top;
		right = pDoc->GetEllipse()->GetData()[i].right;
		bottom = pDoc->GetEllipse()->GetData()[i].bottom;
		dc.Ellipse( left, top, right, bottom );
	}
	// ��̬Ч��
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
	exit( 0 );						// �˳�����
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
		exit( 0 );					// �˳�����
	}
	return 0L;
}

LRESULT CWTLView::OnFileNew( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ )
{
	if(IsDocumentSave( m_hWnd, _Carbonium ))
	{
		GetDocument()->OnNew();
	}
	return 0L;						// ���س�����
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
	return 0L;						// ���س�����
}

LRESULT CWTLView::OnFileSave( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ )
{  
	HDC hDC = ::GetDC( m_hWnd );																//��ȡDC 
    HDC hDCMem = ::CreateCompatibleDC( hDC );													//��������DC      
	HBITMAP hBitMap = ::CreateCompatibleBitmap( hDC, clientRect.Width(), clientRect.Height() );	//��������λͼ      
	HBITMAP hOldMap = (HBITMAP)::SelectObject( hDCMem, hBitMap );								//��λͼѡ��DC�������淵��ֵ        
    ::BitBlt( hDCMem, 0, 0, clientRect.Width(), clientRect.Height(), hDC, 0, 0, SRCCOPY );		//����ĻDC��ͼ���Ƶ��ڴ�DC��      
    
    CImage image;     
    image.Attach( hBitMap );     
    image.Save( _T("d:\B.jpg") );    
    image.Detach();     
    	
	bool bFailed;
	if( !GetDocument()->OnSave(bFailed) && bFailed )
	{
		// ����ʧ��
		TCHAR szText[MAX_PATH+1];
		const TCHAR* szName = GetDocument()->GetSZName();
		wsprintf(szText, _T("Error saving %s."), szName);
        MessageBox( szText, _Carbonium, MB_RETRYCANCEL | MB_ICONERROR );
	}

	// ѡ���ϴεķ���ֵ  
	::SelectObject( hDCMem, hOldMap );       
    //�ͷ�      
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
	::GetWindowRect( m_hWnd, windowRect );			// ��ȡ����λ�ü���С

	nEditType = 2;									// Ĭ��ͼ�α༭ģʽ
	pDoc = GetDocument();							// ��ȡ�ĵ���ָ��
	bLeftButtonDown = false; 
}
