// DigitalClockDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DigitalClock.h"
#include "DigitalClockDlg.h"
#include <stdio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define N 15
extern unsigned char ascii[][16];

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CDigitalClockDlg 对话框




CDigitalClockDlg::CDigitalClockDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDigitalClockDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDigitalClockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDigitalClockDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_WM_TIMER()
END_MESSAGE_MAP()


// CDigitalClockDlg 消息处理程序

BOOL CDigitalClockDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    RECT client, window;
    GetClientRect(&client);
    GetWindowRect(&window);
    int dx = (window.right - window.left) - ((client.right - client.left));
    int dy = (window.bottom - window.top) - ((client.bottom - client.top));
    MoveWindow(0, 0, N * 8 * 8 + dx, N * 16 + dy);

    SetTimer(1, 100, NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDigitalClockDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDigitalClockDlg::OnPaint()
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
        CPaintDC dc(this);
        Draw(&dc);
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CDigitalClockDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDigitalClockDlg::PutChar(CDC *pDC, int x, int y, char ch)
{
    for(int i = 0; i < 16; i++)
    {
        int c = ascii[ch][i];
        for (int j = 0; j < 8; j++)
            if (c & (1 << (7 - j)))
                pDC->Rectangle((x + j) * N, (y + i) * N, 
                    (x + j + 1) * N - 1, (y + i + 1) * N - 1);
    }
}

void CDigitalClockDlg::PutString(CDC *pDC, int x, int y, char *str)
{
    for (char *p = str; *p != '\0'; p++)
    {
        PutChar(pDC, x, y, *p);
        x += 8;
    }
}

void CDigitalClockDlg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值    
    CClientDC dc(this);
    Draw(&dc);

    CDialog::OnTimer(nIDEvent);
}

void CDigitalClockDlg::Draw(CDC *pDC)
{    
    SYSTEMTIME st;
    char strTime[10];
    GetLocalTime(&st);
    sprintf_s(strTime, 10, "%.2d:%.2d:%.2d", st.wHour, st.wMinute, st.wSecond);

    int width = 64 * N;
    int height = 16 * N;
    CDC MemDC;
    MemDC.CreateCompatibleDC(pDC);
    CBitmap MemBitmap;
    MemBitmap.CreateCompatibleBitmap(pDC, width, height);
    MemDC.SelectObject(MemBitmap);
    MemDC.FillSolidRect(0, 0, width, height, RGB(0, 0, 0));
    PutString(&MemDC, 0, 0, strTime);
    pDC->BitBlt(0, 0, width, height, &MemDC, 0, 0, SRCCOPY); 
    MemBitmap.DeleteObject();
    MemDC.DeleteDC();
}
