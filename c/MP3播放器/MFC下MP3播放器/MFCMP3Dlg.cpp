// MFC下MP3播放器Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCMP3.h"
#include "MFCMP3Dlg.h"
#include <Digitalv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define FILE_PATH_SUB_ITEM 0 //记录文件路径的列数
#define ID_TIMER 1

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


// CMFCMP3Dlg 对话框




CMFCMP3Dlg::CMFCMP3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMFCMP3Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    // 初始化
    m_PlayingStatusInfo.DeviceId = INVALID_DEVICE_ID;
    m_PlayingStatusInfo.PlayStatus = INVALID;
    m_PlayingStatusInfo.CurrentIndex = -1;
    m_PlayingStatusInfo.PlayStep = 0;
    m_PlayingStatusInfo.Volume = 700; //初始音量设置为70%

    m_Bitmap_Play = ::LoadBitmap(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_PLAY));
    m_Bitmap_Pause = ::LoadBitmap(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_PAUSE));
    m_Bitmap_NoMute = ::LoadBitmap(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_NO_MUTE));
    m_Bitmap_Mute = ::LoadBitmap(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_MUTE));
}

void CMFCMP3Dlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_PLAYLIST, m_ListCtrl_PlayList);
    DDX_Control(pDX, IDC_BUTTON_PLAY_PAUSE, m_Button_PlayPause);
    DDX_Control(pDX, IDC_STATIC_INFO, m_Static_Info);
    DDX_Control(pDX, IDC_SLIDER_STATUS, m_Slider_PlayStep);
    DDX_Control(pDX, IDC_SLIDER_VOLUME, m_Slider_Volume);
    DDX_Control(pDX, IDC_STATIC_STEP, m_StaticStep);
}

BEGIN_MESSAGE_MAP(CMFCMP3Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_NOTIFY(NM_RCLICK, IDC_LIST_PLAYLIST, &CMFCMP3Dlg::OnNMRclickListPlaylist)
    ON_BN_CLICKED(IDC_BUTTON_PLAY_PAUSE, &CMFCMP3Dlg::OnBnClickedButtonPlayPause)
    ON_COMMAND(ID_POPUP_ADD_FILE, &CMFCMP3Dlg::OnPopupAddFile)
    ON_COMMAND(ID_POPUP_DEL_FILE, &CMFCMP3Dlg::OnPopupDelFile)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST_PLAYLIST, &CMFCMP3Dlg::OnNMDblclkListPlaylist)
    ON_BN_CLICKED(IDC_BUTTON_MUTE, &CMFCMP3Dlg::OnBnClickedButtonMute)
    ON_BN_CLICKED(IDC_BUTTON_PREV, &CMFCMP3Dlg::OnBnClickedButtonPrev)
    ON_BN_CLICKED(IDC_BUTTON_NEXT, &CMFCMP3Dlg::OnBnClickedButtonNext)
    ON_COMMAND(ID_POPUP_OPEN_PLAYLIST_FILE, &CMFCMP3Dlg::OnPopupOpenPlaylistFile)
    ON_COMMAND(ID_POPUP_SAVE_PLAYLIST_FILE, &CMFCMP3Dlg::OnPopupSavePlaylistFile)
    ON_WM_TIMER()
    ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_STATUS, &CMFCMP3Dlg::OnNMReleasedcaptureSliderStatus)
    ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_VOLUME, &CMFCMP3Dlg::OnNMReleasedcaptureSliderVolume)
END_MESSAGE_MAP()


// CMFCMP3Dlg 消息处理程序

BOOL CMFCMP3Dlg::OnInitDialog()
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
    InitListCtrl();
    InitButton();
    m_Slider_Volume.SetRange(0, 1000);
    m_Slider_Volume.SetPos(700);

	return FALSE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCMP3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCMP3Dlg::OnPaint()
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
HCURSOR CMFCMP3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

