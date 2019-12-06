﻿
// DemoMFC10Dlg.cpp: 实现文件
//

#include "stdafx.h"
#include "DemoMFC10.h"
#include "DemoMFC10Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDemoMFC10Dlg 对话框



CDemoMFC10Dlg::CDemoMFC10Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DEMOMFC10_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDemoMFC10Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDemoMFC10Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDemoMFC10Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDemoMFC10Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDemoMFC10Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CDemoMFC10Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CDemoMFC10Dlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CDemoMFC10Dlg 消息处理程序

BOOL CDemoMFC10Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDemoMFC10Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDemoMFC10Dlg::OnPaint()
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
HCURSOR CDemoMFC10Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDemoMFC10Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	
	ZeroMemory(&pi, sizeof(pi));

	if(!CreateProcess(TEXT("C:/WINDOWS/system32/calc.exe"),
		NULL,//命令行参数
		NULL,//进程的安全属性 默认
		NULL,//进程里面的线程安全属性 默认
		FALSE,//继承句柄 不继承
		0,//创建标志
		NULL,//环境变量 使用父进程的环境变量
		NULL,//使用父进程的当前目录 作为子进程的目录
		&si,
		&pi)){
		CString s;
		s.Format(TEXT("创建进程失败：%d"), GetLastError());
		AfxMessageBox(s);
		return;
	}
}

STARTUPINFO si;
PROCESS_INFORMATION pi;

void CDemoMFC10Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);

	ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcess(TEXT("DemoMFC01.exe"),
		NULL,//命令行参数
		NULL,//进程的安全属性 默认
		NULL,//进程里面的线程安全属性 默认
		FALSE,//继承句柄 不继承
		0,//创建标志
		NULL,//环境变量 使用父进程的环境变量
		NULL,//使用父进程的当前目录 作为子进程的目录
		&si,
		&pi)) {
		CString s;
		s.Format(TEXT("创建进程失败：%d"), GetLastError());
		AfxMessageBox(s);
		return;
	}
}


void CDemoMFC10Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	TerminateProcess(pi.hProcess, 0);
	
}


void CDemoMFC10Dlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	str.Format(TEXT("子进程ID：%d 自己进程ID：%d"),
		pi.dwProcessId, GetCurrentProcessId());
	AfxMessageBox(str);
}


void CDemoMFC10Dlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);

	ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcess(TEXT("C:/WINDOWS/system32/notepad.exe"),
		TEXT(" book.txt"),//命令行参数
		NULL,//进程的安全属性 默认
		NULL,//进程里面的线程安全属性 默认
		FALSE,//继承句柄 不继承
		0,//创建标志
		NULL,//环境变量 使用父进程的环境变量
		NULL,//使用父进程的当前目录 作为子进程的目录
		&si,
		&pi)) {
		CString s;
		s.Format(TEXT("创建进程失败：%d"), GetLastError());
		AfxMessageBox(s);
		return;
	}
}