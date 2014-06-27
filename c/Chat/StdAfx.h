// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__DF203814_6067_47F1_917B_94B530E1E8AA__INCLUDED_)
#define AFX_STDAFX_H__DF203814_6067_47F1_917B_94B530E1E8AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#define WM_SERVER_MESSAGE (WM_USER+100)
#define WM_CLIENT_MESSAGE (WM_USER+201)
#define MAX_BUF 1024

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#include <time.h>
#include <WINSOCK2.H>

#pragma comment(lib,"WS2_32.lib")

#endif // _AFX_NO_AFXCMN_SUPPORT


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__DF203814_6067_47F1_917B_94B530E1E8AA__INCLUDED_)