DWORD CMFCMP3Dlg::Play(CString strFileName, DWORD Start)
{
    DWORD Ret = OK;
    
    // 关闭之前打开的
    if (m_PlayingStatusInfo.DeviceId != INVALID_DEVICE_ID)
        mciSendCommand(m_PlayingStatusInfo.DeviceId, MCI_CLOSE, 0, 0);
    
    // 打开多媒体
    MCI_OPEN_PARMS mciOpenParms = {0};
    mciOpenParms.lpstrElementName = strFileName.GetBuffer();
    Ret = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_WAIT, (DWORD)&mciOpenParms);
    if (Ret != OK)
    {
        MessageBox(TEXT("open mci fail"));
        return Ret;
    }
    m_PlayingStatusInfo.DeviceId = mciOpenParms.wDeviceID;

    //设置音量
    SetVolume(m_PlayingStatusInfo.Volume);
    
    // 播放MP3
    MCI_PLAY_PARMS mciPlayParms = {0};
    mciPlayParms.dwFrom = Start * 1000;
    Ret = mciSendCommand(m_PlayingStatusInfo.DeviceId, MCI_PLAY, MCI_FROM | MCI_NOTIFY, (DWORD)&mciPlayParms);
    if (Ret != OK)
    {
        MessageBox(TEXT("play mci fail"));
        return Ret;
    }
    
    // 获取MP3长度
    if (Start == 0)
    {
        MCI_STATUS_PARMS mciStatusParms = {0};
        mciStatusParms.dwItem = MCI_STATUS_LENGTH;
        mciSendCommand(m_PlayingStatusInfo.DeviceId, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM,(DWORD)&mciStatusParms);//关键,取得长度
        DWORD mSecond = (int)mciStatusParms.dwReturn;
        m_PlayingStatusInfo.CurrentLength = mSecond / 1000 + 1;
    }
    
    m_PlayingStatusInfo.PlayStep = Start;
    m_Slider_PlayStep.SetRange(0, m_PlayingStatusInfo.CurrentLength);
    m_Slider_PlayStep.SetPos(Start);
    SetTimer(ID_TIMER, 1000, NULL);

    return OK;
}

DWORD CMFCMP3Dlg::Pause()
{
    DWORD Ret = OK;

    Ret = mciSendCommand(m_PlayingStatusInfo.DeviceId, MCI_PAUSE, 0, 0);
    if (Ret != OK)
    {
        MessageBox(TEXT("pause mci fail"));
        return Ret;
    }
    
    KillTimer(ID_TIMER);
    return OK;
}

DWORD CMFCMP3Dlg::Resume()
{
    DWORD Ret = OK;

    Ret = mciSendCommand(m_PlayingStatusInfo.DeviceId, MCI_RESUME, 0, 0);
    if (Ret != OK)
    {
        MessageBox(TEXT("resume mci fail"));
        return Ret;
    }
    
    SetTimer(ID_TIMER, 1000, NULL);
    return OK;
}

void CMFCMP3Dlg::InitListCtrl()
{
    m_ListCtrl_PlayList.SetExtendedStyle(LVS_EX_FULLROWSELECT);

    CRect ListRect;
    m_ListCtrl_PlayList.GetClientRect(&ListRect);
    int ListWidth = ListRect.Width();
    m_ListCtrl_PlayList.InsertColumn(FILE_PATH_SUB_ITEM, TEXT("歌曲"), LVCFMT_LEFT, ListWidth * 4 / 5);
}

void CMFCMP3Dlg::InitButton()
{
    ((CButton *)GetDlgItem(IDC_BUTTON_NEXT))->SetBitmap(::LoadBitmap(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_NEXT)));
    ((CButton *)GetDlgItem(IDC_BUTTON_PREV))->SetBitmap(::LoadBitmap(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_PREV)));
    ((CButton *)GetDlgItem(IDC_BUTTON_MUTE))->SetBitmap(m_Bitmap_NoMute);
    m_Button_PlayPause.SetBitmap(m_Bitmap_Play);
}

