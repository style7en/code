// DigitalClock.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDigitalClockApp:
// �йش����ʵ�֣������ DigitalClock.cpp
//

class CDigitalClockApp : public CWinApp
{
public:
	CDigitalClockApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDigitalClockApp theApp;