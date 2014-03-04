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

}

LRESULT CWTLView::ss( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled )
{
    ExitProcess( 0 );
	return 0;
}
