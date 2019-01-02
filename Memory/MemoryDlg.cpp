
// MemoryDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Memory.h"
#include "MemoryDlg.h"
#include "afxdialogex.h"
#include <time.h>
#include<iostream>
int rand1[10], rand2[10], rand3[10];
void bsort(MCB *A, int n);
void wsort(MCB *B, int n);
int s = 0;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMemoryDlg 对话框



CMemoryDlg::CMemoryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMemoryDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMemoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_LIST2, j_list);
	DDX_Control(pDX, IDC_BUTTON3, b_start);
	DDX_Control(pDX, IDC_BUTTON6, b_second);
	DDX_Control(pDX, IDC_BUTTON4, b_recovery);
}

BEGIN_MESSAGE_MAP(CMemoryDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMemoryDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMemoryDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_RADIO1, &CMemoryDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_BUTTON5, &CMemoryDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_RADIO2, &CMemoryDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CMemoryDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CMemoryDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_BUTTON3, &CMemoryDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMemoryDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &CMemoryDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CMemoryDlg 消息处理程序

BOOL CMemoryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	m_list.InsertColumn(0, TEXT("ID"), LVCFMT_CENTER, 50);
	m_list.InsertColumn(1, TEXT("原始空间大小"), LVCFMT_CENTER, 90);
	m_list.InsertColumn(2, TEXT("剩余空间大小"), LVCFMT_CENTER, 90);
	m_list.InsertColumn(3, TEXT("首地址"), LVCFMT_CENTER, 50);
	m_list.InsertColumn(4, TEXT("分配的作业"), LVCFMT_CENTER, 80);
	j_list.InsertColumn(0, TEXT("ID"), LVCFMT_CENTER, 50);
	j_list.InsertColumn(1, TEXT("作业大小"), LVCFMT_CENTER, 60);
	j_list.InsertColumn(2, TEXT("对应区块"), LVCFMT_CENTER, 60);
	j_list.InsertColumn(3, TEXT("状态"), LVCFMT_CENTER, 50);
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES);
	j_list.SetExtendedStyle(LVS_EX_GRIDLINES);
	b_start.EnableWindow(0);
	b_second.EnableWindow(0);
	b_recovery.EnableWindow(0);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMemoryDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMemoryDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMemoryDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//随机生成空闲分区
void CMemoryDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	m_list.DeleteAllItems();
	b_recovery.EnableWindow(1);
	int x = 1, y = 100, i, j;
	srand((unsigned)time(NULL));
	CString tmp_str;
	for (i = 0; i < 10; i++)
	{
		rand1[i] = rand() % (y - x + 1) + x;
		rand2[i] = rand() % (y - x + 1) + x;
	}
	for (j = 0; j < 10; j++)
	{
		tmp_str.Format(_T("%d"), j+1);
		m_list.InsertItem(j , tmp_str);
		tmp_str.Format(_T("%d"), rand1[j]);
		m_list.SetItemText(j, 1, tmp_str);
		tmp_str.Format(_T("%d"), rand1[j]);
		m_list.SetItemText(j, 2, tmp_str);
		tmp_str.Format(_T("%d"), rand2[j]);
		m_list.SetItemText(j, 3, tmp_str);
		memory[j].id = j+1;
		memory[j].original_size = rand1[j];
		memory[j].rest_size = rand1[j];
		memory[j].head_address = rand2[j];
		memory[j].work = m_list.GetItemText(j,4);
	}

}

//随机生成作业
void CMemoryDlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	j_list.DeleteAllItems();
	b_recovery.EnableWindow(1);
	int x = 1, y = 100, i, j;
	srand((unsigned)time(NULL));
	CString tmp_str;
	for (i = 0; i < 10; i++)
	{
		rand3[i] = rand() % (y - x + 1) + x;
	}
	for (j = 0; j < 10; j++)
	{
		tmp_str.Format(_T("%d"), j+1);
		j_list.InsertItem(j, tmp_str);
		tmp_str.Format(_T("%d"), rand3[j]);
		j_list.SetItemText(j, 1, tmp_str);
		j_list.SetItemText(j, 3, _T("N"));
	}

}

