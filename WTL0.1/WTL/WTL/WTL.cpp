// WTL.cpp : main source file for WTL.exe
//

#include "stdafx.h"
#include "resource.h"

#include "WTLView.h"
#include "aboutdlg.h"
#include "MainFrm.h"

// CAppModule _Module可以看做是MFC程序的应用程序类对象，起着初始化和建立消息循环的作用
CAppModule _Module;

// Run函数的主要作用是创建主框架窗口，进入消息循环
int Run(LPTSTR /*lpstrCmdLine*/ = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
	CMessageLoop theLoop;					// 消息循环类
	_Module.AddMessageLoop(&theLoop);		// 保存全局应用theLoop

	CMainFrame wndMain;

	if(wndMain.CreateEx() == NULL)
	{
		ATLTRACE(_T("Main window creation failed!\n"));
		return 0;
	}

	wndMain.ShowWindow(nCmdShow);

	int nRet = theLoop.Run();				// 不断的从消息队列里取消息，然后分发给对应的窗口

	_Module.RemoveMessageLoop();
	return nRet;
}

// 初始化COM环境，公用控件和_Module，调用全局函数Run()
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
	HRESULT hRes = ::CoInitialize(NULL);	// 初始化COM环境
// If you are running on NT 4.0 or higher you can use the following call instead to 
// make the EXE free threaded. This means that calls come in on a random RPC thread.
//	HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	ATLASSERT(SUCCEEDED(hRes));

	// this resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used
	::DefWindowProc(NULL, 0, 0, 0L);		// ?

	AtlInitCommonControls(ICC_BAR_CLASSES);	// add flags to support other controls

	hRes = _Module.Init(NULL, hInstance);	// 应用程序初始化
	ATLASSERT(SUCCEEDED(hRes));

	int nRet = Run(lpstrCmdLine, nCmdShow);	

	_Module.Term();							// 销毁应用程序
	::CoUninitialize();						// COM环境销毁

	return nRet;
}
