// MFC��MP3������.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCMP3App:
// �йش����ʵ�֣������ MFC��MP3������.cpp
//

class CMFCMP3App : public CWinApp
{
public:
	CMFCMP3App();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCMP3App theApp;