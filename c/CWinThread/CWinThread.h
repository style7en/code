// CWinThread.h : main header file for the CWINTHREAD application
//

#if !defined(AFX_CWINTHREAD_H__258B0D42_CCE4_43F5_9FD7_9C955F9B826C__INCLUDED_)
#define AFX_CWINTHREAD_H__258B0D42_CCE4_43F5_9FD7_9C955F9B826C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCWinThreadApp:
// See CWinThread.cpp for the implementation of this class
//

class CCWinThreadApp : public CWinApp
{
public:
	CCWinThreadApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCWinThreadApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCWinThreadApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CWINTHREAD_H__258B0D42_CCE4_43F5_9FD7_9C955F9B826C__INCLUDED_)
