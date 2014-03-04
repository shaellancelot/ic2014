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

	// �ṹ����
	CWTLView			m_view;			// ��ͼ���ڣ��൱��MFC����ͼ�࣬����message map
	CMyDoc				m_doc;			// �ĵ���	
	CCommandBarCtrl		m_cmdBar;		// ���������ؼ���
		
	// ���غ���
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle();

	BEGIN_UPDATE_UI_MAP(CMainFrame)
		UPDATE_ELEMENT(ID_VIEW_TOOLBAR,UPDUI_MENUPOPUP)			// ����ʽ�˵���
		UPDATE_ELEMENT(ID_VIEW_STATUS_BAR, UPDUI_MENUPOPUP)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMainFrame)
		MESSAGE_HANDLER( WM_CREATE, OnCreate )
		MESSAGE_HANDLER( WM_DESTROY, OnDestroy )		
		if ( uMsg == WM_COMMAND || uMsg == WM_CLOSE )
			CHAIN_MSG_MAP_ALT_MEMBER(m_view, 0)					// ����message map����ڣ���m_view
		COMMAND_ID_HANDLER(ID_VIEW_TOOLBAR, OnViewToolBar)		// ������View-Toolbar��ť
		COMMAND_ID_HANDLER(ID_VIEW_STATUS_BAR, OnViewStatusBar)	// ������View-Statusbar��ť
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)			// ������Help��ť,���������ʺš���ť
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
