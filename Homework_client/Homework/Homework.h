
// Homework.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CHomeworkApp:
// �йش����ʵ�֣������ Homework.cpp
//

class CHomeworkApp : public CWinApp
{
public:
	CHomeworkApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CHomeworkApp theApp;