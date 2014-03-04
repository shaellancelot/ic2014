// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#pragma once

// Change these values to use different versions
#define WINVER		0x0500
#define _WIN32_WINNT	0x0501
#define _WIN32_IE	0x0501
#define _RICHEDIT_VER	0x0200
#define _WTL_USE_CSTRING		// 使用CString类

#include <atlbase.h>			// 基本的ATL类
#include <atlapp.h>				// 基本的WTL类

extern CAppModule _Module;		// WTL 派生的CComModule版本,CAppModule是从CComModule派生的类

#include <atlwin.h>				// ATL 窗口类	
#include <atlcom.h>
#include <atlhost.h>
#include <atlctl.h>
#include <atlimage.h>			// CImage

#include <atlframe.h>			// WTL 主框架窗口类
#include <atlmisc.h>			// WTL 实用工具类，例如：CString
#include <atlcrack.h>			// WTL 增强的消息宏
#include <atlctrls.h>			// standard and common control classes
#include <atlctrlw.h>			// command bar class
#include <atldlgs.h>			// common dialog classes, property sheet and page classes

#if defined _M_IX86
  #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
  #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
  #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
  #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
