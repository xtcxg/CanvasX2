
// CanvasX2View.cpp : CCanvasX2View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CanvasX2.h"
#endif

#include "CanvasX2Doc.h"
#include "CanvasX2View.h"
#include "MainFrm.h"
#include <iostream>
#include <thread>
#include <Windows.h>  
#include "RIGHT.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCanvasX2View

IMPLEMENT_DYNCREATE(CCanvasX2View, CScrollView)

BEGIN_MESSAGE_MAP(CCanvasX2View, CScrollView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_BUTTON_CATCH,&CCanvasX2View::OnButtonCatch)
	ON_COMMAND(ID_BUTTON_BACK,&CCanvasX2View::OnButtonBack)
	ON_COMMAND(ID_FILE_SAVE,&CCanvasX2View::OnFileSave)
	ON_COMMAND(ID_FILE_OPEN,&CCanvasX2View::OnFileOpen)
	ON_COMMAND(ID_BUTTON_BRUSH,&CCanvasX2View::OnCBrush)
	ON_COMMAND(ID_ROLL_BACK, &CCanvasX2View::OnRollBack)
	ON_COMMAND(ID_ROLL_FRONT, &CCanvasX2View::OnRollFront)
	ON_COMMAND(ID_BUTTON_DELECT,&CCanvasX2View::OnDelect)
	ON_WM_PAINT()
	ON_MESSAGE(WM_CONTROLPRINT,&CCanvasX2View::OnRgsmsg)
	ON_COMMAND(ID_VIEW_RTOM, &CCanvasX2View::OnViewRtom)
END_MESSAGE_MAP()

// CCanvasX2View 构造/析构

CCanvasX2View::CCanvasX2View()
	: drag(false)
	, total(0)
	, sum(1)
	, catchs(-1)
	, brush(false)
	, changes(0)
	, delect(false)
	, dm(-1)
{
	// TODO: 在此处添加构造代码
	for(int i = 0 ;i<9998;i++){
		arr[i][0]=0;
	}

	for(int i=0;i<998;i++){
		sarr[i][1][0]=0;
	}
	RIGHT* right = new RIGHT;
	right->Create(IDD_RIGHT);
	DWORD style = right->GetStyle();
	//right->SetParent(this);
	//right->ModifyStyle(WS_POPUPWINDOW, WS_CHILD);
	right-> ShowWindow(WS_EX_TOPMOST );
}

CCanvasX2View::~CCanvasX2View()
{
}

BOOL CCanvasX2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// CCanvasX2View 绘制

void CCanvasX2View::OnDraw(CDC* pDC)
{
	CCanvasX2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此处为本机数据添加绘制代码

	for(int i = 0;i<9998;i++){
		if(arr[i][0]==0){
			//break;
		}else{
			CPen cpen;
			cpen.CreatePen(PS_SOLID,arr[i][8],RGB(arr[i][5],arr[i][6],arr[i][7]));
			CPen *OldPen = pDC->SelectObject(&cpen);
			pDC->SetROP2(R2_COPYPEN);
			pDC->SelectStockObject(NULL_BRUSH);
			switch (arr[i][9])
			{
			case 0:
			case 5:
			case 1:
				pDC->MoveTo(arr[i][1],arr[i][2]);
				pDC->LineTo(arr[i][3],arr[i][4]);
				break;
			case 2:
				pDC->Rectangle(arr[i][1],arr[i][2],arr[i][3],arr[i][4]);
				break;
			case 3:
			case 4:
				pDC->Ellipse(arr[i][1],arr[i][2],arr[i][3],arr[i][4]);
				break;
			default:
				break;
			}
			pDC->SelectObject(cpen);
		}
	}
}

void CCanvasX2View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 计算此视图的合计大小
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

// CCanvasX2View 诊断

#ifdef _DEBUG
void CCanvasX2View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CCanvasX2View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CCanvasX2Doc* CCanvasX2View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCanvasX2Doc)));
	return (CCanvasX2Doc*)m_pDocument;
}
#endif //_DEBUG

// CCanvasX2View 消息处理程序

