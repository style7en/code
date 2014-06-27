// MFC下MP3播放器Dlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include <Mmsystem.h> //多媒体头文件
#include "afxwin.h"
#include "mp3.h"

#pragma comment(lib, "Winmm.lib") //多媒体库
#pragma warning(disable:4311) //屏蔽4311告警

typedef struct
{
    DWORD DeviceId; //多媒体设备ID
    PLAT_STATUS PlayStatus; //播放状态（暂停，播放，未开始）
    int CurrentIndex; //当前播放歌曲的索引
    int CurrentLength; //当前播放歌曲的长度
    int PlayStep; //当前播放歌曲的进度，播放到了多少秒
    int Volume; //当前的音量
}PLAYING_STATUS_INFO;

// CMFCMP3Dlg 对话框
class CMFCMP3Dlg : public CDialog
{
// 构造
public:
	CMFCMP3Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCMP3_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


    CListCtrl m_ListCtrl_PlayList;
    CButton m_Button_PlayPause;
    CStatic m_Static_Info;
    CStatic m_StaticStep;
    CSliderCtrl m_Slider_PlayStep;
    CSliderCtrl m_Slider_Volume;

    PLAYING_STATUS_INFO m_PlayingStatusInfo;

    HBITMAP m_Bitmap_Play;
    HBITMAP m_Bitmap_Pause;
    HBITMAP m_Bitmap_Mute;
    HBITMAP m_Bitmap_NoMute;

    DWORD Play(CString strFileName, DWORD Start);
    DWORD Pause();
    DWORD Resume();
    void InitListCtrl();
    void InitButton();
    void UpdateStatus();
    void SetVolume(int Value);
    afx_msg void OnNMRclickListPlaylist(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedButtonPlayPause();
    afx_msg void OnPopupAddFile();
    afx_msg void OnPopupDelFile();
    afx_msg void OnNMDblclkListPlaylist(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedButtonMute();
    afx_msg void OnBnClickedButtonPrev();
    afx_msg void OnBnClickedButtonNext();
    afx_msg void OnPopupOpenPlaylistFile();
    afx_msg void OnPopupSavePlaylistFile();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnNMReleasedcaptureSliderStatus(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMReleasedcaptureSliderVolume(NMHDR *pNMHDR, LRESULT *pResult);
    virtual BOOL PreTranslateMessage(MSG* pMsg);

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()    
};
