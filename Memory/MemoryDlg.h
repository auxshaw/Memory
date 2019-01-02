
// MemoryDlg.h : ͷ�ļ�
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


// CMemoryDlg �Ի���
class CMemoryDlg : public CDialogEx
{
// ����
public:
	CMemoryDlg(CWnd* pParent = NULL);	// ��׼���캯��
	MCB memory[10];

// �Ի�������
	enum { IDD = IDD_MEMORY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