//清空
void CMemoryDlg::OnBnClickedButton5()
{
	// TODO:  在此添加控件通知处理程序代码
	m_list.DeleteAllItems();
	j_list.DeleteAllItems();
	b_start.EnableWindow(0);
	b_second.EnableWindow(0);
	b_recovery.EnableWindow(0);
	for (int j = 0; j < 10; j++)
	{
		memory[j].id = j + 1;
		memory[j].original_size = rand1[j];
		memory[j].rest_size = rand1[j];
		memory[j].head_address = rand2[j];
		memory[j].work = m_list.GetItemText(j, 4);
	}
	((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_RADIO3))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_RADIO4))->SetCheck(FALSE);
}

//首次适应（FF）算法
void CMemoryDlg::OnBnClickedRadio1()
{
	// TODO:  在此添加控件通知处理程序代码
//	m_list.DeleteAllItems();
//	j_list.DeleteAllItems();
	b_start.EnableWindow(1);
	int i, j;
	CString tmp_str;
	for (i = 0; i < 10; i++)
	{
		tmp_str.Format(_T("%d"), i + 1);
		m_list.SetItemText(i, 0, tmp_str);
		tmp_str.Format(_T("%d"), rand1[i]);
		m_list.SetItemText(i, 1, tmp_str);
		tmp_str.Format(_T("%d"), rand1[i]);
		m_list.SetItemText(i, 2, tmp_str);
		tmp_str.Format(_T("%d"), rand2[i]);
		m_list.SetItemText(i, 3, tmp_str);
		m_list.SetItemText(i, 4, _T(""));
	}
	for (j = 0; j < 10; j++)
	{
		tmp_str.Format(_T("%d"), j + 1);
		j_list.SetItemText(j, 0, tmp_str);
		tmp_str.Format(_T("%d"), rand3[j]);
		j_list.SetItemText(j, 1, tmp_str);
		j_list.SetItemText(j, 2, _T(""));
		j_list.SetItemText(j, 3, _T("N"));
	}
	s = 1;
}

//循环首次适应（NF）算法
void CMemoryDlg::OnBnClickedRadio2()
{
	// TODO:  在此添加控件通知处理程序代码
	//m_list.DeleteAllItems();
	//j_list.DeleteAllItems();
	b_start.EnableWindow(1);
	int i, j;
	CString tmp_str;
	for (i = 0; i < 10; i++)
	{
		tmp_str.Format(_T("%d"), i + 1);
		m_list.SetItemText(i, 0, tmp_str);
		tmp_str.Format(_T("%d"), rand1[i]);
		m_list.SetItemText(i, 1, tmp_str);
		tmp_str.Format(_T("%d"), rand1[i]);
		m_list.SetItemText(i, 2, tmp_str);
		tmp_str.Format(_T("%d"), rand2[i]);
		m_list.SetItemText(i, 3, tmp_str);
		m_list.SetItemText(i, 4, _T(""));
	}
	for (j = 0; j < 10; j++)
	{
		tmp_str.Format(_T("%d"), j + 1);
		j_list.SetItemText(j, 0, tmp_str);
		tmp_str.Format(_T("%d"), rand3[j]);
		j_list.SetItemText(j, 1, tmp_str);
		j_list.SetItemText(j, 2, _T(""));
		j_list.SetItemText(j, 3, _T("N"));
	}
	s = 2;
}

//最佳适应（BF）算法
void CMemoryDlg::OnBnClickedRadio3()
{
	// TODO:  在此添加控件通知处理程序代码
	//m_list.DeleteAllItems();
	//j_list.DeleteAllItems();
	b_start.EnableWindow(1);
	int i, j;
	CString tmp_str;
	bsort(memory, 10);
	for (i = 0; i < 10; i++)
	{
		tmp_str.Format(_T("%d"), memory[i].id);
		m_list.SetItemText(i, 0, tmp_str);
		tmp_str.Format(_T("%d"), memory[i].original_size);
		m_list.SetItemText(i, 1, tmp_str);
		tmp_str.Format(_T("%d"), memory[i].rest_size);
		m_list.SetItemText(i, 2, tmp_str);
		tmp_str.Format(_T("%d"), memory[i].head_address);
		m_list.SetItemText(i, 3, tmp_str);
		tmp_str = memory[i].work;
		m_list.SetItemText(i, 4, tmp_str);
	}
	for (j = 0; j < 10; j++)
	{
		tmp_str.Format(_T("%d"), j + 1);
		j_list.SetItemText(j, 0, tmp_str);
		tmp_str.Format(_T("%d"), rand3[j]);
		j_list.SetItemText(j, 1, tmp_str);
		j_list.SetItemText(j, 2, _T(""));
		j_list.SetItemText(j, 3, _T("N"));
		m_list.SetItemText(j, 4, _T(""));
	}
	s = 3;
}

