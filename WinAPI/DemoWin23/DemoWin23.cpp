#define _CRT_SECURE_NO_WARNINGS

#include <tchar.h>
#include <stdio.h>
#include <Windows.h>
#include <strsafe.h>
#include <Psapi.h>

#pragma comment(lib, "Psapi.lib")

#include "resource.h"

#define IDT_UPDATE 1

INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
VOID FillListBox(HWND hWnd);

int APIENTRY wWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR    lpCmdLine,
	int       nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, MainDlgProc);
	return 0;
}


INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	BOOL bRet = TRUE;
	int iIndex, iLength;
	TCHAR *pVarName, *pVarValue;
	switch (message)
	{
	case WM_INITDIALOG:
		//SetTimer(hDlg, IDT_UPDATE, 1000, NULL);
		//SendMessage(hDlg, WM_TIMER, IDT_UPDATE, 0);
		FillListBox(GetDlgItem(hDlg, IDC_LIST1));
		break;
	case WM_TIMER:

		break;
	case WM_CLOSE:
		EndDialog(hDlg, 0);
		break;
	case WM_COMMAND:
		//列表框 消息 列表框选中发生改变
		if (LOWORD(wParam) == IDC_LIST1 && HIWORD(wParam) == LBN_SELCHANGE) {
			//获取列表框选中的第几行
			iIndex = SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_GETCURSEL, 0, 0);
			//获取列表框选中的字符串长度
			iLength = SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_GETTEXTLEN, 0, 0);
			//用堆 分配内存
			pVarName = (TCHAR*)calloc(iLength+1, sizeof(TCHAR));
			//获取列表中的iIndex行数据
			SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_GETTEXT, iIndex, (LPARAM)pVarName);
			//获取环境变量的长度
			iLength = GetEnvironmentVariable(pVarName, NULL, 0);
			//用堆 分配内存
			pVarValue = (TCHAR*)calloc(iLength+1, sizeof(TCHAR));
			//获取环境变量的值
			GetEnvironmentVariable(pVarName, pVarValue, iLength+1);
			//设置文本区的值
			SetWindowText(GetDlgItem(hDlg, IDC_EDIT1), pVarValue);

			free(pVarValue);
			free(pVarName);
		}
		break;
	default:
		bRet = FALSE;
		break;
	}
	return bRet;
}

VOID FillListBox(HWND hWnd) {
	//TCHAR szBuf[1024];//使用栈
	////环境变量块
	//TCHAR *pVarBlock = GetEnvironmentStrings();//获取所有环境变量
	//TCHAR *pVarBeg = pVarBlock;
	//while (*pVarBeg) {
	//	CopyMemory(szBuf, pVarBeg, lstrlen(pVarBeg));
	//	SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)szBuf);
	//	pVarBeg += lstrlen(pVarBeg) + 1;
	//	ZeroMemory(szBuf, 1024);
	//}
	//FreeEnvironmentStrings(pVarBlock);
	
	//TCHAR *pVarName;//使用堆
	////环境变量块
	//TCHAR *pVarBlock = GetEnvironmentStrings();//获取所有环境变量
	//TCHAR *pVarBeg = pVarBlock;
	//int iLength;
	//while (*pVarBeg) {
	//int iLength = lstrlen(pVarBeg);
	//	pVarName = (TCHAR*)calloc(iLength+1, sizeof(TCHAR));//自己会初始化
	//	//pVarName = (TCHAR*)malloc((iLength + 1)*sizeof(TCHAR));
	//	//ZeroMemory(pVarName, (iLength + 1) * sizeof(TCHAR));
	//	CopyMemory(pVarName, pVarBeg, iLength*sizeof(TCHAR));
	//	SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)pVarName);
	//	free(pVarName);//释放内存
	//	pVarBeg += lstrlen(pVarBeg) + 1;
	//}
	//FreeEnvironmentStrings(pVarBlock);

	TCHAR *pVName;//使用HeapAlloc
	TCHAR *pVarBlock = GetEnvironmentStrings();
	TCHAR *pVarBeg = pVarBlock, *pVarEnd;
	while (*pVarBeg) {
		pVarEnd = pVarBeg;
		while (*pVarEnd != '=') {
			++pVarEnd;
		}
		int iLength = pVarEnd - pVarBeg;
		//获取当前进程上的堆 并分配内存
		pVName = (TCHAR*)HeapAlloc(GetProcessHeap(), 0, (iLength+1)*sizeof(TCHAR));
		ZeroMemory(pVName, (iLength+1)*sizeof(TCHAR));
		CopyMemory(pVName, pVarBeg, iLength*sizeof(TCHAR));
		SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)pVName);
		//释放当前内存上的堆内存
		HeapFree(GetProcessHeap(), 0, pVName);
		pVarBeg += lstrlen(pVarBeg) + 1;
	}
	FreeEnvironmentStrings(pVarBlock);
}