void CMFCMP3Dlg::UpdateStatus()
{
    int item = m_ListCtrl_PlayList.GetHotItem();
    if (m_PlayingStatusInfo.PlayStatus == PLAYING)
    {
        m_Button_PlayPause.SetBitmap(m_Bitmap_Pause);

        CString str;
        str.Format(TEXT("正在播放\n%s"), 
            m_ListCtrl_PlayList.GetItemText(m_PlayingStatusInfo.CurrentIndex, FILE_PATH_SUB_ITEM));
        m_Static_Info.SetWindowText(str);
        
        //选中正在播放歌曲,其余取消选中
        m_ListCtrl_PlayList.SetFocus();
        for (int i = 0; i < (int)m_ListCtrl_PlayList.GetItemCount(); i++)
            m_ListCtrl_PlayList.SetItemState(i, 0, LVIS_SELECTED|LVIS_FOCUSED);
        m_ListCtrl_PlayList.SetItemState(m_PlayingStatusInfo.CurrentIndex, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
    }
    else if (m_PlayingStatusInfo.PlayStatus == PAUSE)
    {
        m_Button_PlayPause.SetBitmap(m_Bitmap_Play);

        CString str;
        str.Format(TEXT("暂停\n%s"), 
            m_ListCtrl_PlayList.GetItemText(m_PlayingStatusInfo.CurrentIndex, FILE_PATH_SUB_ITEM));
        m_Static_Info.SetWindowText(str);
    }
    else 
    {
        m_Button_PlayPause.SetBitmap(m_Bitmap_Play);
        m_Static_Info.SetWindowText(TEXT("请添加歌曲\n"));
    }
}

void CMFCMP3Dlg::SetVolume(int Value)
{
    MCI_DGV_SETAUDIO_PARMS mciSetAudio = {0};
    mciSetAudio.dwValue = Value;
    mciSetAudio.dwItem = MCI_DGV_SETAUDIO_VOLUME;
    mciSendCommand(m_PlayingStatusInfo.DeviceId, 
        MCI_SETAUDIO, MCI_DGV_SETAUDIO_ITEM | MCI_DGV_SETAUDIO_VALUE, (DWORD)&mciSetAudio);

}

void CMFCMP3Dlg::OnPopupAddFile()
{
    CFileDialog dlg(TRUE, 
        TEXT("mp3文件 (*.mp3)"), 
        NULL, 
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT |OFN_ALLOWMULTISELECT|OFN_ENABLESIZING, 
        TEXT("mp3文件 (*.mp3)|*.mp3|wma文件 (*.wma)|*.wma|所有文件 (*.*)|*.*||"),
        NULL);
    if (dlg.DoModal() == IDOK)
    {
        POSITION pos = dlg.GetStartPosition();
        while (pos != NULL)
        {
            CString strPathName = dlg.GetNextPathName(pos);
            int Count = m_ListCtrl_PlayList.GetItemCount();
            m_ListCtrl_PlayList.InsertItem(Count, strPathName);
        }            
    }
}

void CMFCMP3Dlg::OnPopupDelFile()
{
    while (m_ListCtrl_PlayList.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED) != -1)
    {
        int item = m_ListCtrl_PlayList.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
        if (item != m_PlayingStatusInfo.CurrentIndex)
        {
            m_ListCtrl_PlayList.DeleteItem(item);
            if (item < m_PlayingStatusInfo.CurrentIndex)
                m_PlayingStatusInfo.CurrentIndex--;
        }
        else //没有这句会陷入死循环            
            m_ListCtrl_PlayList.SetItemState(item, 0, LVIS_SELECTED|LVIS_FOCUSED);
    }
}


void CMFCMP3Dlg::OnNMRclickListPlaylist(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO: 在此添加控件通知处理程序代码
    CPoint pt;
    GetCursorPos(&pt);

    CMenu PopMenu, *ListMenu;
    PopMenu.LoadMenu(IDR_MENU_POPUP);
    ListMenu = PopMenu.GetSubMenu(0);
    ListMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
    *pResult = 0;
}


