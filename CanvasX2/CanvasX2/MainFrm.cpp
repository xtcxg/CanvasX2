
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "CanvasX2.h"
#include "afxPane.h"
#include "MainFrm.h"
#include <afxcontrolbars.h> 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_BUTTON_0,CMainFrame::OnButton0)
	ON_COMMAND(ID_BUTTON_1,CMainFrame::OnButton1)
	ON_COMMAND(ID_BUTTON_2,CMainFrame::OnButton2)
	ON_COMMAND(ID_BUTTON_3,CMainFrame::OnButton3)
	ON_COMMAND(ID_BUTTON_4,CMainFrame::OnButton4)
	ON_COMMAND(ID_BUTTON_5,CMainFrame::OnButton5)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������

// 	RIGHT* right = new RIGHT;
// 	right->Create(IDD_RIGHT);
// 	DWORD style = right->GetStyle();
// 	//right->SetParent(this);
// 	//right->ModifyStyle(WS_POPUPWINDOW, WS_CHILD);
// 	right-> ShowWindow(WS_EX_TOPMOST );
}

CMainFrame::~CMainFrame()
{
}
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return 0;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: �������Ҫ��ͣ������������ɾ��������
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_THICKFRAME | WS_MINIMIZEBOX | WS_SYSMENU;

	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������
void CMainFrame::OnButton0(){
	types=0;
}

void CMainFrame::OnButton1(){
	types=1;
}

void CMainFrame::OnButton2(){
	types=2;
}

void CMainFrame::OnButton3(){
	types=3;
}

void CMainFrame::OnButton4(){
	types=4;
}

void CMainFrame::OnButton5(){
	types=5;
}