// TCLDlg.h : ͷ�ļ�
//

#pragma once


// CTCLDlg �Ի���
class CTCLDlg : public CDialog
{
// ����
public:
	CTCLDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TCL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButtonOpen();
public:
    afx_msg void OnBnClickedButtonSend();
};
