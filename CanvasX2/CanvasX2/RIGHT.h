#pragma once

#include "CanvasX2View.h"
// RIGHT �Ի���

class RIGHT : public CDialogEx
{
	DECLARE_DYNAMIC(RIGHT)

public:
	RIGHT(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RIGHT();
	BOOL  OnInitDialog();
// �Ի�������
	enum { IDD = IDD_RIGHT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	//CCanvasX2View cv;
	afx_msg void OnBnClickedRadio1();

	afx_msg void OnBnClickedCatch();
	afx_msg void OnBnClickedBack();
	afx_msg void OnBnClickedBush();
	afx_msg void OnBnClickedDel();
	afx_msg void OnBnClickedF();
	afx_msg void OnBnClickedN();
	
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnTRBNThumbPosChangingSlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSlider(NMHDR *pNMHDR, LRESULT *pResult);
};
