// Num.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CanvasX2.h"
#include "Num.h"
#include "afxdialogex.h"
#include <iostream>

// CNum �Ի���
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


// CNum ��Ϣ�������

void CNum::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
	CString t1;
	((CEdit*) GetDlgItem(IDC_EDIT1))->GetWindowText(t1);
	if(t1==""){
		MessageBox(_T("������������"),_T("����"), MB_ICONEXCLAMATION);
	}else{
		std::string s1;
		s1 = CStringA(t1);

		int i1;
		char* c = new char[10];
		strcpy_s(c,(s1.length()+1),s1.data());
		i1 = atoi(c);
		if(i1<3){
			MessageBox(_T("���������3��"),_T("����"), MB_ICONEXCLAMATION);
		}else{
			num=i1;
		}
	}
}