//最坏适应（WF）算法
void CMemoryDlg::OnBnClickedRadio4()
{
	// TODO:  在此添加控件通知处理程序代码
	//m_list.DeleteAllItems();
	//j_list.DeleteAllItems();
	b_start.EnableWindow(1);
	int i, j;
	CString tmp_str;
	wsort(memory, 10);
	for (i = 0; i < 10; i++)
	{
		tmp_str.Format(_T("%d"), memory[i].id);
		m_list.SetItemText(i, 0, tmp_str);
		tmp_str.Format(_T("%d"), memory[i].original_size);
		m_list.SetItemText(i, 1, tmp_str);
		tmp_str.Format(_T("%d"), memory[i].rest_size);
		m_list.SetItemText(i, 2, tmp_str);
		tmp_str.Format(_T("%d"), memory[i].head_address);
		m_list.SetItemText(i, 3, tmp_str);
		tmp_str = memory[i].work;
		m_list.SetItemText(i, 4, tmp_str);
	}
	for (j = 0; j < 10; j++)
	{
		tmp_str.Format(_T("%d"), j + 1);
		j_list.SetItemText(j, 0, tmp_str);
		tmp_str.Format(_T("%d"), rand3[j]);
		j_list.SetItemText(j, 1, tmp_str);
		j_list.SetItemText(j, 2, _T(""));
		j_list.SetItemText(j, 3, _T("N"));
		m_list.SetItemText(j, 4, _T(""));
	}
	s = 4;
}
//按容量从小到大排序
void bsort(MCB *A, int n)
{
	int i, j;
	MCB t;
	for (i = 0; i<n - 1; i++)
	{
		for (j = n - 1; j>i; j--)
		{
			if (A[j].rest_size<A[j - 1].rest_size)
			{
				t = A[j];
				A[j] = A[j - 1];
				A[j - 1] = t;
			}
		}
	}
}
//按容量从大到小排序
void wsort(MCB *B, int n)
{
	int i, j;
	MCB t;
	for (i = 0; i<n - 1; i++)
	{
		for (j = n - 1; j>i; j--)
		{
			if (B[j].rest_size>B[j - 1].rest_size)
			{
				t = B[j];
				B[j] = B[j - 1];
				B[j - 1] = t;
			}
		}
	}
}

