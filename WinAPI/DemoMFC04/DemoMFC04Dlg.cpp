
// DemoMFC04Dlg.cpp: 实现文件
//

#include "stdafx.h"
#include "DemoMFC04.h"
#include "DemoMFC04Dlg.h"
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


// CDemoMFC04Dlg 对话框



CDemoMFC04Dlg::CDemoMFC04Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DEMOMFC04_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDemoMFC04Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDemoMFC04Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CDemoMFC04Dlg 消息处理程序

BOOL CDemoMFC04Dlg::OnInitDialog()
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

	LoadFile(TEXT("a.txt"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDemoMFC04Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDemoMFC04Dlg::OnPaint()
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
HCURSOR CDemoMFC04Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDemoMFC04Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}

BOOL CDemoMFC04Dlg::LoadFile(CString strFileName) {
	HANDLE hFile = CreateFile(strFileName,
		GENERIC_READ,
		FILE_SHARE_READ,
		0,//文件安全属性
		OPEN_EXISTING,//打开已存在的文件
		FILE_FLAG_SEQUENTIAL_SCAN,//序列读
		0);
	if (hFile == INVALID_HANDLE_VALUE) {
		MessageBox(TEXT("打开文件失败"));
		return FALSE;
	}
	HANDLE hMapping = CreateFileMapping(hFile,
		0,//文件安全属性
		PAGE_READONLY,//文件页 只读
		0,0,//打开的文件内存和文件大小一样
		NULL);//可以设置多个线程访问
	if (hMapping == INVALID_HANDLE_VALUE) {
		MessageBox(TEXT("文件映射失败"));
		CloseHandle(hFile);
		return FALSE;
	}
	PVOID basepointer = MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, 0);
	if (basepointer == NULL) {
		MessageBox(TEXT("映射失败"));
		CloseHandle(hMapping);
		CloseHandle(hFile);
		return FALSE;
	}

	CString str;
	str = (LPTSTR)basepointer;
	SetDlgItemText(IDC_EDIT_TEXT, str);

	UnmapViewOfFile(basepointer);
	CloseHandle(hMapping);
	CloseHandle(hFile);
	return TRUE;
}