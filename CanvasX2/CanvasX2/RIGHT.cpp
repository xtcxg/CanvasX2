// RIGHT.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CanvasX2.h"
#include "RIGHT.h"
#include "afxdialogex.h"
#include "CanvasX2View.h"

// RIGHT �Ի���

IMPLEMENT_DYNAMIC(RIGHT, CDialog)

RIGHT::RIGHT(CWnd* pParent /*=NULL*/)
	: CDialogEx(RIGHT::IDD, pParent)
{

}

RIGHT::~RIGHT()
{
}

void RIGHT::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}
BOOL RIGHT::OnInitDialog(){
	CSliderCtrl *pSlidCtrl=(CSliderCtrl*)GetDlgItem(IDC_SLIDER);
	pSlidCtrl->SetRange(3,13,TRUE);//���û�������Χ
	pSlidCtrl->SetPos(0);//���û�����λ��
	return true;
}

BEGIN_MESSAGE_MAP(RIGHT, CDialog)
	
	ON_BN_CLICKED(IDC_RADIO1, &RIGHT::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_CATCH, &RIGHT::OnBnClickedCatch)
	ON_BN_CLICKED(IDC_BACK, &RIGHT::OnBnClickedBack)
	ON_BN_CLICKED(IDC_BUSH, &RIGHT::OnBnClickedBush)
	ON_BN_CLICKED(IDC_DEL, &RIGHT::OnBnClickedDel)
	ON_BN_CLICKED(IDC_F, &RIGHT::OnBnClickedF)
	ON_BN_CLICKED(IDC_N, &RIGHT::OnBnClickedN)
	ON_BN_CLICKED(IDC_RADIO2, &RIGHT::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &RIGHT::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &RIGHT::OnBnClickedRadio4)
	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDER, &RIGHT::OnTRBNThumbPosChangingSlider)

	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER, &RIGHT::OnNMReleasedcaptureSlider)
END_MESSAGE_MAP()

// RIGHT ��Ϣ�������

void RIGHT::OnBnClickedRadio1()
{
	HWND hWnd = ::FindWindow(NULL, _T("CanvasX2 - canvas"));
	::PostMessage(hWnd,WM_COMMAND,ID_SIZE_1,0);
}

void RIGHT::OnBnClickedRadio2()
{
	HWND hWnd = ::FindWindow(NULL, _T("CanvasX2 - canvas"));
	::PostMessage(hWnd,WM_COMMAND,ID_SIZE_2,0);
}

void RIGHT::OnBnClickedRadio3()
{
	HWND hWnd = ::FindWindow(NULL, _T("CanvasX2 - canvas"));
	::PostMessage(hWnd,WM_COMMAND,ID_SIZE_3,0);
}

void RIGHT::OnBnClickedRadio4()
{
	HWND hWnd = ::FindWindow(NULL, _T("CanvasX2 - canvas"));
}

void RIGHT::OnBnClickedCatch()
{
	HWND hWnd = ::FindWindow(NULL, _T("CanvasX2 - canvas"));
	//::PostMessage(hWnd,WM_CONTROLPRINT,0,0);
	
	//CWnd  *pWnd = CWnd::FindWindow(NULL, _T("CanvasX2 - canvas"));
	//pWnd->SendMessage(WM_CONTROLPRINT,NULL,0);
	if(hWnd!=0){
		::PostMessage(hWnd,WM_COMMAND,ID_BUTTON_CATCH,0);
	}
}

void RIGHT::OnBnClickedBack()
{
	HWND hWnd = ::FindWindow(NULL, _T("CanvasX2 - canvas"));
	::PostMessage(hWnd,WM_COMMAND,ID_BUTTON_BACK,0);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void RIGHT::OnBnClickedBush()
{
	HWND hWnd = ::FindWindow(NULL, _T("CanvasX2 - canvas"));
	::PostMessage(hWnd,WM_COMMAND,ID_BUTTON_BRUSH,0);
}

void RIGHT::OnBnClickedDel()
{
	HWND hWnd = ::FindWindow(NULL, _T("CanvasX2 - canvas"));
	::PostMessage(hWnd,WM_COMMAND,ID_BUTTON_DELECT,0);
}

void RIGHT::OnBnClickedF()
{
	HWND hWnd = ::FindWindow(NULL, _T("CanvasX2 - canvas"));
	::PostMessage(hWnd,WM_COMMAND,ID_ROLL_BACK,0);
}

void RIGHT::OnBnClickedN()
{
	HWND hWnd = ::FindWindow(NULL, _T("CanvasX2 - canvas"));
	::PostMessage(hWnd,WM_COMMAND,ID_ROLL_FRONT,0);
}

void RIGHT::OnTRBNThumbPosChangingSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	 CSliderCtrl *pSlidCtrl=(CSliderCtrl*)GetDlgItem(IDC_SLIDER);
	 
	//NMTRBTHUMBPOSCHANGING *pNMTPC = reinterpret_cast<NMTRBTHUMBPOSCHANGING *>(pNMHDR);
	//@TN
	//	*pResult = 0;
	//
	//*pResult = 0;
}

void RIGHT::OnNMReleasedcaptureSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CSliderCtrl *pSlidCtrl=(CSliderCtrl*)GetDlgItem(IDC_SLIDER);
	num = pSlidCtrl->GetPos();
	//num = *pResult;
	*pResult = 0;
}
