// ChatDlg.h : header file
//

#if !defined(AFX_CHATDLG_H__F6F2EE49_2111_4469_8EA1_D20A24E1C813__INCLUDED_)
#define AFX_CHATDLG_H__F6F2EE49_2111_4469_8EA1_D20A24E1C813__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Server.h"
#include "Client.h"
#define MAX_CLIENT 100

/////////////////////////////////////////////////////////////////////////////
// CChatDlg dialog

class CChatDlg : public CDialog
{
// Construction
public:
	CChatDlg(CWnd* pParent = NULL);	// standard constructor
	afx_msg LRESULT OnServerMessage(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnClientMessage(WPARAM wParam,LPARAM lParam);

	CServer m_server;
	CString m_strRecv;
	SOCKET m_sockClient[MAX_CLIENT];
	int m_iClientNum;

	CClient m_client;
// Dialog Data
	//{{AFX_DATA(CChatDlg)
	enum { IDD = IDD_CHAT_DIALOG };
	CEdit	m_ctrRecv;
	CString	m_strIP;
	UINT	m_iPort;
	CString	m_strSend;
	CString	m_strUserName;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CChatDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCreateServer();
	afx_msg void OnConnectServer();
	afx_msg void OnSend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATDLG_H__F6F2EE49_2111_4469_8EA1_D20A24E1C813__INCLUDED_)