/* * * * * * * * * * * DOWN * * * * * * * * * * * * * * * * */
void CCanvasX2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(delect==true){
		for(int i = 0;i<9999;i++){
			//BLine
			if(arr[i][9]==1){
				int x1=arr[i][1],y1=arr[i][2], x2=arr[i][3],y2=arr[i][4];
				double re = sqrt(pow(point.x-x1,2)+pow(point.y-y1,2)) + sqrt(pow(point.x-x2,2)+pow(point.y-y2,2)) - sqrt(pow(x2-x1,2)+pow(y2-y1,2));
				if(re<8){
					int s = arr[i][0];
					for(int j=0;j<9999;j++){
						if(arr[j][0]==s){
							arr[j][0]=0;
						}
					}
					AddChange();
					break;
				}
			}
			//圆 椭圆 矩形
			if (arr[i][9]==2||arr[i][9]==3||arr[i][9]==4)
			{
				int x1,y1,x2,y2;
				if(arr[i][1]>arr[i][3]){
					x1 = arr[i][1];
					x2 = arr[i][3];
				}else
				{
					x1 = arr[i][3];
					x2 = arr[i][1];
				}
				if(arr[i][2]>arr[i][4]){
					y1 = arr[i][2];
					y2 = arr[i][4];
				}else
				{
					y1 = arr[i][4];
					y2 = arr[i][2];
				}

				if(x2<point.x && point.x<x1 && y2<point.y && point.y<y1){
					int s = arr[i][0];
					for(int j=0;j<9999;j++){
						if(arr[j][0]==s){
							arr[j][0]=0;
						}
					}
					AddChange();
					break;
				}
			}
			//Line
			if(arr[i][9]==0){
				double r = sqrt(pow(point.x-arr[i][1],2)+pow(point.y-arr[i][2],2));
				if(r<8){
					int s = arr[i][0];
					for(int j=0;j<9999;j++){
						if(arr[j][0]==s){
							arr[j][0]=0;
						}
					}
					AddChange();
					break;
				}
			}
			//
			if(arr[i][9]==5){
				int cat = arr[i][0];
				int x1=arr[i][1],y1=arr[i][2],x2=arr[i][3],y2=arr[i][4];
				for(int a=i;a<99+i;a++){
					if(arr[a][0]==cat){
						if(arr[a][1]>x1){x1=arr[a][1];}
						if(arr[a][1]<x2){x2=arr[a][1];}
						if(arr[a][2]>y1){y1=arr[a][2];}
						if(arr[a][2]<y2){y2=arr[a][2];}
					}
				}
				if(x2<point.x && point.x<x1 && y2<point.y && point.y<y1){
					int s = arr[i][0];
					for(int j=0;j<9999;j++){
						if(arr[j][0]==s){
							arr[j][0]=0;
						}
					}
					AddChange();
					break;
				}
			}
		}
		
		CWnd::Invalidate(TRUE);

		return;
	}
	if(brush==true&& delect==false){
		OnBrush(point.x,point.y);
		return;
	}
	if(drag==true){
		for(int i = 0;i<9999;i++){
			if(arr[i][9]==1){
				int x1=arr[i][1],y1=arr[i][2], x2=arr[i][3],y2=arr[i][4];
				double re = sqrt(pow(point.x-x1,2)+pow(point.y-y1,2)) + sqrt(pow(point.x-x2,2)+pow(point.y-y2,2)) - sqrt(pow(x2-x1,2)+pow(y2-y1,2));
				if(re<8){
					catchs = i;
					pbegin.x = x1;
					pbegin.y = y1;
					pend.x=x2;
					pend.y=y2;
					break;
				}
			}
			//圆 椭圆 矩形
			if (arr[i][9]==2||arr[i][9]==3||arr[i][9]==4)
			{
				int x1,y1,x2,y2;
				if(arr[i][1]>arr[i][3]){
					x1 = arr[i][1];
					x2 = arr[i][3];
				}else
				{
					x1 = arr[i][3];
					x2 = arr[i][1];
				}
				if(arr[i][2]>arr[i][4]){
					y1 = arr[i][2];
					y2 = arr[i][4];
				}else
				{
					y1 = arr[i][4];
					y2 = arr[i][2];
				}

				if(x2<point.x && point.x<x1 && y2<point.y && point.y<y1){
					catchs = i;
					pbegin.x = arr[i][1];
					pbegin.y = arr[i][2];
					pend.x=arr[i][3];
					pend.y=arr[i][4];
					break;
				}
			}
			//Line
			if(arr[i][9]==0){
				double r = sqrt(pow(point.x-arr[i][1],2)+pow(point.y-arr[i][2],2));
				if(r<8){
					catchs = i;
					pbegin.x = arr[i][1];
					pbegin.y = arr[i][2];
					pend.x=arr[i][3];
					pend.y=arr[i][4];
					break;
				}
			}
			if(arr[i][9]==5){
				int cat = arr[i][0];
				int x1=arr[i][1],y1=arr[i][2],x2=arr[i][3],y2=arr[i][4];
				for(int a=i;a<99+i;a++){
					if(arr[a][0]==cat){
						if(arr[a][1]>x1){x1=arr[a][1];}
						if(arr[a][1]<x2){x2=arr[a][1];}
						if(arr[a][2]>y1){y1=arr[a][2];}
						if(arr[a][2]<y2){y2=arr[a][2];}
					}
				}
				if(x2<point.x && point.x<x1 && y2<point.y && point.y<y1){
					catchs = i;
					break;
				}
			}
		}
	}

	CScrollView::OnLButtonDown(nFlags, point);

	if(types==5 && drag==false &&delect==false){
		if(sum>1 && sum <=num ){
			CClientDC ClientDC(this);
			CPen cpen;
			cpen.CreatePen(PS_SOLID,size,RGB(r,g,b));
			CPen *OldPen = ClientDC.SelectObject(&cpen);
			ClientDC.SetROP2(R2_COPYPEN);//缺省绘图模式，像素为画笔颜色

			ClientDC.MoveTo(PDown);
			ClientDC.LineTo(point);
			SetArr(PDown,point);
			ClientDC.SelectObject(OldPen);
			sum++;
		}
		if(sum==1){
			sum++;
			total++;
			AddChange();
			pbegin = point;
		}
		if(sum>num){
			CClientDC ClientDC(this);
			CPen cpen;
			cpen.CreatePen(PS_SOLID,size,RGB(r,g,b));
			CPen *OldPen = ClientDC.SelectObject(&cpen);
			ClientDC.SetROP2(R2_COPYPEN);//缺省绘图模式，像素为画笔颜色

			ClientDC.MoveTo(PDown);
			ClientDC.LineTo(point);
			ClientDC.LineTo(pbegin);
			SetArr(PDown,point);
			SetArr(point,pbegin);
			ClientDC.SelectObject(OldPen);
			sum=1;
		}
	}
	if(types==0 && drag==false){
		total++;
		AddChange();
	}
	PDown = point;
	PUp=point;
}

