#pragma once


// CNum �Ի��� CDialogEx

class CNum : public CDialogEx
{
	DECLARE_DYNAMIC(CNum)

public:
	static CNum cnum;
	CNum(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNum();

// �Ի�������
	enum { IDD = IDD_NUM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