void CMFCMP3Dlg::OnNMDblclkListPlaylist(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO: 在此添加控件通知处理程序代码
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    if(pNMListView->iItem != -1)
    {
        CString strPathName = m_ListCtrl_PlayList.GetItemText(pNMListView->iItem, FILE_PATH_SUB_ITEM);
        if (Play(strPathName, 0) == OK)
        {
            m_PlayingStatusInfo.PlayStatus = PLAYING;
            m_PlayingStatusInfo.CurrentIndex = pNMListView->iItem;
            UpdateStatus();
        }

    }
    *pResult = 0;
}


void CMFCMP3Dlg::OnBnClickedButtonPlayPause()
{
    // TODO: 在此添加控件通知处理程序代码
    if (m_PlayingStatusInfo.PlayStatus == PLAYING)
    {
        Pause();
        m_PlayingStatusInfo.PlayStatus = PAUSE;
    }
    else if (m_PlayingStatusInfo.PlayStatus == PAUSE)
    {
        Resume();
        m_PlayingStatusInfo.PlayStatus = PLAYING;
    }
    else
    {
        m_PlayingStatusInfo.PlayStatus = INVALID;
    }

    UpdateStatus();
}


void CMFCMP3Dlg::OnBnClickedButtonMute()
{
    static bool flag = true;
    if (flag)
    {
        ((CButton *)GetDlgItem(IDC_BUTTON_MUTE))->SetBitmap(m_Bitmap_Mute);    
        m_Slider_Volume.SetPos(0);  
        SetVolume(0);
        m_Slider_Volume.EnableWindow(FALSE);
    }
    else
    {
        ((CButton *)GetDlgItem(IDC_BUTTON_MUTE))->SetBitmap(m_Bitmap_NoMute);    
        m_Slider_Volume.SetPos(m_PlayingStatusInfo.Volume); 
        SetVolume(m_PlayingStatusInfo.Volume);
        m_Slider_Volume.EnableWindow(TRUE);
    }

    flag = !flag;
}

void CMFCMP3Dlg::OnBnClickedButtonPrev()
{
    if (m_ListCtrl_PlayList.GetItemCount() == 0)
        return ;

    m_PlayingStatusInfo.CurrentIndex--;
    if (m_PlayingStatusInfo.CurrentIndex < 0)
        m_PlayingStatusInfo.CurrentIndex = (int)m_ListCtrl_PlayList.GetItemCount() - 1;

    DWORD Ret = Play(m_ListCtrl_PlayList.GetItemText(m_PlayingStatusInfo.CurrentIndex, FILE_PATH_SUB_ITEM), 0);
    if (Ret == OK)
    {
        m_PlayingStatusInfo.PlayStatus = PLAYING;
        UpdateStatus();        
    }
}

void CMFCMP3Dlg::OnBnClickedButtonNext()
{
    if (m_ListCtrl_PlayList.GetItemCount() == 0)
        return ;

    m_PlayingStatusInfo.CurrentIndex++;
    if (m_PlayingStatusInfo.CurrentIndex > m_ListCtrl_PlayList.GetItemCount() - 1)
        m_PlayingStatusInfo.CurrentIndex = 0;
    
    DWORD Ret = Play(m_ListCtrl_PlayList.GetItemText(m_PlayingStatusInfo.CurrentIndex, FILE_PATH_SUB_ITEM), 0);
    if (Ret == OK)
    {
        m_PlayingStatusInfo.PlayStatus = PLAYING;
        UpdateStatus();
    }
}

void CMFCMP3Dlg::OnPopupOpenPlaylistFile()
{
    // TODO: 在此添加命令处理程序代码
    CFileDialog dlg(TRUE, 
        TEXT("播放列表文件 (*.pl)"), 
        NULL, 
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT |OFN_ENABLESIZING, 
        TEXT("播放列表文件 (*.pl)|*.pl|文本文件 (*.txt)|*.txt|所有文件 (*.*)|*.*||"),
        NULL);
    if (dlg.DoModal() == IDOK)
    {
        m_ListCtrl_PlayList.DeleteAllItems();

        CFile file(dlg.GetPathName(), CFile::modeRead);
        CString str;
        TCHAR c;
        int item_index = 0;
        while (file.Read(&c, sizeof(TCHAR)))
        {
            if (c == TEXT('\n'))
            {
                m_ListCtrl_PlayList.InsertItem(item_index, TEXT(""));
                m_ListCtrl_PlayList.SetItemText(item_index, FILE_PATH_SUB_ITEM, str);
                item_index++;
                str.Empty();
            }
            else
                str += c;
        }
        file.Close();
    }
}