/* * * * * * *  * * MOVE * * * * * * * * * * * */
void CCanvasX2View::OnMouseMove(UINT nFlags, CPoint point)
{
	if(drag==true && nFlags&MK_LBUTTON && catchs>=0 && brush==false && delect==false){
		if(arr[catchs][9]==1 || arr[catchs][9]==2 ||arr[catchs][9]==3 ||arr[catchs][9]==4 ){
			arr[catchs][1] =pbegin.x+ point.x-PDown.x;
			arr[catchs][2] =pbegin.y+ point.y-PDown.y;
			arr[catchs][3] =pend.x+ point.x-PDown.x;
			arr[catchs][4] =pend.y+ point.y-PDown.y;
			CWnd::Invalidate(TRUE);
		}
		if(arr[catchs][9]==0 || arr[catchs][9]==5){
			int cat = arr[catchs][0];
			for(int i=0;i<9999;i++){
				if(arr[i][0]==cat){
					arr[i][1] =arr[i][1]+ point.x-PUp.x;
					arr[i][2] =arr[i][2]+ point.y-PUp.y;
					arr[i][3] =arr[i][3]+ point.x-PUp.x;
					arr[i][4] =arr[i][4]+ point.y-PUp.y;
				}
			}
			CWnd::Invalidate(TRUE);
		}
	}

	CScrollView::OnMouseMove(nFlags, point);

	CString str;
	str.Format(_T("坐标：x=%d, y=%d;R=%d,G=%d,B=%d"), point.x, point.y,r,g,b);    //格式化坐标值  
	((CMainFrame*)GetParent())->SetMessageText(str); 
	
	if(nFlags&MK_LBUTTON && drag==false && brush==false&& delect==false){
		if(types==0){
			CClientDC aDC(this);
			CPen cpen;
			cpen.CreatePen(PS_SOLID,size,RGB(r,g,b));
			CPen *OldPen = aDC.SelectObject(&cpen);
			aDC.MoveTo(PUp);
			aDC.LineTo(point);
			aDC.SelectObject(OldPen);
			SetArr(PUp,point);
		}
		CClientDC aDC(this);
		CPen cpen;
		cpen.CreatePen(PS_SOLID,size,RGB(r,g,b));
		CPen *OldPen = aDC.SelectObject(&cpen);
		aDC.SetROP2(R2_NOTXORPEN);
		aDC.SetROP2(R2_NOTXORPEN);
		aDC.SelectStockObject(NULL_BRUSH);
		
		if(types==1){//BLine
			aDC.MoveTo(PDown);
			aDC.LineTo(PUp);

			aDC.MoveTo(PDown);
			aDC.LineTo(point);
		}
		if(types==2){//rect
			aDC.Rectangle(PDown.x,PDown.y,PUp.x,PUp.y);
			aDC.Rectangle(PDown.x,PDown.y,point.x,point.y);
		}
		if(types==3){//ell
			aDC.Ellipse(PDown.x,PDown.y,PUp.x,PUp.y);
			aDC.Ellipse(PDown.x,PDown.y,point.x,point.y);
		}
		if(types==4){//cir
			CPoint p1,p2;
			int r = (int)sqrt(pow((PDown.x-PUp.x),2)+pow((PDown.y-PUp.y),2));
			p1.x = PDown.x-r;
			p1.y = PDown.y-r;
			p2.x = PDown.x+r;
			p2.y = PDown.y+r;
			aDC.Ellipse(p1.x,p1.y,p2.x,p2.y);

			r = (int)sqrt(pow((PDown.x-point.x),2)+pow((PDown.y-point.y),2));
			p1.x = PDown.x-r;
			p1.y = PDown.y-r;
			p2.x = PDown.x+r;
			p2.y = PDown.y+r;
			aDC.Ellipse(p1.x,p1.y,p2.x,p2.y);
		}
		aDC.SelectObject(OldPen);
	}
	
	PUp = point;
}

