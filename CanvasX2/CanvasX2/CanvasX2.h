
// CanvasX2.h : CanvasX2 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CCanvasX2App:
// 有关此类的实现，请参阅 CanvasX2.cpp
//

class CCanvasX2App : public CWinApp
{
public:
	CCanvasX2App();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBlack();
	afx_msg void OnRed();
	afx_msg void OnBlue();
	afx_msg void OnYellow();
	afx_msg void OnCself();
	afx_msg void OnSize1();
	afx_msg void OnSize2();
	afx_msg void OnSize3();
	afx_msg void OnSizeSelf();
	afx_msg void OnB3();
	afx_msg void OnB4();
	afx_msg void OnB5();
	afx_msg void OnB6();
	afx_msg void OnBself();
};

extern CCanvasX2App theApp;