//开始分配
void CMemoryDlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	b_start.EnableWindow(0);
	int i, j, k, temp = 0;
	CString tmp_str;
	switch (s)
	{
	case 1:
		for (i = 0; i < 10; i++)
		{
			for (j = 0; (j < 10) && (_ttoi(m_list.GetItemText(j, 2)) < rand3[i]); j++)
			{
				;
			}
			if (j>9)
			{
				j_list.SetItemText(i, 2, _T("未分配"));
				j_list.SetItemText(i, 3, _T("N"));
			}
			else if (_ttoi(m_list.GetItemText(j, 2)) >= rand3[i])
			{
				tmp_str.Format(_T("%d"), _ttoi(m_list.GetItemText(j, 2))-rand3[i]);
				m_list.SetItemText(j, 2, tmp_str);
				tmp_str.Format(_T("%d"), i+1);
				m_list.SetItemText(j, 4, m_list.GetItemText(j, 4) + "|" + tmp_str);
				tmp_str.Format(_T("%d"), j+1);
				j_list.SetItemText(i, 2, tmp_str);
				j_list.SetItemText(i, 3, _T("Y"));
			}
		}
		break;
	case 2:
		int sum;
		for (i = 0; i < 10; i++)
		{
			for (j = temp, sum = 0; sum < 10; j++)
			{
				k = j%10;
				
				sum++;
				if (_ttoi(m_list.GetItemText(k, 2)) >= rand3[i])
				{
					break;
				}
			}
			if (sum == 10)
			{
				j_list.SetItemText(i, 2, _T("未分配"));
				j_list.SetItemText(i, 3, _T("N"));
			}
			else if (_ttoi(m_list.GetItemText(k, 2)) >= rand3[i])
			{
				temp = k + 1;
				tmp_str.Format(_T("%d"), _ttoi(m_list.GetItemText(k, 2)) - rand3[i]);
				m_list.SetItemText(k, 2, tmp_str);
				tmp_str.Format(_T("%d"), i + 1);
				m_list.SetItemText(k, 4, m_list.GetItemText(k, 4) + "|" + tmp_str);
				tmp_str.Format(_T("%d"), k + 1);
				j_list.SetItemText(i, 2, tmp_str);
				j_list.SetItemText(i, 3, _T("Y"));
			}
		}
		break;
	case 3:
		for (i = 0; i < 10; i++)
		{
			for (j = 0; (j < 10) && (memory[j].rest_size< rand3[i]); j++)
			{
				;
			}
			if (j>9)
			{
				j_list.SetItemText(i, 2, _T("未分配"));
				j_list.SetItemText(i, 3, _T("N"));
			}
			else if (memory[j].rest_size >= rand3[i])
			{
				tmp_str.Format(_T("%d"), _ttoi(m_list.GetItemText(j, 2)) - rand3[i]);
				m_list.SetItemText(j, 2, tmp_str);
				tmp_str.Format(_T("%d"), i + 1);
				m_list.SetItemText(j, 4, m_list.GetItemText(j, 4) + "|" + tmp_str);
				memory[j].rest_size = _ttoi(m_list.GetItemText(j, 2));
				memory[j].work = m_list.GetItemText(j, 4);
				tmp_str.Format(_T("%d"), memory[j].id);
				j_list.SetItemText(i, 2, tmp_str);
				j_list.SetItemText(i, 3, _T("Y"));
				bsort(memory, 10);
				for (int z = 0; z < 10; z++)
				{
					tmp_str.Format(_T("%d"), memory[z].id);
					m_list.SetItemText(z, 0, tmp_str);
					tmp_str.Format(_T("%d"), memory[z].original_size);
					m_list.SetItemText(z, 1, tmp_str);
					tmp_str.Format(_T("%d"), memory[z].rest_size);
					m_list.SetItemText(z, 2, tmp_str);
					tmp_str.Format(_T("%d"), memory[z].head_address);
					m_list.SetItemText(z, 3, tmp_str);
					tmp_str = memory[z].work;
					m_list.SetItemText(z, 4, tmp_str);
				}
			}
		}
		break;
	case 4:
		for (i = 0; i < 10; i++)
		{
			for (j = 0; (j < 10) && (memory[j].rest_size< rand3[i]); j++)
			{
				;
			}
			if (j>9)
			{
				j_list.SetItemText(i, 2, _T("未分配"));
				j_list.SetItemText(i, 3, _T("N"));
			}
			else if (memory[j].rest_size >= rand3[i])
			{
				tmp_str.Format(_T("%d"), _ttoi(m_list.GetItemText(j, 2)) - rand3[i]);
				m_list.SetItemText(j, 2, tmp_str);
				tmp_str.Format(_T("%d"), i + 1);
				m_list.SetItemText(j, 4, m_list.GetItemText(j, 4) + "|" + tmp_str);
				memory[j].rest_size = _ttoi(m_list.GetItemText(j, 2));
				memory[j].work = m_list.GetItemText(j, 4);
				tmp_str.Format(_T("%d"), memory[j].id);
				j_list.SetItemText(i, 2, tmp_str);
				j_list.SetItemText(i, 3, _T("Y"));
				wsort(memory, 10);
//				m_list.DeleteAllItems();
				for (int z = 0; z < 10; z++)
				{
					tmp_str.Format(_T("%d"), memory[z].id);
					m_list.SetItemText(z, 0, tmp_str);
					tmp_str.Format(_T("%d"), memory[z].original_size);
					m_list.SetItemText(z, 1, tmp_str);
					tmp_str.Format(_T("%d"), memory[z].rest_size);
					m_list.SetItemText(z, 2, tmp_str);
					tmp_str.Format(_T("%d"), memory[z].head_address);
					m_list.SetItemText(z, 3, tmp_str);
					tmp_str = memory[z].work;
					m_list.SetItemText(z, 4, tmp_str);
				}
			}
		}
		break;
	default:
		MessageBox(TEXT("请选择算法") );
		break;
	}
}