/* * * * * * * * UP * * * * * * * * * * * */
void CCanvasX2View::OnLButtonUp(UINT nFlags, CPoint point)
{
	catchs = -1;
	CScrollView::OnLButtonUp(nFlags, point);
	if(drag==false && brush==false&& delect==false){
		PUp = point;
		CClientDC ClientDC(this);
		ClientDC.SetROP2(R2_NOT);
		CPen cpen;
		cpen.CreatePen(PS_SOLID,size,RGB(r,g,b));
		CPen *OldPen = ClientDC.SelectObject(&cpen);
		ClientDC.SetROP2(R2_COPYPEN);//缺省绘图模式，像素为画笔颜色
		ClientDC.SelectStockObject(NULL_BRUSH);//rect,ell,cir不覆盖

		switch(types){
		case 0:
		case 5:break;
		case 1://直线
			ClientDC.MoveTo(PDown);
			ClientDC.LineTo(PUp);

			ClientDC.MoveTo(PDown);
			ClientDC.LineTo(point);
			total++;
			AddChange();
			SetArr(PDown,point);
			break;
		case 2:
			ClientDC.Rectangle(PDown.x,PDown.y,PUp.x,PUp.y);
			ClientDC.Rectangle(PDown.x,PDown.y,point.x,point.y);
			total++;
			AddChange();
			SetArr(PDown,point);
			break;
		case 3:
			ClientDC.Ellipse(PDown.x,PDown.y,PUp.x,PUp.y);
			ClientDC.Ellipse(PDown.x,PDown.y,point.x,point.y);
			total++;
			AddChange();
			SetArr(PDown,point);
			break;
		case 4:
			CPoint p1,p2;
			int r = (int)sqrt(pow((PDown.x-PUp.x),2)+pow((PDown.y-PUp.y),2));
			p1.x = PDown.x-r;
			p1.y = PDown.y-r;
			p2.x = PDown.x+r;
			p2.y = PDown.y+r;
			ClientDC.Ellipse(p1.x,p1.y,p2.x,p2.y);

			r = (int)sqrt(pow((PDown.x-point.x),2)+pow((PDown.y-point.y),2));
			p1.x = PDown.x-r;
			p1.y = PDown.y-r;
			p2.x = PDown.x+r;
			p2.y = PDown.y+r;
			ClientDC.Ellipse(p1.x,p1.y,p2.x,p2.y);
			total++;
			AddChange();
			SetArr(p1,p2);
			break;
		}
		ClientDC.SelectObject(OldPen);
	}
}
void CCanvasX2View::OnButtonCatch(){
	CMainFrame *pMainWnd = (CMainFrame*)AfxGetMainWnd(); 
	if(drag==true){
		pMainWnd->m_wndToolBar.GetToolBarCtrl().SetState(ID_BUTTON_CATCH,TBSTATE_ENABLED);
		drag=false;
	}else{
		drag=true;
		pMainWnd->m_wndToolBar.GetToolBarCtrl().SetState(ID_BUTTON_CATCH,TBSTATE_PRESSED);
	}
}

