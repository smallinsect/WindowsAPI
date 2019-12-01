

#include <windows.h>

#include "DemoDll01.h"

//入口点 出口点
int WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, PVOID pvReserved) {

	switch (fdwReason) {
	case DLL_PROCESS_ATTACH://映射进程 加载DLL
		MessageBox(NULL, TEXT("DLL_PROCESS_ATTACH"), TEXT("提示"), MB_OK);
		break;
	case DLL_PROCESS_DETACH://释放DLL
		MessageBox(NULL, TEXT("DLL_PROCESS_DETACH"), TEXT("提示"), MB_OK);
		break;
	case DLL_THREAD_ATTACH://新建线程 加载DLL
		MessageBox(NULL, TEXT("DLL_THREAD_ATTACH"), TEXT("提示"), MB_OK);
		break;
	case DLL_THREAD_DETACH://线程退出 释放DLL
		MessageBox(NULL, TEXT("DLL_THREAD_DETACH"), TEXT("提示"), MB_OK);
		break;
	}

	return TRUE;
}

EXPORT
BOOL CALLBACK EdrCenterTextA(HDC hdc, PRECT prc, PCSTR pString) {
	int iLength = lstrlenA(pString);
	SIZE size;
	GetTextExtentPoint32A(hdc, pString, iLength, &size);//获取字体的宽度高度
	return TextOutA(hdc, 
		(prc->right - prc->left - size.cx)/2,
		(prc->bottom - prc->top - size.cy)/2,
		pString, iLength);
}

EXPORT
BOOL CALLBACK EdrCenterTextW(HDC hdc, PRECT prc, PCWSTR pString) {
	int iLength = lstrlenW(pString);
	SIZE size;
	GetTextExtentPoint32W(hdc, pString, iLength, &size);//获取字体的宽度高度
	return TextOutW(hdc,
		(prc->right - prc->left - size.cx) / 2,
		(prc->bottom - prc->top - size.cy) / 2,
		pString, iLength);
}