//回收所有资源
void CMemoryDlg::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码
	b_start.EnableWindow(1);
	b_second.EnableWindow(1);
	/*m_list.DeleteAllItems();*/
	int j, k;
	CString tmp_str;
	for (j = 0; j < 10; j++)
	{
		tmp_str.Format(_T("%d"), j + 1);
		m_list.SetItemText(j, 0, tmp_str);
		tmp_str.Format(_T("%d"), rand1[j]);
		m_list.SetItemText(j, 1, tmp_str);
		tmp_str.Format(_T("%d"), rand1[j]);
		m_list.SetItemText(j, 2, tmp_str);
		tmp_str.Format(_T("%d"), rand2[j]);
		m_list.SetItemText(j, 3, tmp_str);
		m_list.SetItemText(j, 4, _T(""));
		memory[j].id = j + 1;
		memory[j].original_size = rand1[j];
		memory[j].rest_size = rand1[j];
		memory[j].head_address = rand2[j];
		memory[j].work = m_list.GetItemText(j, 4);
	}
	for (k = 0; k < 10; k++)
	{
		tmp_str.Format(_T("%d"), k + 1);
		j_list.SetItemText(k, 0, tmp_str);
		tmp_str.Format(_T("%d"), rand3[k]);
		j_list.SetItemText(k, 1, tmp_str);
		j_list.SetItemText(k, 2, _T(""));
		if (j_list.GetItemText(k, 3) == "Y")
		{
			j_list.SetItemText(k, 3, _T("已完成"));
		}
	}
}