void CCanvasX2View::OnButtonBack(){
	int cat;
	if(arr[0][0]==0){
		MessageBox(_T("已完全清除"),_T("warming"),MB_OK);
		return;
	}
	for(int i = 0 ;i<9999;i++){
		if(arr[i][0]==0){
			cat = arr[i-1][0];
			break;
		}
	}
	for(int i=0;i<9999;i++){
		if(arr[i][0]==cat){
			arr[i][0]=0;
		}
	}
	CWnd::Invalidate(TRUE);
}

void CCanvasX2View::SetArr(CPoint p1, CPoint p2)
{
	int ax[10] = {total,p1.x,p1.y,p2.x,p2.y,r,g,b,size,types};
	for(int i = 0;i<9998;i++){
		if(arr[i][0]==0){
			for(int j=0;j<10;j++){
				arr[i][j]=ax[j];
			}
			break;
		}
	}
}

void CCanvasX2View::OnFileSave()
{
// 	thread t(ThreadSave);
// 	t.detach;
	thread(ThreadSave);
	
}
void CCanvasX2View::ThreadSave(){
	CString m_txtName=_T("E:\\save.txt");
	CStdioFile file;  
	CString filepath;  
	TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||");  
	CFileDialog fileDlg(FALSE, _T("txt"), m_txtName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);  

	if (IDOK == fileDlg.DoModal())  
	{  
		filepath = fileDlg.GetPathName();  
		file.Open(filepath, CFile::modeCreate | CFile::modeWrite | CFile::typeText);  
		CString str;  
		for(int i =0;i<9999;i++){
			if(arr[i][0]==0){return;}
			string str = to_string(arr[i][0])+"-"+to_string(arr[i][1])+"-"+to_string(arr[i][2])+"-"
				+to_string(arr[i][3])+"-"+to_string(arr[i][4])+"-"+to_string(arr[i][5])+"-"
				+to_string(arr[i][6])+"-"+to_string(arr[i][7])+"-"+to_string(arr[i][8])+"-"+to_string(arr[i][9]);
			char t2[100];
			strncpy_s(t2, (str).data(), 99);
			CString cs = CString(t2)+_T("\n");
			file.WriteString(cs);
		}
		file.Close();  
	} 
}

