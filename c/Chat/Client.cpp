// Client.cpp: implementation of the CClient class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Chat.h"
#include "Client.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClient::CClient()
{
	m_hSocket=NULL;
}

CClient::~CClient()
{

}

void CClient::Connect(HWND hwnd,UINT port, CString strserver)
{
	if(m_hSocket!=NULL)
	{
		closesocket(m_hSocket);
		m_hSocket=NULL;
	}

	m_hWnd=hwnd;
	m_iPort=port;
	m_strServer=strserver;
	m_hSocket=socket(AF_INET,SOCK_STREAM,0);

	WSAAsyncSelect(m_hSocket,m_hWnd,WM_CLIENT_MESSAGE,FD_READ|FD_CONNECT);

	m_addr.sin_family=AF_INET;
	m_addr.sin_port=htons(m_iPort);
	m_addr.sin_addr.S_un.S_addr=inet_addr(m_strServer.GetBuffer(0));

	connect(m_hSocket,(SOCKADDR *)&m_addr,sizeof(m_addr));

}
