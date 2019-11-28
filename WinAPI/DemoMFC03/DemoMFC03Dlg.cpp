
// DemoMFC03Dlg.cpp: 实现文件
//

#include "stdafx.h"
#include "DemoMFC03.h"
#include "DemoMFC03Dlg.h"
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


// CDemoMFC03Dlg 对话框



CDemoMFC03Dlg::CDemoMFC03Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DEMOMFC03_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDemoMFC03Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDemoMFC03Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDemoMFC03Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDemoMFC03Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDemoMFC03Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CDemoMFC03Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CDemoMFC03Dlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CDemoMFC03Dlg 消息处理程序

BOOL CDemoMFC03Dlg::OnInitDialog()
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

void CDemoMFC03Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDemoMFC03Dlg::OnPaint()
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
HCURSOR CDemoMFC03Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDemoMFC03Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//LPTSTR szDirPath = TEXT("c:/dog");//绝对路径
	LPTSTR szDirPath = TEXT("dog");//相对路径
	if (!CreateDirectory(szDirPath, NULL)) {
		SetDlgItemText(IDC_DISPLAY, TEXT("创建目录失败"));
		return;
	}
	SetDlgItemText(IDC_DISPLAY, TEXT("创建目录成功"));
}


void CDemoMFC03Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR szCurrentDirectory[MAX_PATH];
	DWORD dwLen = GetCurrentDirectory(MAX_PATH, szCurrentDirectory);
	if (dwLen == 0) {
		SetDlgItemText(IDC_DISPLAY, TEXT("获取当前目录失败"));
		return;
	}
	SetDlgItemText(IDC_DISPLAY, szCurrentDirectory);
}


void CDemoMFC03Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!SetCurrentDirectory(TEXT("C:/"))) {
		SetDlgItemText(IDC_DISPLAY, TEXT("设置当前目录失败"));
		return;
	}
	SetDlgItemText(IDC_DISPLAY, TEXT("当前目录设置为C:/"));
}


void CDemoMFC03Dlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR szModulePath[MAX_PATH];
	if (!GetModuleFileName(NULL, szModulePath, MAX_PATH)) {
		SetDlgItemText(IDC_DISPLAY, TEXT("获取主模块失败"));
		return;
	}
	SetDlgItemText(IDC_DISPLAY, szModulePath);
}


void CDemoMFC03Dlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	HMODULE hKernel32 = LoadLibrary(TEXT("kernel32.dll"));

	TCHAR szModulePath[MAX_PATH];
	if (!GetModuleFileName(hKernel32, szModulePath, MAX_PATH)) {
		SetDlgItemText(IDC_DISPLAY, TEXT("获取模块失败"));
		return;
	}
	SetDlgItemText(IDC_DISPLAY, szModulePath);
}
