

#include <windows.h>

#include "DemoDll01.h"

//��ڵ� ���ڵ�
int WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, PVOID pvReserved) {

	switch (fdwReason) {
	case DLL_PROCESS_ATTACH://ӳ����� ����DLL
		MessageBox(NULL, TEXT("DLL_PROCESS_ATTACH"), TEXT("��ʾ"), MB_OK);
		break;
	case DLL_PROCESS_DETACH://�ͷ�DLL
		MessageBox(NULL, TEXT("DLL_PROCESS_DETACH"), TEXT("��ʾ"), MB_OK);
		break;
	case DLL_THREAD_ATTACH://�½��߳� ����DLL
		MessageBox(NULL, TEXT("DLL_THREAD_ATTACH"), TEXT("��ʾ"), MB_OK);
		break;
	case DLL_THREAD_DETACH://�߳��˳� �ͷ�DLL
		MessageBox(NULL, TEXT("DLL_THREAD_DETACH"), TEXT("��ʾ"), MB_OK);
		break;
	}

	return TRUE;
}

EXPORT
BOOL CALLBACK EdrCenterTextA(HDC hdc, PRECT prc, PCSTR pString) {
	int iLength = lstrlenA(pString);
	SIZE size;
	GetTextExtentPoint32A(hdc, pString, iLength, &size);//��ȡ����Ŀ�ȸ߶�
	return TextOutA(hdc, 
		(prc->right - prc->left - size.cx)/2,
		(prc->bottom - prc->top - size.cy)/2,
		pString, iLength);
}

EXPORT
BOOL CALLBACK EdrCenterTextW(HDC hdc, PRECT prc, PCWSTR pString) {
	int iLength = lstrlenW(pString);
	SIZE size;
	GetTextExtentPoint32W(hdc, pString, iLength, &size);//��ȡ����Ŀ�ȸ߶�
	return TextOutW(hdc,
		(prc->right - prc->left - size.cx) / 2,
		(prc->bottom - prc->top - size.cy) / 2,
		pString, iLength);
}