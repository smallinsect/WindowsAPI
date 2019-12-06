#define _CRT_SECURE_NO_WARNINGS

#include <tchar.h>
#include <stdio.h>
#include <Windows.h>
#include <strsafe.h>

#include "resource.h"

INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
PTSTR BigNumToString(LONG lNum, PTSTR szBuf, DWORD chBufSize);
VOID ShowCPUInfo(HWND hWnd, WORD wProcessorArchitecture, WORD wProcessorLevel, WORD wProcessorRevision);

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
	switch (message)
	{
	case WM_INITDIALOG:

		SYSTEM_INFO sinf;
		GetSystemInfo(&sinf);

		TCHAR szBuf[128];
		SetDlgItemText(hDlg, Page_size, BigNumToString(sinf.dwPageSize, szBuf, _countof(szBuf)));
		StringCchPrintf(szBuf, _countof(szBuf), TEXT("%p"), sinf.lpMinimumApplicationAddress);
		SetDlgItemText(hDlg, Minimum_app_address, szBuf);
		StringCchPrintf(szBuf, _countof(szBuf), TEXT("%p"), sinf.lpMaximumApplicationAddress);
		SetDlgItemText(hDlg, Maximum_app_address, szBuf);
		SetDlgItemText(hDlg, Allocation_granularity, BigNumToString(sinf.dwAllocationGranularity, szBuf, _countof(szBuf)));
		//处理器个数
		SetDlgItemText(hDlg, Number_of_processor, BigNumToString(sinf.dwNumberOfProcessors, szBuf, _countof(szBuf)));
		//有几个CPU可以用
		StringCchPrintf(szBuf, _countof(szBuf), TEXT("0x%016I64X"), (__int64)sinf.dwActiveProcessorMask);
		SetDlgItemText(hDlg, Active_processor_mask, szBuf);

		ShowCPUInfo(hDlg, sinf.wProcessorArchitecture, sinf.wProcessorLevel, sinf.wProcessorRevision);
		break;
	case WM_CLOSE:
		EndDialog(hDlg, 0);
		break;
	case WM_COMMAND:
		break;
	default:
		bRet = FALSE;
		break;
	}
	return bRet;
}


PTSTR BigNumToString(LONG lNum, PTSTR szBuf, DWORD chBufSize) {
	TCHAR szNum[128];
	StringCchPrintf(szNum, _countof(szNum), TEXT("%d"), lNum);

	NUMBERFMT nf;//数字格式
	nf.NumDigits = 0;//
	nf.LeadingZero = FALSE;//前导零
	nf.Grouping = 3;//分组 3个一组
	nf.lpDecimalSep = (LPSTR)TEXT(".");//小数点
	nf.lpThousandSep = (LPSTR)TEXT(",");//线分为
	nf.NegativeOrder = 0;

	GetNumberFormat(LOCALE_USER_DEFAULT, 0, szNum, &nf, szBuf, chBufSize);

	return szBuf;
}

VOID ShowCPUInfo(HWND hWnd, 
	WORD wProcessorArchitecture, 
	WORD wProcessorLevel, 
	WORD wProcessorRevision) 
{
	TCHAR szCPUArch[64] = TEXT("unknown");
	TCHAR szCPULevel[64] = TEXT("unknown");
	TCHAR szCPURev[64] = TEXT("unknown");

	switch (wProcessorArchitecture) {
	case PROCESSOR_ARCHITECTURE_INTEL:
		_tcscpy_s(szCPUArch, _countof(szCPUArch), TEXT("Intel"));
		break;
	case PROCESSOR_ARCHITECTURE_IA64:
		_tcscpy_s(szCPUArch, _countof(szCPUArch), TEXT("IA64"));
		break;
	case PROCESSOR_ARCHITECTURE_AMD64:
		_tcscpy_s(szCPUArch, _countof(szCPUArch), TEXT("AMD64"));
		break;
	}
	PROCESSOR_INTEL_PENTIUM;

	SetDlgItemText(hWnd, Processor_Architecture, szCPUArch);
	sprintf(szCPULevel, TEXT("%d"), wProcessorLevel);
	SetDlgItemText(hWnd, Processor_Level, szCPULevel);
	sprintf(szCPURev, TEXT("%d"), wProcessorRevision);
	SetDlgItemText(hWnd, Processor_revision, szCPURev);
}