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
#define _WTL_USE_CSTRING		// ʹ��CString��

#include <atlbase.h>			// ������ATL��
#include <atlapp.h>				// ������WTL��

extern CAppModule _Module;		// WTL ������CComModule�汾,CAppModule�Ǵ�CComModule��������

#include <atlwin.h>				// ATL ������	
#include <atlcom.h>
#include <atlhost.h>
#include <atlctl.h>
#include <atlimage.h>			// CImage

#include <atlframe.h>			// WTL ����ܴ�����
#include <atlmisc.h>			// WTL ʵ�ù����࣬���磺CString
#include <atlcrack.h>			// WTL ��ǿ����Ϣ��
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
