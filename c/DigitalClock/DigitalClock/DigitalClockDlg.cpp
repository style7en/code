// DigitalClockDlg.cpp : ʵ���ļ�
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

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CDigitalClockDlg �Ի���




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


// CDigitalClockDlg ��Ϣ�������

BOOL CDigitalClockDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
    RECT client, window;
    GetClientRect(&client);
    GetWindowRect(&window);
    int dx = (window.right - window.left) - ((client.right - client.left));
    int dy = (window.bottom - window.top) - ((client.bottom - client.top));
    MoveWindow(0, 0, N * 8 * 8 + dx, N * 16 + dy);

    SetTimer(1, 100, NULL);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDigitalClockDlg::OnPaint()
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
        CPaintDC dc(this);
        Draw(&dc);
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
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
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ    
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
