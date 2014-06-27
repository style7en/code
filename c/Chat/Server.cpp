// Server.cpp: implementation of the CServer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Chat.h"
#include "Server.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CServer::CServer()
{
	m_hSocket=NULL;
}

CServer::~CServer()
{
	WSAAsyncSelect(m_hSocket,m_hWnd,0,0);
}

BOOL CServer::Listen(HWND hwnd,UINT port)
{
	if(m_hSocket!=NULL)
	{
		closesocket(m_hSocket);
		m_hSocket=NULL;
	}

	m_hWnd=hwnd;
	m_iPort=port;
	m_hSocket=socket(AF_INET,SOCK_STREAM,0);
	
	WSAAsyncSelect(m_hSocket,m_hWnd,WM_SERVER_MESSAGE, FD_ACCEPT|FD_READ|FD_CLOSE);
	
	m_addr.sin_family=AF_INET;
	m_addr.sin_port=htons(m_iPort);
	m_addr.sin_addr.S_un.S_addr=INADDR_ANY;

	if(bind(m_hSocket,(SOCKADDR *)&m_addr,sizeof(m_addr))==SOCKET_ERROR)
	{
		AfxMessageBox("Binding Error");
		return FALSE;
	}

	if(listen(m_hSocket,5)==SOCKET_ERROR)
	{
		AfxMessageBox("Listening Error");
		return FALSE;
	}

	return TRUE;
}
