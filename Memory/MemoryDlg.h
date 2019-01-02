
// MemoryDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
typedef struct MCB{
	int id;
	int original_size;
	int rest_size;
	int head_address;
	CString work;
}MCB;


// CMemoryDlg 对话框
class CMemoryDlg : public CDialogEx
{
// 构造
public:
	CMemoryDlg(CWnd* pParent = NULL);	// 标准构造函数
	MCB memory[10];

// 对话框数据
	enum { IDD = IDD_MEMORY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	CListCtrl j_list;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton6();
	CButton b_start;
	CButton b_second;
	CButton b_recovery;
};
