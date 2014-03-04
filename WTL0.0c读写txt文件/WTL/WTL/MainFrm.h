// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "MyDoc.h"

class CMainFrame : public CFrameWindowImpl<CMainFrame>, 
				   public CUpdateUI<CMainFrame>,
				   public CMessageFilter, 
				   public CIdleHandler
{
public:
	DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)

	// 结构变量
	CWTLView			m_view;			// 视图窗口，相当于MFC的视图类，包含message map
	CMyDoc				m_doc;			// 文档类	
	CCommandBarCtrl		m_cmdBar;		// 命令条，控件类
		
	// 重载函数
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle();

	BEGIN_UPDATE_UI_MAP(CMainFrame)
		UPDATE_ELEMENT(ID_VIEW_TOOLBAR,UPDUI_MENUPOPUP)			// 弹出式菜单项
		UPDATE_ELEMENT(ID_VIEW_STATUS_BAR, UPDUI_MENUPOPUP)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMainFrame)
		MESSAGE_HANDLER( WM_CREATE, OnCreate )
		MESSAGE_HANDLER( WM_DESTROY, OnDestroy )		
		if ( uMsg == WM_COMMAND || uMsg == WM_CLOSE )
			CHAIN_MSG_MAP_ALT_MEMBER(m_view, 0)					// 定义message map的入口，即m_view
		COMMAND_ID_HANDLER(ID_VIEW_TOOLBAR, OnViewToolBar)		// 命令栏View-Toolbar按钮
		COMMAND_ID_HANDLER(ID_VIEW_STATUS_BAR, OnViewStatusBar)	// 命令栏View-Statusbar按钮
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)			// 命令栏Help按钮,工具栏“问号”按钮
		CHAIN_MSG_MAP(CUpdateUI<CMainFrame>)
		CHAIN_MSG_MAP(CFrameWindowImpl<CMainFrame>)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
	LRESULT OnViewToolBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnViewStatusBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};
