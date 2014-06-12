// DigitalClockDlg.h : 头文件
//

#pragma once


// CDigitalClockDlg 对话框
class CDigitalClockDlg : public CDialog
{
// 构造
public:
	CDigitalClockDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DIGITALCLOCK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

    void PutChar(CDC *pDC, int x, int y, char ch);
    void PutString(CDC *pDC, int x, int y, char *str);
    void Draw(CDC *pDC);

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnTimer(UINT_PTR nIDEvent);
};
