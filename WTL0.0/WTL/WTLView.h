// WTLView.h : interface of the CWTLView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

class CWTLView : public CWindowImpl<CWTLView>,
				 public WTL::CDoubleBufferImpl<CWTLView>  // �̳�˫������
{
public:
	DECLARE_WND_CLASS(NULL)

	BOOL PreTranslateMessage(MSG* pMsg);

	// BEGIN_MSG_MAP_EX��ͬ��BEGIN_MSG_MAP��ATL����Ϣӳ�����Ժ�WTL�ĺ���ʹ��
	BEGIN_MSG_MAP_EX(CWTLView)
		CHAIN_MSG_MAP( WTL::CDoubleBufferImpl<CWTLView>)
		MESSAGE_HANDLER( WM_MOUSEMOVE, ss )
		//MESSAGE_HANDLER( WM_PAINT, OnPaint )
		MSG_WM_CREATE( OnCreate )
        MSG_WM_DESTROY( OnDestroy )
		MSG_WM_TIMER( OnTimer )
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnPaint( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled );
	void	DoPaint(CDCHandle dcc);
	LRESULT OnCreate( LPCREATESTRUCT lpcs );
	void	OnDestroy();
	void	OnTimer( UINT_PTR wParam );
	LRESULT	ss( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled );
};