//二次分配
void CMemoryDlg::OnBnClickedButton6()
{
	// TODO:  在此添加控件通知处理程序代码
	b_start.EnableWindow(1);
	int i, j, k, temp = 0;
	CString tmp_str;
	switch (s)
	{
	case 1:
		for (i = 0; i < 10; i++)
		{
			if (j_list.GetItemText(i, 3) == "N")
			{
				for (j = 0; (j < 10) && (_ttoi(m_list.GetItemText(j, 2)) < rand3[i]); j++)
				{
					;
				}
				if (j>9)
				{
					j_list.SetItemText(i, 2, _T("未分配"));
					j_list.SetItemText(i, 3, _T("N"));
				}
				else if (_ttoi(m_list.GetItemText(j, 2)) >= rand3[i])
				{
					tmp_str.Format(_T("%d"), _ttoi(m_list.GetItemText(j, 2)) - rand3[i]);
					m_list.SetItemText(j, 2, tmp_str);
					tmp_str.Format(_T("%d"), i + 1);
					m_list.SetItemText(j, 4, m_list.GetItemText(j, 4) + "|" + tmp_str);
					tmp_str.Format(_T("%d"), j + 1);
					j_list.SetItemText(i, 2, tmp_str);
					j_list.SetItemText(i, 3, _T("Y"));
				}
			}
		}
		break;
	case 2:
		int sum;
		for (i = 0; i < 10; i++)
		{
			if (j_list.GetItemText(i, 3) == "N")
			{
				for (j = temp, sum = 0; sum < 10; j++)
				{
					k = j % 10;

					sum++;
					if (_ttoi(m_list.GetItemText(k, 2)) >= rand3[i])
					{
						break;
					}
				}
				if (sum == 10)
				{
					j_list.SetItemText(i, 2, _T("未分配"));
					j_list.SetItemText(i, 3, _T("N"));
				}
				else if (_ttoi(m_list.GetItemText(k, 2)) >= rand3[i])
				{
					temp = k + 1;
					tmp_str.Format(_T("%d"), _ttoi(m_list.GetItemText(k, 2)) - rand3[i]);
					m_list.SetItemText(k, 2, tmp_str);
					tmp_str.Format(_T("%d"), i + 1);
					m_list.SetItemText(k, 4, m_list.GetItemText(k, 4) + "|" + tmp_str);
					tmp_str.Format(_T("%d"), k + 1);
					j_list.SetItemText(i, 2, tmp_str);
					j_list.SetItemText(i, 3, _T("Y"));
				}
			}
		}
		break;
	case 3:
		for (i = 0; i < 10; i++)
		{
			if (j_list.GetItemText(i, 3) == "N")
			{
				for (j = 0; (j < 10) && (memory[j].rest_size< rand3[i]); j++)
				{
					;
				}
				if (j>9)
				{
					j_list.SetItemText(i, 2, _T("未分配"));
					j_list.SetItemText(i, 3, _T("N"));
				}
				else if (memory[j].rest_size >= rand3[i])
				{
					tmp_str.Format(_T("%d"), _ttoi(m_list.GetItemText(j, 2)) - rand3[i]);
					m_list.SetItemText(j, 2, tmp_str);
					tmp_str.Format(_T("%d"), i + 1);
					m_list.SetItemText(j, 4, m_list.GetItemText(j, 4) + "|" + tmp_str);
					memory[j].rest_size = _ttoi(m_list.GetItemText(j, 2));
					memory[j].work = m_list.GetItemText(j, 4);
					tmp_str.Format(_T("%d"), memory[j].id);
					j_list.SetItemText(i, 2, tmp_str);
					j_list.SetItemText(i, 3, _T("Y"));
					bsort(memory, 10);
					/*m_list.DeleteAllItems();*/
					for (int z = 0; z < 10; z++)
					{
						tmp_str.Format(_T("%d"), memory[z].id);
						m_list.SetItemText(z, 0, tmp_str);
						tmp_str.Format(_T("%d"), memory[z].original_size);
						m_list.SetItemText(z, 1, tmp_str);
						tmp_str.Format(_T("%d"), memory[z].rest_size);
						m_list.SetItemText(z, 2, tmp_str);
						tmp_str.Format(_T("%d"), memory[z].head_address);
						m_list.SetItemText(z, 3, tmp_str);
						tmp_str = memory[z].work;
						m_list.SetItemText(z, 4, tmp_str);
					}
				}
			}
		}
		break;
	case 4:
		for (i = 0; i < 10; i++)
		{
			if (j_list.GetItemText(i, 3) == "N")
			{
				for (j = 0; (j < 10) && (memory[j].rest_size< rand3[i]); j++)
				{
					;
				}
				if (j>9)
				{
					j_list.SetItemText(i, 2, _T("未分配"));
					j_list.SetItemText(i, 3, _T("N"));
				}
				else if (memory[j].rest_size >= rand3[i])
				{
					tmp_str.Format(_T("%d"), _ttoi(m_list.GetItemText(j, 2)) - rand3[i]);
					m_list.SetItemText(j, 2, tmp_str);
					tmp_str.Format(_T("%d"), i + 1);
					m_list.SetItemText(j, 4, m_list.GetItemText(j, 4) + "|" + tmp_str);
					memory[j].rest_size = _ttoi(m_list.GetItemText(j, 2));
					memory[j].work = m_list.GetItemText(j, 4);
					tmp_str.Format(_T("%d"), memory[j].id);
					j_list.SetItemText(i, 2, tmp_str);
					j_list.SetItemText(i, 3, _T("Y"));
					wsort(memory, 10);
					/*m_list.DeleteAllItems();*/
					for (int z = 0; z < 10; z++)
					{
						tmp_str.Format(_T("%d"), memory[z].id);
						m_list.SetItemText(z, 0, tmp_str);
						tmp_str.Format(_T("%d"), memory[z].original_size);
						m_list.SetItemText(z, 1, tmp_str);
						tmp_str.Format(_T("%d"), memory[z].rest_size);
						m_list.SetItemText(z, 2, tmp_str);
						tmp_str.Format(_T("%d"), memory[z].head_address);
						m_list.SetItemText(z, 3, tmp_str);
						tmp_str = memory[z].work;
						m_list.SetItemText(z, 4, tmp_str);
					}
				}
			}
		}
		break;
	default:
		break;
	}
}
