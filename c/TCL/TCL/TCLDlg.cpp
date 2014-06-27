// TCLDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TCL.h"
#include "TCLDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTCLDlg 对话框




CTCLDlg::CTCLDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTCLDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTCLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTCLDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BUTTON_OPEN, &CTCLDlg::OnBnClickedButtonOpen)
    ON_BN_CLICKED(IDC_BUTTON_SEND, &CTCLDlg::OnBnClickedButtonSend)
END_MESSAGE_MAP()


// CTCLDlg 消息处理程序

BOOL CTCLDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTCLDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CTCLDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTCLDlg::OnBnClickedButtonOpen()
{
    // TODO: 在此添加控件通知处理程序代码
    //打开文本文件
    CFileDialog dlg(TRUE);
    if (dlg.DoModal())
    {        
        CString strFileName(dlg.GetPathName());
        SetDlgItemText(IDC_EDIT_FILE_NAME, strFileName);

        CString content;
        CFile file(strFileName, CFile::modeRead);        
        file.Read(content.GetBufferSetLength((int)file.GetLength()), (UINT)file.GetLength());
        file.Close();
        content.ReleaseBuffer();
        
        SetDlgItemText(IDC_EDIT_CONTENT, content);
    }
}

void CTCLDlg::OnBnClickedButtonSend()
{
    // TODO: 在此添加控件通知处理程序代码
    CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT_CONTENT);

    //获取光标所在的行号
    int current_line = pEdit->LineFromChar(pEdit->LineIndex());
    
    //获取行内容
    CString content;
    int length = pEdit->LineLength();
    if (length != 0)
    {
        pEdit->GetLine(current_line, content.GetBufferSetLength(length), length);
        content.ReleaseBuffer();
    }
    
    //发送
    MessageBox(content);

    //光标移动到下一行
    //pEdit->SetCaretPos(CPoint(3, 3));
}
