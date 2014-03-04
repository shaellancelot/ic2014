// WTLView.h : interface of the CWTLView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "MyDoc.h"

#define _Carbonium	_T("Carbonium")							// 软件名称

class CWTLView : public CWindowImpl<CWTLView>,
				 public CDocumentClient,
				 public WTL::CDoubleBufferImpl<CWTLView>	// 继承双缓冲类
{
public:
	DECLARE_WND_CLASS(NULL)

	BOOL PreTranslateMessage(MSG* pMsg);

	BEGIN_MSG_MAP(CWTLView)
		MESSAGE_HANDLER( WM_CLOSE, OnClose )
		MESSAGE_HANDLER( WM_PAINT, OnPaint )
		MESSAGE_HANDLER( WM_LBUTTONDOWN, OnLeftButtonDown )
		MESSAGE_HANDLER( WM_LBUTTONUP, OnLeftButtonUp )
		MESSAGE_HANDLER( WM_RBUTTONDOWN, OnRightButtonDown )
		MESSAGE_HANDLER( WM_RBUTTONUP, OnRightButtonDown )
		MESSAGE_HANDLER( WM_MOUSEMOVE, OnMouseMove )
		COMMAND_ID_HANDLER( ID_APP_EXIT, OnFileExit )			
		COMMAND_ID_HANDLER( ID_FILE_NEW, OnFileNew )
		COMMAND_ID_HANDLER( ID_FILE_OPEN, OnFileOpen )
		COMMAND_ID_HANDLER( ID_FILE_SAVE, OnFileSave )
		COMMAND_ID_HANDLER( ID_FILE_SAVE_AS, OnFileSaveAs )
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnClose( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ );
	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnLeftButtonDown( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ );
	LRESULT OnLeftButtonUp( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ );
	LRESULT OnRightButtonDown( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ );
	LRESULT OnMouseMove( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ );
	LRESULT OnFileExit( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ );
	LRESULT OnFileNew( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ );
	LRESULT OnFileOpen( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ );
	LRESULT OnFileSave( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ );
	LRESULT OnFileSaveAs( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ );

private:
    CMyDoc* GetDocument() const;

// 变量
private:
	CRect	windowRect;
	CPoint	cursorPoint;

// 普通函数
public:
	void	SetRect( CRect rect );
	CRect*	GetRect();

};
