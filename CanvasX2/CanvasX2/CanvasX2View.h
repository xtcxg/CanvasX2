
// CanvasX2View.h : CCanvasX2View 类的接口
//

#pragma once
#include <iostream>
#include <string>
#include <list>
#include "CanvasX2Doc.h"
using namespace std;
DWORD WINAPI Thread1(LPVOID pParam);
class CCanvasX2View : public CScrollView
{
	public: // 仅从序列化创建
	CCanvasX2View();
	DECLARE_DYNCREATE(CCanvasX2View)

// 特性
public:
	CCanvasX2Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CCanvasX2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:

// 生成的消息映射函数
public:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnButtonCatch();
	afx_msg void OnButtonBack();
	afx_msg void OnFileSave();
	afx_msg void OnFileOpen();
	afx_msg void OnCBrush();
	void OnBrush(int x,int y);
	CPoint PDown;
	CPoint PUp;
	CPoint pbegin;
	CPoint pend;
	int sarr[999][9999][10];
	int changes;
	void AddChange();
	bool brush;
	bool drag;
	int arr[9999][10];
	int total; //添加前自增
	int sum; //计数 
	int catchs;
	bool delect;
	int dm;
	void SetArr(CPoint p1, CPoint p2);
	void Stuff1(int x,int y);
	void Stuff2(int x,int y);
	void Stuff3(int x,int y);
	void Stuff4(int x,int y);

	afx_msg void OnRollBack();
	afx_msg void OnRollFront();
	afx_msg void ThreadSave();
	afx_msg void OnDelect();

	friend class RIGHT;//友元
	afx_msg LRESULT OnRgsmsg(WPARAM wParam,LPARAM lparam);
	afx_msg void OnViewRtom();
};

#ifndef _DEBUG  // CanvasX2View.cpp 中的调试版本
inline CCanvasX2Doc* CCanvasX2View::GetDocument() const
   { return reinterpret_cast<CCanvasX2Doc*>(m_pDocument); }
#endif

