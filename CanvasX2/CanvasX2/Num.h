#pragma once


// CNum 对话框 CDialogEx

class CNum : public CDialogEx
{
	DECLARE_DYNAMIC(CNum)

public:
	static CNum cnum;
	CNum(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNum();

// 对话框数据
	enum { IDD = IDD_NUM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
