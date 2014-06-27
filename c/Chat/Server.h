// Server.h: interface for the CServer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERVER_H__AC9C0AE5_DED7_4386_B4F7_2E2696362A2E__INCLUDED_)
#define AFX_SERVER_H__AC9C0AE5_DED7_4386_B4F7_2E2696362A2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CServer  
{
public:
	CServer();
	virtual ~CServer();

	SOCKET m_hSocket;
	SOCKADDR_IN m_addr;
	UINT m_iPort;
	HWND m_hWnd;

	BOOL Listen(HWND hwnd,UINT port);
};

#endif // !defined(AFX_SERVER_H__AC9C0AE5_DED7_4386_B4F7_2E2696362A2E__INCLUDED_)
