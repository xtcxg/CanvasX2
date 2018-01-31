// Num.cpp : 实现文件
//

#include "stdafx.h"
#include "CanvasX2.h"
#include "Num.h"
#include "afxdialogex.h"
#include <iostream>

// CNum 对话框
IMPLEMENT_DYNAMIC(CNum, CDialogEx)

CNum::CNum(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNum::IDD, pParent)
{

}

CNum::~CNum()
{
}

void CNum::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNum, CDialogEx)
	ON_BN_CLICKED(IDOK, &CNum::OnBnClickedOk)
END_MESSAGE_MAP()


// CNum 消息处理程序

void CNum::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	CString t1;
	((CEdit*) GetDlgItem(IDC_EDIT1))->GetWindowText(t1);
	if(t1==""){
		MessageBox(_T("请输入完整！"),_T("警告"), MB_ICONEXCLAMATION);
	}else{
		std::string s1;
		s1 = CStringA(t1);

		int i1;
		char* c = new char[10];
		strcpy_s(c,(s1.length()+1),s1.data());
		i1 = atoi(c);
		if(i1<3){
			MessageBox(_T("请输入大于3！"),_T("警告"), MB_ICONEXCLAMATION);
		}else{
			num=i1;
		}
	}
}
