
// homework_server.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Chomework_serverApp:
// �йش����ʵ�֣������ homework_server.cpp
//

class Chomework_serverApp : public CWinApp
{
public:
	Chomework_serverApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Chomework_serverApp theApp;