﻿
// DemoMFC12Dlg.h: 头文件
//

#pragma once


// CDemoMFC12Dlg 对话框
class CDemoMFC12Dlg : public CDialogEx
{
// 构造
public:
	CDemoMFC12Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEMOMFC12_DIALOG };
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
	afx_msg LRESULT OnUserReceiveMsg(WPARAM, LPARAM);
	afx_msg LRESULT OnRegReceiveMsg(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
private:
	CString m_strUserMsg;
	CString m_strRegMsg;
};
