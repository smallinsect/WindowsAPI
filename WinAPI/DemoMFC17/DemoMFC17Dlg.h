
// DemoMFC17Dlg.h: 头文件
//

#pragma once


// CDemoMFC17Dlg 对话框
class CDemoMFC17Dlg : public CDialogEx
{
// 构造
public:
	CDemoMFC17Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEMOMFC17_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	//内存映射文件
	HANDLE m_hMapObject;
	LPTSTR m_pszMapView;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
private:
	CString m_strSend;
};
