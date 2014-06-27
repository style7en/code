// TCLDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TCL.h"
#include "TCLDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTCLDlg �Ի���




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


// CTCLDlg ��Ϣ�������

BOOL CTCLDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTCLDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CTCLDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTCLDlg::OnBnClickedButtonOpen()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    //���ı��ļ�
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
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT_CONTENT);

    //��ȡ������ڵ��к�
    int current_line = pEdit->LineFromChar(pEdit->LineIndex());
    
    //��ȡ������
    CString content;
    int length = pEdit->LineLength();
    if (length != 0)
    {
        pEdit->GetLine(current_line, content.GetBufferSetLength(length), length);
        content.ReleaseBuffer();
    }
    
    //����
    MessageBox(content);

    //����ƶ�����һ��
    //pEdit->SetCaretPos(CPoint(3, 3));
}
