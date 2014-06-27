// ChatDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Chat.h"
#include "ChatDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatDlg dialog

CChatDlg::CChatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChatDlg)
	m_strIP = _T("127.0.0.1");
	m_iPort = 8000;
	m_strSend = _T("");
	m_strUserName = _T("Guest");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strRecv="";
	m_iClientNum=0;
}

void CChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChatDlg)
	DDX_Control(pDX, IDC_EDIT_RECV, m_ctrRecv);
	DDX_Text(pDX, IDC_EDIT_IP, m_strIP);
	DDX_Text(pDX, IDC_EDIT_PORT, m_iPort);
	DDX_Text(pDX, IDC_EDIT_SEND, m_strSend);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_strUserName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CChatDlg, CDialog)
	//{{AFX_MSG_MAP(CChatDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CREATE_SERVER, OnCreateServer)
	ON_BN_CLICKED(IDC_CONNECT_SERVER, OnConnectServer)
	ON_BN_CLICKED(IDC_SEND, OnSend)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_SERVER_MESSAGE,OnServerMessage)
	ON_MESSAGE(WM_CLIENT_MESSAGE,OnClientMessage)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatDlg message handlers

BOOL CChatDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2,2), &wsadata);

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CChatDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CChatDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CChatDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CChatDlg::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN && (pMsg->wParam==VK_ESCAPE))
		return TRUE;
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CChatDlg::OnCreateServer() 
{
	UpdateData();

	CString str;
	GetDlgItemText(IDC_CREATE_SERVER,str);

	if(!str.Compare("Create Server"))
	{		
		if(m_server.Listen(m_hWnd,m_iPort))
		{
			m_strRecv+="Create server suceesed.\r\n";
			m_ctrRecv.SetWindowText(m_strRecv);
			
			SetDlgItemText(IDC_CREATE_SERVER,"Close Server");
			
			GetDlgItem(IDC_CONNECT_SERVER)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_IP)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_PORT)->EnableWindow(FALSE);
			GetDlgItem(IDC_SEND)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SEND)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_USERNAME)->EnableWindow(FALSE);
			
		}	
	}
	else
	{
		closesocket(m_server.m_hSocket);
		m_server.m_hSocket=NULL;
		SetDlgItemText(IDC_CREATE_SERVER,"Create Server");

		GetDlgItem(IDC_CONNECT_SERVER)->EnableWindow();
		GetDlgItem(IDC_EDIT_IP)->EnableWindow();
		GetDlgItem(IDC_EDIT_PORT)->EnableWindow();
		GetDlgItem(IDC_SEND)->EnableWindow();
		GetDlgItem(IDC_EDIT_SEND)->EnableWindow();
		GetDlgItem(IDC_EDIT_USERNAME)->EnableWindow();
	}
}

LRESULT CChatDlg::OnServerMessage(WPARAM wParam,LPARAM lParam)
{
	int i,j;
	SOCKET sock_client;
	char strRecv[MAX_BUF];
	char str[MAX_BUF];
	SYSTEMTIME st;

	memset(strRecv,0,MAX_BUF);
	memset(str,0,MAX_BUF);

	SOCKADDR_IN stemp;
	int len=sizeof stemp;

	switch(WSAGETSELECTEVENT(lParam))
	{
	case FD_ACCEPT:
		sock_client=accept(m_server.m_hSocket,NULL,NULL);		
		getpeername(sock_client,(SOCKADDR *)&stemp,&len);

		sprintf(str,"Some one come into char room, IP:%s,Port:%d.\r\n",inet_ntoa(stemp.sin_addr),ntohs(stemp.sin_port));
		//strcpy(str,"Some one come into char room.\r\n");
		for(i=0;i<m_iClientNum;i++)
		{
			send(m_sockClient[i],str,strlen(str),0);
		}
		m_strRecv+=str;
		m_sockClient[m_iClientNum]=sock_client;
		m_iClientNum++;
		break;

	case FD_READ:
		recv(wParam,str,MAX_BUF,0);

		GetLocalTime(&st);
		sprintf(strRecv,"%.2d:%.2d:%.2d %s",st.wHour,st.wMinute,st.wSecond,str);
		
		for(j=0;j<m_iClientNum;j++)
			send(m_sockClient[j],strRecv,strlen(strRecv),0);
		m_strRecv+=strRecv;	

		break;

	case FD_CLOSE:
		m_strRecv+="Some one leave server.\r\n";
		break;

	default:
		m_strRecv+="An networking error has occured with a client.\r\n";		
		break;
	}

	m_ctrRecv.SetWindowText(m_strRecv);
	m_ctrRecv.LineScroll(m_ctrRecv.GetLineCount());
	return 0;
}

void CChatDlg::OnConnectServer() 
{
	UpdateData();

	CString str;
	GetDlgItemText(IDC_CONNECT_SERVER,str);

	if(!str.Compare("Connect Server"))
	{
		m_client.Connect(m_hWnd,m_iPort,m_strIP);
	}
	else
	{
		closesocket(m_client.m_hSocket);
		m_client.m_hSocket=NULL;

		SetDlgItemText(IDC_CONNECT_SERVER,"Connect Server");

		GetDlgItem(IDC_CREATE_SERVER)->EnableWindow();
		GetDlgItem(IDC_EDIT_IP)->EnableWindow();
		GetDlgItem(IDC_EDIT_PORT)->EnableWindow();
		GetDlgItem(IDC_EDIT_USERNAME)->EnableWindow();
	}
	
}

LRESULT CChatDlg::OnClientMessage(WPARAM wParam,LPARAM lParam)
{
	char strRecv[MAX_BUF];
	char str[MAX_BUF];
	CString s;
	
	memset(strRecv,0,MAX_BUF);
	memset(str,0,MAX_BUF);
	
	switch(WSAGETSELECTEVENT(lParam))
	{	
	case FD_CONNECT:
		if(WSAGETSELECTERROR(lParam))
			MessageBox("Connect server fail");
		else
		{
			SetDlgItemText(IDC_CONNECT_SERVER,"Disconnect Server");
			
			GetDlgItem(IDC_CREATE_SERVER)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_IP)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_PORT)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_USERNAME)->EnableWindow(FALSE);

			m_strRecv+="Connect server successed.\r\n";			
		}
					
		break;

	case FD_READ:
		recv(m_client.m_hSocket,strRecv,MAX_BUF,0);
		m_strRecv+=strRecv;
		break;
		
	default:
		m_strRecv+="An networking error has occured with a client.\r\n";
		break;		
	}

	m_ctrRecv.SetWindowText(m_strRecv);
	m_ctrRecv.LineScroll(m_ctrRecv.GetLineCount());

	return 0;
}

void CChatDlg::OnSend() 
{
	UpdateData();

	if(m_strSend=="")
		return;

	CString str;
	str.Format("%s said: %s\r\n",m_strUserName,m_strSend);
	
	if(send(m_client.m_hSocket,str.GetBuffer(0),str.GetLength(),0)!=SOCKET_ERROR)
	{
		m_strSend="";
		GetDlgItem(IDC_EDIT_SEND)->SetFocus();
		UpdateData(FALSE);
	}
}