void CCanvasX2View::OnFileOpen()
{
	CString str;

	CString defaultDir = L"E:\\";   //默认打开的文件路径  
	CString fileName = L"save.txt";         //默认打开的文件名  
	CString filter = L"文件 (*.txt;*.doc;)|*.doc;*.txt";   //文件过虑的类型  
	CFileDialog openFileDlg(TRUE, defaultDir, fileName, OFN_HIDEREADONLY|OFN_READONLY, filter, NULL);  
	openFileDlg.GetOFN().lpstrInitialDir = L"E:\\save.txt";  
	INT_PTR result = openFileDlg.DoModal();  
	CString filePath = defaultDir + "\\save.txt";  
	if(result == IDOK) {  
		filePath = openFileDlg.GetPathName();  
		CStdioFile file;
		if(!file.Open(filePath,CFile::modeRead)){
			::AfxMessageBox(_T("文件打开失败。"));
			return;
		}
		for(int i=0;i<999;i++){
			if(arr[i][0]!=0){
				arr[i][0]=0;
			}else{break;}
		}
		str = _T("");
		int j=0;
		while(file.ReadString(str)){
			
			USES_CONVERSION;
			char* ch = W2A(str);
			std::string s=ch;
			char* res =NULL;
			char* res1 = NULL;
			int i =0;
			res = strtok_s(ch,"-",&res1);
			while (res!=NULL)
			{
				if(res!=NULL){
					arr[j][i] = atoi(res);
					res = strtok_s(NULL,"-",&res1);
					i++;
				}
			}
			j++;
		}
		file.Close();
		CWnd::Invalidate(TRUE);
	}  
	CWnd::SetDlgItemTextW(ID_FILE_OPEN, filePath); 
}

void CCanvasX2View::OnBrush(int x,int y)
{
	CPoint copen[9999];
	for(int i = 0;i<9999;i++){
		copen[i]=(0,0);
	}
	HDC hdc=::GetDC(m_hWnd);
	CClientDC aDC(this);
	copen[0].x=x;
	copen[0].y=y;
	bool bl =true;
	while (bl)
	{
		for(int i=0;i<9999;i++){
			if(copen[i].x!=0&&copen[i].y!=0){
				aDC.SetPixel(copen[i].x,copen[i].y,RGB(r,g,b));
				int a=copen[i].x,b=copen[i].y;
				copen[i].x=0;
				copen[i].y=0;

				//x+1,y+1
				CPoint p1(a+1,b+1);
				//CWinThread *m_pthread=AfxBeginThread((AFX_THREADPROC)Thread1, &p1,THREAD_PRIORITY_NORMAL,0,0);
				
				if(GetPixel(hdc,a+1,b+1)==RGB(255,255,255)){
					for (int j = 0; j < 9999; j++)
					{
						if(copen[j].x==0){copen[j].x=a+1;copen[j].y=b+1;break;}
					}
				} 
				//x-1,y-1
				if(GetPixel(hdc,a-1,b-1)==RGB(255,255,255)){
					for (int j = 0; j < 9999; j++)
					{
						if(copen[j].x==0){copen[j].x=a-1;copen[j].y=b-1;break;}
					}
				}
				//x+1,y-1
				if(GetPixel(hdc,a+1,b-1)==RGB(255,255,255)){
					for (int j = 0; j < 9999; j++)
					{
						if(copen[j].x==0){copen[j].x=a+1;copen[j].y=b-1;break;}
					}
				}
				//x-1,y+1
				if(GetPixel(hdc,a-1,b+1)==RGB(255,255,255)){
					for (int j = 0; j < 9999; j++)
					{
						if(copen[j].x==0){copen[j].x=a-1;copen[j].y=b+1;break;}
					}
				}
			}
		}
		bl=false;
		for(int i =0;i<9999;i++){
			if(copen[i].x!=0&&copen[i].y!=0){
				bl=true;
			}
		}
	}
}
void CCanvasX2View::OnCBrush(){
	CMainFrame *pMainWnd = (CMainFrame*)AfxGetMainWnd(); 
	if(brush==true){
		pMainWnd->m_wndToolBar.GetToolBarCtrl().SetState(ID_BUTTON_BRUSH,TBSTATE_ENABLED);
		brush=false;
	}else{
		brush=true;
		pMainWnd->m_wndToolBar.GetToolBarCtrl().SetState(ID_BUTTON_BRUSH,TBSTATE_PRESSED);
	}
}

