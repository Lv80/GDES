
// SimpleMFCTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSimpleMFCTestApp:
// �йش����ʵ�֣������ SimpleMFCTest.cpp
//

class CSimpleMFCTestApp : public CWinAppEx
{
public:
	CSimpleMFCTestApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSimpleMFCTestApp theApp;