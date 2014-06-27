// WatchThread.cpp : implementation file
//

#include "stdafx.h"
#include "CWinThread.h"
#include "WatchThread.h"
#include "CWinThreadDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWatchThread

IMPLEMENT_DYNCREATE(CWatchThread, CWinThread)

CWatchThread::CWatchThread()
{
}

CWatchThread::~CWatchThread()
{
}

BOOL CWatchThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CWatchThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CWatchThread, CWinThread)
	//{{AFX_MSG_MAP(CWatchThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWatchThread message handlers

int CWatchThread::Run() 
{
	// TODO: Add your specialized code here and/or call the base class
	static int i=0;
	CCWinThreadDlg *dlg=(CCWinThreadDlg *)AfxGetMainWnd();
	CString s;
	
	while (1)
	{		
		s.Format("%.4d",i);
		SetDlgItemText(dlg->m_hWnd,IDC_EDIT1,s);
		Sleep(1);
		i++;
	}
	return CWinThread::Run();
}
