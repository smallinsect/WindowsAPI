
// DemoMFC11Dlg.h: 头文件
//

#pragma once


// CDemoMFC11Dlg 对话框
class CDemoMFC11Dlg : public CDialogEx
{
// 构造
public:
	CDemoMFC11Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEMOMFC11_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
private:
	CString m_strUserMsg;
public:
	afx_msg void OnBnClickedButton2();
private:
	CString m_strRegMsg;
};
