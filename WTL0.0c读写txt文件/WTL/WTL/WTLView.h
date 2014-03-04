// WTLView.h : interface of the CWTLView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "MyDoc.h"

#define _Carbonium	_T("Carbonium")							// 软件名称	

class CWTLView : public CWindowImpl<CWTLView, CRichEditCtrl>,
				 public CDocumentClient,
				 public WTL::CDoubleBufferImpl<CWTLView>	// 继承双缓冲类
{
public:
	// rich edit control: a window in which the user can enter and edit text
	//DECLARE_WND_SUPERCLASS( NULL, CRichEditCtrl::GetWndClassName() )		
	//DECLARE_WND_SUPERCLASS( NULL, _T("qw") )
	DECLARE_WND_CLASS(NULL)

	BOOL PreTranslateMessage(MSG* pMsg);

	// BEGIN_MSG_MAP_EX不同于BEGIN_MSG_MAP，ATL的消息映射宏可以和WTL的宏混合使用
	BEGIN_MSG_MAP_EX(CWTLView)
		MESSAGE_HANDLER( WM_CLOSE, OnClose )
		MESSAGE_HANDLER( WM_PAINT, OnPaint )
		MESSAGE_HANDLER( WM_LBUTTONDOWN, OnLeftButtonDown )
		MESSAGE_HANDLER( WM_RBUTTONDOWN, OnClose )
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
	LRESULT OnPaint( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ );
	LRESULT OnFileExit( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ );
	LRESULT OnFileNew( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ );
	LRESULT OnFileOpen( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ );
	LRESULT OnFileSave( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ );
	LRESULT OnFileSaveAs( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ );
	LRESULT OnLeftButtonDown( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ );
	LRESULT OnRightButtonDown( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ );
	LRESULT OnMouseMove( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ );
// 普通函数
	
private:
    CMyDoc* GetDocument() const;
};
