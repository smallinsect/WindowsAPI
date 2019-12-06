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
	MEMORYSTATUSEX ms = { sizeof(ms) };
	TCHAR szData[512] = { 0 };
	PROCESS_MEMORY_COUNTERS_EX pmc = {sizeof(pmc)};
	switch (message)
	{
	case WM_INITDIALOG:
		SetTimer(hDlg, IDT_UPDATE, 1000, NULL);
		SendMessage(hDlg, WM_TIMER, IDT_UPDATE, 0);
		break;
	case WM_TIMER:
		GlobalMemoryStatusEx(&ms);
		StringCchPrintf(szData, _countof(szData), 
			TEXT("%d\n%lld\n%lld\n%lld\n%lld\n%lld\n%lld\n"),
			ms.dwMemoryLoad,
			ms.ullTotalPhys,
			ms.ullAvailPhys,
			ms.ullTotalPageFile,
			ms.ullAvailPageFile,
			ms.ullTotalVirtual,
			ms.ullAvailVirtual);
		SetDlgItemText(hDlg, IDC_EDIT1, szData);

		GetProcessMemoryInfo(GetCurrentProcess(), (PPROCESS_MEMORY_COUNTERS)&pmc, sizeof(pmc));
		StringCchPrintf(szData, _countof(szData), 
			TEXT("%lldK\n%lldK\n"),
			pmc.WorkingSetSize / 1024,
			pmc.PrivateUsage / 1024);

		SetDlgItemText(hDlg, IDC_EDIT2, szData);
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



