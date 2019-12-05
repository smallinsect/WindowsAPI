
// DemoMFC09Dlg.cpp: 实现文件
//

#include "stdafx.h"
#include "DemoMFC09.h"
#include "DemoMFC09Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//临界区对象
CCriticalSection* g_pCS;
//互斥量对象
CMutex* g_pMutex;
//信号量
CSemaphore* g_pSemaphore;
//事件
CEvent* g_pEvent;

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


// CDemoMFC09Dlg 对话框



CDemoMFC09Dlg::CDemoMFC09Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DEMOMFC09_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//创建临界区对象
	g_pCS = new CCriticalSection();
	//创建互斥量
	g_pMutex = new CMutex();
	//信号量
	g_pSemaphore = new CSemaphore(1, 1);
	//事件
	g_pEvent = new CEvent(TRUE);

}
CDemoMFC09Dlg::~CDemoMFC09Dlg() {
	//释放临界区对象
	delete g_pCS;
	g_pCS = NULL;
	//释放互斥量
	delete g_pMutex;
	g_pMutex = NULL;
	//释放信号量
	delete g_pSemaphore;
	g_pSemaphore = NULL;
	//释放信号量
	delete g_pEvent;
	g_pEvent = NULL;
}


void CDemoMFC09Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDemoMFC09Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDemoMFC09Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDemoMFC09Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDemoMFC09Dlg 消息处理程序

BOOL CDemoMFC09Dlg::OnInitDialog()
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

void CDemoMFC09Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDemoMFC09Dlg::OnPaint()
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
HCURSOR CDemoMFC09Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#define MAX_NUM 1000000
int k = 1;
int total = 0;


UINT ThreadProcA(LPVOID pParam) {
	::SetDlgItemText(AfxGetApp()->m_pMainWnd->m_hWnd,
		IDC_OUTPUTA, TEXT("线程A启动"));
	//临界区
	//for (int i = 1; i <= MAX_NUM; ++i) {
	//	//加锁
	//	g_pCS->Lock();
	//	k = k * 2;
	//	k = k / 2;
	//	total += k;
	//	//解锁
	//	g_pCS->Unlock();
	//}
	//互斥量
	//CSingleLock singleLock(g_pMutex);
	//for (int i = 1; i <= MAX_NUM; ++i) {
	//	//加锁
	//	singleLock.Lock();
	//	if (singleLock.IsLocked()) {//如果锁住了，就执行
	//		k = k * 2;
	//		k = k / 2;
	//		total += k;
	//		//解锁
	//		singleLock.Unlock();
	//	}
	//}
	//信号量
	//CSingleLock singleLock(g_pSemaphore);
	//for (int i = 1; i <= MAX_NUM; ++i) {
	//	//加锁
	//	singleLock.Lock();
	//	if (singleLock.IsLocked()) {//如果锁住了，就执行
	//		k = k * 2;
	//		k = k / 2;
	//		total += k;
	//		//解锁
	//		singleLock.Unlock();
	//	}
	//}


	//事件
	CSingleLock singleLock(g_pEvent);
	for (int i = 1; i <= MAX_NUM; ++i) {
		//加锁
		singleLock.Lock();
		if (singleLock.IsLocked()) {//如果锁住了，就执行
			k = k * 2;
			k = k / 2;
			total += k;
			//解锁
			singleLock.Unlock();
			g_pEvent->SetEvent();//发信号给其他线程
		}
	}
	::SetDlgItemInt(AfxGetApp()->m_pMainWnd->m_hWnd,
		IDC_OUTPUT, total, false);
	return 0;
}
UINT ThreadProcB(LPVOID pParam) {
	::SetDlgItemText(AfxGetApp()->m_pMainWnd->m_hWnd,
		IDC_OUTPUTB, TEXT("线程B启动"));
	//临界区
	//for (int j = 1; j <= MAX_NUM; ++j) {
	//	//加锁
	//	g_pCS->Lock();
	//	k = k * 2;
	//	k = k / 2;
	//	total += k;
	//	//解锁
	//	g_pCS->Unlock();
	//}

	//互斥量
	//CSingleLock singleLock(g_pMutex);
	//for (int j = 1; j <= MAX_NUM; ++j) {
	//	//加锁
	//	singleLock.Lock();
	//	if (singleLock.IsLocked()) {//如果锁住，就执行
	//		k = k * 2;
	//		k = k / 2;
	//		total += k;
	//		//解锁
	//		singleLock.Unlock();
	//	}
	//}

	//信号量
	//CSingleLock singleLock(g_pSemaphore);
	//for (int j = 1; j <= MAX_NUM; ++j) {
	//	//加锁
	//	singleLock.Lock();
	//	if (singleLock.IsLocked()) {//如果锁住，就执行
	//		k = k * 2;
	//		k = k / 2;
	//		total += k;
	//		//解锁
	//		singleLock.Unlock();
	//	}
	//}

	//事件
	CSingleLock singleLock(g_pEvent); 
	for (int j = 1; j <= MAX_NUM; ++j) {
		//加锁
		singleLock.Lock();
		if (singleLock.IsLocked()) {//如果锁住，就执行
			k = k * 2;
			k = k / 2;
			total += k;
			//解锁
			singleLock.Unlock();
			g_pEvent->SetEvent();//发信号给其他线程
		}
	}
	::SetDlgItemInt(AfxGetApp()->m_pMainWnd->m_hWnd,
		IDC_OUTPUT, total, false);
	return 0;
}

void CDemoMFC09Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	AfxBeginThread(ThreadProcA, NULL);
	AfxBeginThread(ThreadProcB, NULL);
}

void CDemoMFC09Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	AfxBeginThread(ThreadProcB, NULL);
}
