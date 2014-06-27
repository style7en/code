// CWinThreadDlg.h : header file
//

#if !defined(AFX_CWINTHREADDLG_H__E0304AF9_F486_42FA_B8D3_B0610F937117__INCLUDED_)
#define AFX_CWINTHREADDLG_H__E0304AF9_F486_42FA_B8D3_B0610F937117__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCWinThreadDlg dialog

class CCWinThreadDlg : public CDialog
{
// Construction
public:
	CCWinThreadDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCWinThreadDlg)
	enum { IDD = IDD_CWINTHREAD_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCWinThreadDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCWinThreadDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CWINTHREADDLG_H__E0304AF9_F486_42FA_B8D3_B0610F937117__INCLUDED_)
