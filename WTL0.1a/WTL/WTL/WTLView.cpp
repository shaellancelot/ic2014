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

	CMyDoc* pDoc = GetDocument();
	CPen NewPen;
	NewPen.CreatePen( PS_SOLID, 1, RGB(0,0,0) );	//创建新画笔
 
    dc.SaveDC();
 	
	// 设置背景颜色
    dc.SetBkColor ( RGB(255,255,255) );
	dc.ExtTextOut ( 0, 0, ETO_OPAQUE, clientRect, "", 0, NULL );

	dc.SelectPen(NewPen);
	dc.SelectStockBrush(NULL_BRUSH);
	
	dc.Ellipse(200,200,300,300);

	dc.MoveTo(200,0);
	dc.LineTo(0,200);
	dc.BeginPath();
	dc.MoveTo(0,0);
	dc.LineTo(cursorPoint.x-windowRect.left, cursorPoint.y-windowRect.top);
	dc.EndPath();
	dc.StrokePath();
 
    dc.RestoreDC(-1);
	
}

LRESULT CWTLView::OnLeftButtonDown( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled )
{	
	switch( nEditType )
	{
	case 0:break;
	case 1:
		break;
	case 2:break;
	case 3:break;
	default:break;
	}
	return 0L;
}

LRESULT CWTLView::OnLeftButtonUp( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
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
	if (IsDocumentSave( m_hWnd, _Carbonium ))
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
	bool bFailed;
	if (!GetDocument()->OnSave(bFailed) && bFailed)
	{
		TCHAR szText[256];
		const TCHAR* szName = GetDocument()->GetName();
		wsprintf(szText, _T("Error saving %s."), szName);
        
		MessageBox(szText, _Carbonium, MB_RETRYCANCEL | MB_ICONERROR);
	}
	return 0L;
}

LRESULT CWTLView::OnFileSaveAs( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ )
{
	bool bFailed;
	if (!GetDocument()->OnSaveAs(bFailed) && bFailed)
	{
		TCHAR szText[256];
		const TCHAR* szName = GetDocument()->GetName();
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

CMyDoc* CWTLView::GetDocument() const
{
	return static_cast<CMyDoc*>( CDocumentClient::GetDocument() );
}

void CWTLView::InitVar()
{
	CRect rect;
	
	::GetWindowRect( m_hWnd, rect );				// 获取窗口位置及大小

	windowRect = rect;
	nEditType = 0;
	
}
