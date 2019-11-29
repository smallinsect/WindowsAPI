
// DemoMFC05Dlg.cpp: 实现文件
//

#include "stdafx.h"
#include "DemoMFC05.h"
#include "DemoMFC05Dlg.h"
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


// CDemoMFC05Dlg 对话框



CDemoMFC05Dlg::CDemoMFC05Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DEMOMFC05_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDemoMFC05Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDemoMFC05Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDemoMFC05Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDemoMFC05Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDemoMFC05Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CDemoMFC05Dlg 消息处理程序

BOOL CDemoMFC05Dlg::OnInitDialog()
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

void CDemoMFC05Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDemoMFC05Dlg::OnPaint()
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
HCURSOR CDemoMFC05Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDemoMFC05Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR tchData[64];
	HKEY hKey;
	long lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		_T("Hardware\\Description\\System\\CentralProcessor\\0"),
		0,
		KEY_QUERY_VALUE,
		&hKey);
	DWORD dwSize = sizeof(tchData);
	if (lRet == ERROR_SUCCESS) {
		lRet = RegQueryValueEx(hKey,
			_T("ProcessorNameString"),
			NULL,
			NULL,
			(LPBYTE)tchData,
			&dwSize);
		if (lRet == ERROR_SUCCESS) {
			SetDlgItemText(IDC_STATIC, tchData);
		}
		else {
			SetDlgItemText(IDC_STATIC, TEXT("RegQueryValueEx fail ..."));
		}
	}
	else {
		SetDlgItemText(IDC_STATIC, TEXT("RegOpenKeyEx fail ..."));
	}
	RegCloseKey(hKey);
}


void CDemoMFC05Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	HKEY hKey;
	if (RegCreateKey(HKEY_LOCAL_MACHINE,
		_T("Software\\MyAppTest"),
		&hKey)) {
		SetDlgItemText(IDC_STATIC, TEXT("RegCreateKey 创建注册表示失败"));
		return;
	}
	if (RegSetValue(hKey, NULL, REG_SZ, _T("LieBao"), 6)) {
		SetDlgItemText(IDC_STATIC, TEXT("RegSetValue 设置值失败"));
		RegCloseKey(hKey);
		return;
	}
	DWORD dwAge = 30;
	if (RegSetValueEx(hKey, _T("age"), 0, REG_DWORD, (CONST BYTE*)&dwAge, 4)) {
		SetDlgItemText(IDC_STATIC, TEXT("RegSetValueEx 设置值失败"));
		RegCloseKey(hKey);
		return;
	}

	RegCloseKey(hKey);
	SetDlgItemText(IDC_STATIC, TEXT("设置注册表成功"));
}


void CDemoMFC05Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	//LONG lValue;
	//if (RegQueryValue(HKEY_LOCAL_MACHINE,
	//	_T("Software\\MyAppTest"),
	//	NULL,
	//	&lValue)) {
	//	SetDlgItemText(IDC_STATIC, TEXT("RegQueryValue 读取长度失败"));
	//	return;
	//}
	//TCHAR *pBuf = new TCHAR[lValue];
	//if (RegQueryValue(HKEY_LOCAL_MACHINE,
	//	_T("Software\\MyAppTest"),
	//	pBuf,
	//	&lValue)) {
	//	SetDlgItemText(IDC_STATIC, TEXT("RegQueryValue 读取键值失败"));
	//	return;
	//}
	//SetDlgItemText(IDC_STATIC, pBuf);
	//上面和下面的代码 不能同时存在
	HKEY hKey;
	if (RegOpenKey(HKEY_LOCAL_MACHINE,
		_T("Software\\MyAppTest"),
		&hKey)) {
		AfxMessageBox(TEXT("RegOpenKey 失败"));
		return;
	}
	DWORD dwType;
	DWORD dwAge;
	DWORD dwValue;
	if (RegQueryValueEx(hKey,
		_T("age"),
		0,
		&dwType,
		(LPBYTE)&dwAge,
		&dwValue)) {
		AfxMessageBox(TEXT("RegQueryValueEx 失败"));
		RegCloseKey(hKey);
		return;
	}
	CString str;
	str.Format(_T("age = %d"), dwAge);
	AfxMessageBox(str);

	RegCloseKey(hKey);
}
