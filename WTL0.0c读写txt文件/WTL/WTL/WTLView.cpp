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

LRESULT CWTLView::OnPaint( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	return 0;
}

LRESULT CWTLView::OnFileExit( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ )
{ 
	if( IsDocumentSave( m_hWnd, _Carbonium ) )
	{
		ExitProcess(0);
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

CMyDoc* CWTLView::GetDocument() const
{
	return static_cast<CMyDoc*>( CDocumentClient::GetDocument() );
}

LRESULT CWTLView::OnLeftButtonDown( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	return 0L;
}

LRESULT CWTLView::OnRightButtonDown( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	return 0L;
}

LRESULT CWTLView::OnMouseMove( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	return 0L;
}