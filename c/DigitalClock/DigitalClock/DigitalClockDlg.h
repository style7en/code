// DigitalClockDlg.h : ͷ�ļ�
//

#pragma once


// CDigitalClockDlg �Ի���
class CDigitalClockDlg : public CDialog
{
// ����
public:
	CDigitalClockDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DIGITALCLOCK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

    void PutChar(CDC *pDC, int x, int y, char ch);
    void PutString(CDC *pDC, int x, int y, char *str);
    void Draw(CDC *pDC);

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnTimer(UINT_PTR nIDEvent);
};
