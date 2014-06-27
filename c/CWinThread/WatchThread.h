#if !defined(AFX_WATCHTHREAD_H__0EDB3A9F_4A0B_483E_B48B_BD17DEBC2776__INCLUDED_)
#define AFX_WATCHTHREAD_H__0EDB3A9F_4A0B_483E_B48B_BD17DEBC2776__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WatchThread.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CWatchThread thread

class CWatchThread : public CWinThread
{
	DECLARE_DYNCREATE(CWatchThread)
protected:
	CWatchThread();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWatchThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CWatchThread();

	// Generated message map functions
	//{{AFX_MSG(CWatchThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WATCHTHREAD_H__0EDB3A9F_4A0B_483E_B48B_BD17DEBC2776__INCLUDED_)