void CMFCMP3Dlg::OnPopupSavePlaylistFile()
{
    // TODO: 在此添加命令处理程序代码
    CFileDialog dlg(FALSE, 
        TEXT("播放列表文件 (*.pl)"), 
        NULL, 
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT |OFN_ENABLESIZING, 
        TEXT("播放列表文件 (*.pl)|*.pl|文本文件 (*.txt)|*.txt|所有文件 (*.*)|*.*||"),
        NULL);
    if (dlg.DoModal() == IDOK)
    {
        const int UNICODE_TXT_FLAG = 0xFEFF;
        CFile file(dlg.GetPathName(), CFile::modeCreate | CFile::modeWrite);
        for (int i = 0; i < (int)m_ListCtrl_PlayList.GetItemCount(); i++)
        {
            CString str = m_ListCtrl_PlayList.GetItemText(i, FILE_PATH_SUB_ITEM);
            str += TEXT("\n");
            file.Write(str.GetBuffer(), str.GetLength() * sizeof(TCHAR));
        }
        file.Close();
    }
}

void CMFCMP3Dlg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    if (m_PlayingStatusInfo.PlayStep >= m_PlayingStatusInfo.CurrentLength)   
    {
        m_PlayingStatusInfo.PlayStep = 0;
        OnBnClickedButtonNext();
    }
    else
    {
        m_PlayingStatusInfo.PlayStep++;
        m_Slider_PlayStep.SetPos(m_PlayingStatusInfo.PlayStep);
        CString str;
        str.Format(TEXT("%02d:%02d/%02d:%02d"), 
            m_PlayingStatusInfo.PlayStep / 60, m_PlayingStatusInfo.PlayStep % 60, 
            m_PlayingStatusInfo.CurrentLength / 60, m_PlayingStatusInfo.CurrentLength % 60);
        m_StaticStep.SetWindowText(str);
    }

    CDialog::OnTimer(nIDEvent);
}

void CMFCMP3Dlg::OnNMReleasedcaptureSliderStatus(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO: 在此添加控件通知处理程序代码
    int PlayFrom = m_Slider_PlayStep.GetPos();
    if (PlayFrom >= m_Slider_PlayStep.GetRangeMax() - 1)
        PlayFrom = m_Slider_PlayStep.GetRangeMax() - 1;
    if (m_PlayingStatusInfo.PlayStatus != INVALID)
    {
        Play(m_ListCtrl_PlayList.GetItemText(m_PlayingStatusInfo.CurrentIndex, FILE_PATH_SUB_ITEM), PlayFrom);
        m_PlayingStatusInfo.PlayStatus = PLAYING;
        UpdateStatus();
    }
    *pResult = 0;
}

void CMFCMP3Dlg::OnNMReleasedcaptureSliderVolume(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO: 在此添加控件通知处理程序代码
    m_PlayingStatusInfo.Volume = m_Slider_Volume.GetPos();
    SetVolume(m_PlayingStatusInfo.Volume);
    m_ListCtrl_PlayList.SetFocus(); //转移焦点，使鼠标中键不能滚动Slidder
    *pResult = 0;
}

BOOL CMFCMP3Dlg::PreTranslateMessage(MSG* pMsg)
{
    // TODO: 在此添加专用代码和/或调用基类
    if(pMsg->message == WM_KEYDOWN)
        if (pMsg->wParam==VK_ESCAPE || pMsg->wParam==VK_RETURN)    //屏蔽回车和ESC  
            return TRUE;     
    return CDialog::PreTranslateMessage(pMsg);
}
