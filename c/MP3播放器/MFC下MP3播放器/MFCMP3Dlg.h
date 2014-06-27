// MFC��MP3������Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include <Mmsystem.h> //��ý��ͷ�ļ�
#include "afxwin.h"
#include "mp3.h"

#pragma comment(lib, "Winmm.lib") //��ý���
#pragma warning(disable:4311) //����4311�澯

typedef struct
{
    DWORD DeviceId; //��ý���豸ID
    PLAT_STATUS PlayStatus; //����״̬����ͣ�����ţ�δ��ʼ��
    int CurrentIndex; //��ǰ���Ÿ���������
    int CurrentLength; //��ǰ���Ÿ����ĳ���
    int PlayStep; //��ǰ���Ÿ����Ľ��ȣ����ŵ��˶�����
    int Volume; //��ǰ������
}PLAYING_STATUS_INFO;

// CMFCMP3Dlg �Ի���
class CMFCMP3Dlg : public CDialog
{
// ����
public:
	CMFCMP3Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCMP3_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


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

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()    
};