DWORD WINAPI Thread1(LPVOID pParam){
	CDC* pdc;
	pdc=AfxGetApp()->m_pMainWnd->GetDC();  
	for(int i=0;i<100;i++){
		pdc->SetPixel(100+i,100,RGB(255,0,0));
	}
	return 1;
/*
	
	CPoint* p = (CPoint*)pParam;
	int x =p->x,y=p->y;
	CPoint copen[9999];
	for(int i = 0;i<9999;i++){
		copen[i]=(0,0);
	}
	//m_hWnd
	LPCTSTR lstr = L"CanvasX2";
// 	CWnd *pwnd = FindWindow("CAnxasX2",NULL); 
// 	HWND hwnd = pwnd->GetSafeHwnd();
	HWND hWnd = AfxGetMainWnd()->m_hWnd;
	HDC hdc=::GetDC(hWnd);
	//CClientDC aDC(this);
	copen[0].x=x;
	copen[0].y=y;
	bool bl =true;
	while (bl)
	{
		for(int i=0;i<9999;i++){
			if(copen[i].x!=0&&copen[i].y!=0){
				pdc->SetPixel(copen[i].x,copen[i].y,RGB(r,g,b));
				int a=copen[i].x,b=copen[i].y;
				copen[i].x=0;
				copen[i].y=0;

				//x+1,y+1
				if(GetPixel(hdc,a+1,b+1)==RGB(255,255,255)){
					for (int j = 0; j < 9999; j++)
					{
						if(copen[j].x==0){copen[j].x=a+1;copen[j].y=b+1;break;}
					}
				} 
				//x-1,y-1
				if(GetPixel(hdc,a-1,b-1)==RGB(255,255,255)){
					for (int j = 0; j < 9999; j++)
					{
						if(copen[j].x==0){copen[j].x=a-1;copen[j].y=b-1;break;}
					}
				}
				//x+1,y-1
				if(GetPixel(hdc,a+1,b-1)==RGB(255,255,255)){
					for (int j = 0; j < 9999; j++)
					{
						if(copen[j].x==0){copen[j].x=a+1;copen[j].y=b-1;break;}
					}
				}
				//x-1,y+1
				if(GetPixel(hdc,a-1,b+1)==RGB(255,255,255)){
					for (int j = 0; j < 9999; j++)
					{
						if(copen[j].x==0){copen[j].x=a-1;copen[j].y=b+1;break;}
					}
				}
			}
		}
		bl=false;
		for(int i =0;i<9999;i++){
			if(copen[i].x!=0&&copen[i].y!=0){
				bl=true;
			}
		}
	}
	return 0;*/
}

void CCanvasX2View::AddChange(){
	for(int i=0;i<9998;i++){
		for(int j=0;j<10;j++){
			sarr[changes][i][j]=arr[i][j];
		}
	}
	changes++;
}

void CCanvasX2View::OnRollBack()
{
	// TODO: 在此添加命令处理程序代码
	//MessageBox(_T("back"),_T("Message"),MB_OK);
	changes--;
	for(int i=0;i<9998;i++){
		for(int j=0;j<10;j++){
			arr[i][j]=sarr[changes][i][j];
		}
	}
	CWnd::Invalidate(TRUE);
}

void CCanvasX2View::OnRollFront()
{
	// TODO: 在此添加命令处理程序代码
	if(sarr[changes][0][0]==0){
		return;
	}
	for(int i=0;i<9998;i++){
		for(int j=0;j<10;j++){
			arr[i][j]=sarr[changes][i][j];
		}
	}
	changes++;
	CWnd::Invalidate(TRUE);
}

void CCanvasX2View::OnDelect(){
	CMainFrame *tb = (CMainFrame*)AfxGetMainWnd(); 
	if(delect==false){
		delect=true;
		tb->m_wndToolBar.GetToolBarCtrl().SetState(ID_BUTTON_DELECT,TBSTATE_PRESSED);
	}else{
		delect=false;
		tb->m_wndToolBar.GetToolBarCtrl().SetState(ID_BUTTON_DELECT,TBSTATE_ENABLED);
	}
}

LRESULT CCanvasX2View::OnRgsmsg(WPARAM wParam,LPARAM lParam)
{
 //AfxMessageBox("接收到消息");
	MessageBox(_T("message"),_T("noo"),MB_OK);
	return true;
}

void CCanvasX2View::OnViewRtom()
{ 
	MessageBox(_T("message"),_T("noo"),MB_OK);
}
