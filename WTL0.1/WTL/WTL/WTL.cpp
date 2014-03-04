// WTL.cpp : main source file for WTL.exe
//

#include "stdafx.h"
#include "resource.h"

#include "WTLView.h"
#include "aboutdlg.h"
#include "MainFrm.h"

// CAppModule _Module���Կ�����MFC�����Ӧ�ó�����������ų�ʼ���ͽ�����Ϣѭ��������
CAppModule _Module;

// Run��������Ҫ�����Ǵ�������ܴ��ڣ�������Ϣѭ��
int Run(LPTSTR /*lpstrCmdLine*/ = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
	CMessageLoop theLoop;					// ��Ϣѭ����
	_Module.AddMessageLoop(&theLoop);		// ����ȫ��Ӧ��theLoop

	CMainFrame wndMain;

	if(wndMain.CreateEx() == NULL)
	{
		ATLTRACE(_T("Main window creation failed!\n"));
		return 0;
	}

	wndMain.ShowWindow(nCmdShow);

	int nRet = theLoop.Run();				// ���ϵĴ���Ϣ������ȡ��Ϣ��Ȼ��ַ�����Ӧ�Ĵ���

	_Module.RemoveMessageLoop();
	return nRet;
}

// ��ʼ��COM���������ÿؼ���_Module������ȫ�ֺ���Run()
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
	HRESULT hRes = ::CoInitialize(NULL);	// ��ʼ��COM����
// If you are running on NT 4.0 or higher you can use the following call instead to 
// make the EXE free threaded. This means that calls come in on a random RPC thread.
//	HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	ATLASSERT(SUCCEEDED(hRes));

	// this resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used
	::DefWindowProc(NULL, 0, 0, 0L);		// ?

	AtlInitCommonControls(ICC_BAR_CLASSES);	// add flags to support other controls

	hRes = _Module.Init(NULL, hInstance);	// Ӧ�ó����ʼ��
	ATLASSERT(SUCCEEDED(hRes));

	int nRet = Run(lpstrCmdLine, nCmdShow);	

	_Module.Term();							// ����Ӧ�ó���
	::CoUninitialize();						// COM��������

	return nRet;
}
