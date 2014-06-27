// Client.h: interface for the CClient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIENT_H__AA19F94A_1C1F_44AF_B5BB_37B304535F56__INCLUDED_)
#define AFX_CLIENT_H__AA19F94A_1C1F_44AF_B5BB_37B304535F56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CClient  
{
public:
	CClient();
	virtual ~CClient();

	CString m_strServer;
	SOCKET m_hSocket;
	HWND m_hWnd;
	UINT m_iPort;
	SOCKADDR_IN m_addr;

	void Connect(HWND hwnd,UINT port, CString strserver);

};

#endif // !defined(AFX_CLIENT_H__AA19F94A_1C1F_44AF_B5BB_37B304535F56__INCLUDED_)
