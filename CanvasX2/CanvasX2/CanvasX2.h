
// CanvasX2.h : CanvasX2 Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CCanvasX2App:
// �йش����ʵ�֣������ CanvasX2.cpp
//

class CCanvasX2App : public CWinApp
{
public:
	CCanvasX2App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
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
