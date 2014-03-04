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

LRESULT CWTLView::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
/*
	CPaintDC dc(m_hWnd);

	//TODO: Add your drawing code here
	CRect      rc;
    SYSTEMTIME st;
    CString    sTime;
 
    // Get our window's client area.
    GetClientRect ( rc );
 
    // Build the string to show in the window.
    GetLocalTime ( &st );
    sTime.Format ( _T("The time is %d:%02d:%02d"), st.wHour, st.wMinute, st.wSecond );
 
    // Set up the DC and draw the text.
    dc.SaveDC();
 
	
    dc.SetBkColor ( RGB(255,153,0) );
    dc.SetTextColor ( RGB(0,0,0) );
    dc.ExtTextOut ( 0, 0, ETO_OPAQUE, rc, sTime, sTime.GetLength(), NULL );
 
    // Restore the DC.
    dc.RestoreDC(-1);
*/

	return 0;
}

LRESULT CWTLView::OnCreate(LPCREATESTRUCT lpcs)
{
    SetTimer ( 1, 1000 );				// 每秒触发一次
    SetMsgHandled(false);
    return 0;
}

void CWTLView::OnDestroy()
{
    KillTimer( 1 );
    SetMsgHandled(false);
}

void CWTLView::OnTimer ( UINT uTimerID )
{
    if ( 1 != uTimerID )
        SetMsgHandled( false );
    else
        RedrawWindow();
}

void CWTLView::DoPaint( CDCHandle dc )
{
/*
    CRect      rc;
    SYSTEMTIME st;
    CString    sTime;
 
    // Get our window's client area.
    GetClientRect ( rc );
 
    // Build the string to show in the window.
    GetLocalTime ( &st );
    sTime.Format ( _T("The time is %d:%02d:%02d"), st.wHour, st.wMinute, st.wSecond );
 
    // Set up the DC and draw the text.
    dc.SaveDC();
 
	
    dc.SetBkColor ( RGB(255,153,0) );
    dc.SetTextColor ( RGB(0,0,0) );
    dc.ExtTextOut ( 0, 0, ETO_OPAQUE, rc, sTime, sTime.GetLength(), NULL );
 
    // Restore the DC.
    dc.RestoreDC(-1);

	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(&ps);
	RECT rect; GetClientRect(&rect);

	DrawText(hdc, GetDocument()->GetText(), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	EndPaint(&ps);
*/

}

LRESULT CWTLView::OnClose(UINT, WPARAM, LPARAM, BOOL& bHandled)
{
	return OnFileExit(0, 0, NULL, bHandled);
}

LRESULT CWTLView::OnFileNew( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ )
{
	if (IsDocumentSafe(m_hWnd, _T("WindowsApp")))
	{
		GetDocument()->OnNew();
	}
	return 0L;						// 返回长整型
}

LRESULT CWTLView::OnFileOpen( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ )
{
	if (IsDocumentSafe(m_hWnd, _T("WindowsApp")))
	{
		bool bFailed;
		if (!GetDocument()->OnOpen(bFailed) && bFailed)
		{
			MessageBox(_T("Error loading file."), _T("WindowsApp"), MB_OK | MB_ICONERROR);
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
        
		MessageBox(szText, _T("WindowsApp"), MB_RETRYCANCEL | MB_ICONERROR);
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
        
		MessageBox(szText, _T("WindowsApp"), MB_RETRYCANCEL | MB_ICONERROR);
	}
	return 0L;
}

LRESULT CWTLView::OnFileExit( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ )
{
	if (IsDocumentSafe(m_hWnd, _T("WindowsApp")))
	{
		::DestroyWindow(GetParent());
	}
	return 0L;
}

CMyDoc* CWTLView::GetDocument() const
{
	return static_cast<CMyDoc*>( CDocumentClient::GetDocument() );
}
