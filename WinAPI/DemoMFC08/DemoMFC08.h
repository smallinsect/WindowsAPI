﻿
// DemoMFC08.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CDemoMFC08App:
// 有关此类的实现，请参阅 DemoMFC08.cpp
//

class CDemoMFC08App : public CWinApp
{
public:
	CDemoMFC08App();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CDemoMFC08App theApp;
