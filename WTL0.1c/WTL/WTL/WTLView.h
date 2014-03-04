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
		//MESSAGE_HANDLER( WM_PAINT, OnPaint )
		CHAIN_MSG_MAP( WTL::CDoubleBufferImpl<CWTLView> )
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
		COMMAND_ID_HANDLER( ID_EDIT_LINE, OnEditLine )
		COMMAND_ID_HANDLER( ID_EDIT_ELLIPSE, OnEditEllipse )
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnClose( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ );
	//LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	void	DoPaint(CDCHandle dc);
	LRESULT OnLeftButtonDown( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ );
	LRESULT OnLeftButtonUp( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ );
	LRESULT OnRightButtonDown( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ );
	LRESULT OnMouseMove( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ );
	LRESULT OnFileExit( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ );
	LRESULT OnFileNew( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ );
	LRESULT OnFileOpen( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ );
	LRESULT OnFileSave( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ );
	LRESULT OnFileSaveAs( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ );
	LRESULT OnEditLine( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ );
	LRESULT OnEditEllipse( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ );

// 变量
private:
	CMyDoc* pDoc;
	WTL::CRect	windowRect;
	WTL::CRect	clientRect;
	WTL::CPoint	cursorPoint;
	
	bool	bLeftButtonDown;

	int		nEditType;
	WTL::CPoint	lineStartPoint;

// 普通函数
public:
	void	InitVar();				// 初始化
private:
    CMyDoc* GetDocument() const;

};
