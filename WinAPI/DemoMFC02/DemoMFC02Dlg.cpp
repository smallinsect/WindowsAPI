
// DemoMFC02Dlg.cpp: 实现文件
//

#include "stdafx.h"
#include "DemoMFC02.h"
#include "DemoMFC02Dlg.h"
#include "afxdialogex.h"

#include <fstream>

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


// CDemoMFC02Dlg 对话框



CDemoMFC02Dlg::CDemoMFC02Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DEMOMFC02_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDemoMFC02Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDemoMFC02Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDemoMFC02Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDemoMFC02Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDemoMFC02Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CDemoMFC02Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CDemoMFC02Dlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CDemoMFC02Dlg 消息处理程序

BOOL CDemoMFC02Dlg::OnInitDialog()
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

void CDemoMFC02Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDemoMFC02Dlg::OnPaint()
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
HCURSOR CDemoMFC02Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDemoMFC02Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString s("*********C*********\r\n");
	char line[256];
	FILE *pFile = fopen("book.txt", "r");
	if (!pFile) {
		MessageBox(TEXT("文件打开失败"));
		return;
	}
	while (fgets(line, 256, pFile) != NULL) {
		s += line;
		s += TEXT("\r\n");
	}
	fclose(pFile);
	SetDlgItemText( IDC_EDIT1, s);
}

void CDemoMFC02Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString s("*********C++*********\r\n");
	char line[256];
	std::ifstream ifs("book.txt");
	if (ifs.fail()) {
		MessageBox(TEXT("文件打开失败"));
		return;
	}
	while (ifs.getline(line, 256)) {
		s += line;
		s += TEXT("\r\n");
	}
	ifs.close();
	SetDlgItemText(IDC_EDIT1, s);
}


void CDemoMFC02Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CString s("*********API*********\r\n");
	HANDLE hFile = CreateFile(TEXT("book.txt"),
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		MessageBox(TEXT("文件打开失败"));
		return;
	}
	CHAR lpFileDataBuffer[4096];
	ZeroMemory(lpFileDataBuffer, 4096);
	DWORD dwReadedSize;//实际读取长度
	ReadFile(hFile, lpFileDataBuffer, 4096, &dwReadedSize, NULL);
	CloseHandle(hFile);
	s += lpFileDataBuffer;
	SetDlgItemText(IDC_EDIT1, s);
}

void CDemoMFC02Dlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	char *old_locale = _strdup(setlocale(LC_ALL, ""));
	//setlocale(LC_ALL, "");
	CString s("*********MFC*********\r\n");
	CStdioFile file(TEXT("book.txt"), CFile::modeRead);
	CString line;
	while (file.ReadString(line)) {
		s += line;
		s += TEXT("\r\n");
	}
	file.Close();
	SetDlgItemText(IDC_EDIT1, s);

	setlocale(LC_ALL, old_locale);
	free(old_locale);
}

void CDemoMFC02Dlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	SetDlgItemText(IDC_EDIT1, TEXT(""));
}