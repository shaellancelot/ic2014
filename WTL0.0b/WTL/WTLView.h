// WTLView.h : interface of the CWTLView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "MyDoc.h"

class CWTLView : public CWindowImpl< CWTLView, CRichEditCtrl >,
				 public CDocumentClient,
				 public WTL::CDoubleBufferImpl<CWTLView>  // 继承双缓冲类
{
public:
	DECLARE_WND_SUPERCLASS(NULL, CRichEditCtrl::GetWndClassName())
	//DECLARE_WND_SUPERCLASS(NULL, _T("Shael"))
	//DECLARE_WND_CLASS(NULL)

	BOOL PreTranslateMessage(MSG* pMsg);

	// BEGIN_MSG_MAP_EX不同于BEGIN_MSG_MAP，ATL的消息映射宏可以和WTL的宏混合使用
	BEGIN_MSG_MAP_EX(CWTLView)
		CHAIN_MSG_MAP( WTL::CDoubleBufferImpl<CWTLView>)
		//MESSAGE_HANDLER( WM_PAINT, OnPaint )
		//MESSAGE_HANDLER(WM_CLOSE, OnClose)
		MSG_WM_CREATE( OnCreate )
        MSG_WM_DESTROY( OnDestroy )
		MSG_WM_TIMER( OnTimer )
		COMMAND_ID_HANDLER( ID_FILE_NEW, OnFileNew )
		COMMAND_ID_HANDLER( ID_FILE_OPEN, OnFileOpen )
		COMMAND_ID_HANDLER( ID_FILE_SAVE, OnFileSave )
		COMMAND_ID_HANDLER( ID_FILE_SAVE_AS, OnFileSaveAs )
		COMMAND_ID_HANDLER( ID_APP_EXIT, OnFileExit )
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnPaint( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled );
	LRESULT OnClose( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
	LRESULT OnFileNew( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ );
	LRESULT OnFileOpen( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ );
	LRESULT OnFileSave( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ );
	LRESULT OnFileSaveAs( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ );
	LRESULT OnFileExit( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ );
	void	DoPaint(CDCHandle dcc);
	LRESULT OnCreate( LPCREATESTRUCT lpcs );
	void	OnDestroy();
	void	OnTimer( UINT_PTR wParam );

private:
    CMyDoc* GetDocument() const;
};
