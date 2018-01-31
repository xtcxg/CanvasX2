
// CanvasX2.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "CanvasX2.h"
#include "MainFrm.h"

#include "CanvasX2Doc.h"
#include "CanvasX2View.h"
#include "Num.h"
#include "RIGHT.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCanvasX2App

BEGIN_MESSAGE_MAP(CCanvasX2App, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CCanvasX2App::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	ON_COMMAND(ID_BLACK, &CCanvasX2App::OnBlack)
	ON_COMMAND(ID_RED, &CCanvasX2App::OnRed)
	ON_COMMAND(ID_BLUE, &CCanvasX2App::OnBlue)
	ON_COMMAND(ID_YELLOW, &CCanvasX2App::OnYellow)
	ON_COMMAND(ID_CSELF, &CCanvasX2App::OnCself)
	ON_COMMAND(ID_SIZE_1, &CCanvasX2App::OnSize1)
	ON_COMMAND(ID_SIZE_2, &CCanvasX2App::OnSize2)
	ON_COMMAND(ID_SIZE_3, &CCanvasX2App::OnSize3)
	ON_COMMAND(ID_SIZE_SELF, &CCanvasX2App::OnSizeSelf)
	ON_COMMAND(ID_B3, &CCanvasX2App::OnB3)
	ON_COMMAND(ID_B4, &CCanvasX2App::OnB4)
	ON_COMMAND(ID_B5, &CCanvasX2App::OnB5)
	ON_COMMAND(ID_B6, &CCanvasX2App::OnB6)
	ON_COMMAND(ID_BSELF, &CCanvasX2App::OnBself)
END_MESSAGE_MAP()


// CCanvasX2App ����

CCanvasX2App::CCanvasX2App()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���:
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("CanvasX2.AppID.NoVersion"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CCanvasX2App ����

CCanvasX2App theApp;


// CCanvasX2App ��ʼ��

BOOL CCanvasX2App::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)


	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CCanvasX2Doc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CCanvasX2View));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// ���á�DDE ִ�С�
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� SDI Ӧ�ó����У���Ӧ�� ProcessShellCommand ֮����
	// ������/��
	m_pMainWnd->DragAcceptFiles();
	return TRUE;
}

int CCanvasX2App::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// CCanvasX2App ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CCanvasX2App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CCanvasX2App ��Ϣ�������


void CCanvasX2App::OnBlack()
{
	r=0;
	g=0;
	b=0;
}

void CCanvasX2App::OnRed()
{
	r=255;
	g=0;
	b=0;
}

void CCanvasX2App::OnBlue()
{
	r=0;
	g=0;
	b=255;
}

void CCanvasX2App::OnYellow()
{
	r=255;
	g=255;
	b=0;
}

void CCanvasX2App::OnCself()
{
	CColorDialog cd((0,0,0),CC_FULLOPEN);
	if(cd.DoModal()==IDOK){
		const COLORREF c=cd.GetColor();
		r = GetRValue(c);
		g = GetGValue(c);
		b = GetBValue(c);
	}
}


void CCanvasX2App::OnSize1()
{
	size=1;
}


void CCanvasX2App::OnSize2()
{
	size=2;
}


void CCanvasX2App::OnSize3()
{
	size=3;
}


void CCanvasX2App::OnSizeSelf()
{
	size=4;
}


void CCanvasX2App::OnB3()
{
	num=3;
}


void CCanvasX2App::OnB4()
{
	num=4;
}


void CCanvasX2App::OnB5()
{
	num=5;
}


void CCanvasX2App::OnB6()
{
	num=6;
	RIGHT* right = new RIGHT;
	right->Create(IDD_RIGHT);
	DWORD style = right->GetStyle();
	//right->SetParent(cv);
	right->ModifyStyle(style,WS_CHILD|WS_VISIBLE,1);
	right-> ShowWindow(SW_SHOW);
}


void CCanvasX2App::OnBself()
{
	CNum CN;
	CN.DoModal();
}
