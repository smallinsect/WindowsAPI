
// DemoMFC06Dlg.cpp: 实现文件
//

#include "stdafx.h"
#include "DemoMFC06.h"
#include "DemoMFC06Dlg.h"
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


// CDemoMFC06Dlg 对话框



CDemoMFC06Dlg::CDemoMFC06Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DEMOMFC06_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDemoMFC06Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDemoMFC06Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDemoMFC06Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDemoMFC06Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDemoMFC06Dlg 消息处理程序

BOOL CDemoMFC06Dlg::OnInitDialog()
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

void CDemoMFC06Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDemoMFC06Dlg::OnPaint()
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
HCURSOR CDemoMFC06Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

VOID GdiOut(HDC hdc) {
	HPEN hPen, hPenOld;//画笔
	HBRUSH hBrush, hBrushOld;//画刷

	BYTE bRed = 255;
	BYTE bGreen = 0;
	BYTE bBlue = 0;
	COLORREF cPen = RGB(bRed, bGreen, bBlue);
	COLORREF cBrush = RGB(233, 0, 255);
	hPen = CreatePen(PS_SOLID, 10, cPen);//创建画笔 画笔实心 画笔大小10 画笔颜色红色
	hBrush = CreateSolidBrush(cBrush);//创建画刷

	hPenOld = (HPEN)SelectObject(hdc, hPen);//绑定画笔
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);//绑定画刷

	::LineTo(hdc, 200, 200);
	::Rectangle(hdc, 100, 50, 200, 300);

	hPen = (HPEN)SelectObject(hdc, hPenOld);//还原画笔
	hBrush = (HBRUSH)SelectObject(hdc, hBrushOld);//还原画刷

	DeleteObject(hPen);
	DeleteObject(hBrush);
}

void CDemoMFC06Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	HWND hwnd = GetSafeHwnd();//获取当前窗口句柄
	HDC hdc = ::GetDC(hwnd);//获取当前窗口DC
	GdiOut(hdc);
	::ReleaseDC(hwnd, hdc);//释放DC
}


void CDemoMFC06Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	HDC hdc = ::GetDC(NULL);//获取桌面的DC
	GdiOut(hdc);
	::ReleaseDC(NULL, hdc);//释放桌面DC
}
