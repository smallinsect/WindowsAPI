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
		//�б�� ��Ϣ �б��ѡ�з����ı�
		if (LOWORD(wParam) == IDC_LIST1 && HIWORD(wParam) == LBN_SELCHANGE) {
			//��ȡ�б��ѡ�еĵڼ���
			iIndex = SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_GETCURSEL, 0, 0);
			//��ȡ�б��ѡ�е��ַ�������
			iLength = SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_GETTEXTLEN, 0, 0);
			//�ö� �����ڴ�
			pVarName = (TCHAR*)calloc(iLength+1, sizeof(TCHAR));
			//��ȡ�б��е�iIndex������
			SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_GETTEXT, iIndex, (LPARAM)pVarName);
			//��ȡ���������ĳ���
			iLength = GetEnvironmentVariable(pVarName, NULL, 0);
			//�ö� �����ڴ�
			pVarValue = (TCHAR*)calloc(iLength+1, sizeof(TCHAR));
			//��ȡ����������ֵ
			GetEnvironmentVariable(pVarName, pVarValue, iLength+1);
			//�����ı�����ֵ
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
	//TCHAR szBuf[1024];//ʹ��ջ
	////����������
	//TCHAR *pVarBlock = GetEnvironmentStrings();//��ȡ���л�������
	//TCHAR *pVarBeg = pVarBlock;
	//while (*pVarBeg) {
	//	CopyMemory(szBuf, pVarBeg, lstrlen(pVarBeg));
	//	SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)szBuf);
	//	pVarBeg += lstrlen(pVarBeg) + 1;
	//	ZeroMemory(szBuf, 1024);
	//}
	//FreeEnvironmentStrings(pVarBlock);
	
	//TCHAR *pVarName;//ʹ�ö�
	////����������
	//TCHAR *pVarBlock = GetEnvironmentStrings();//��ȡ���л�������
	//TCHAR *pVarBeg = pVarBlock;
	//int iLength;
	//while (*pVarBeg) {
	//int iLength = lstrlen(pVarBeg);
	//	pVarName = (TCHAR*)calloc(iLength+1, sizeof(TCHAR));//�Լ����ʼ��
	//	//pVarName = (TCHAR*)malloc((iLength + 1)*sizeof(TCHAR));
	//	//ZeroMemory(pVarName, (iLength + 1) * sizeof(TCHAR));
	//	CopyMemory(pVarName, pVarBeg, iLength*sizeof(TCHAR));
	//	SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)pVarName);
	//	free(pVarName);//�ͷ��ڴ�
	//	pVarBeg += lstrlen(pVarBeg) + 1;
	//}
	//FreeEnvironmentStrings(pVarBlock);

	TCHAR *pVName;//ʹ��HeapAlloc
	TCHAR *pVarBlock = GetEnvironmentStrings();
	TCHAR *pVarBeg = pVarBlock, *pVarEnd;
	while (*pVarBeg) {
		pVarEnd = pVarBeg;
		while (*pVarEnd != '=') {
			++pVarEnd;
		}
		int iLength = pVarEnd - pVarBeg;
		//��ȡ��ǰ�����ϵĶ� �������ڴ�
		pVName = (TCHAR*)HeapAlloc(GetProcessHeap(), 0, (iLength+1)*sizeof(TCHAR));
		ZeroMemory(pVName, (iLength+1)*sizeof(TCHAR));
		CopyMemory(pVName, pVarBeg, iLength*sizeof(TCHAR));
		SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)pVName);
		//�ͷŵ�ǰ�ڴ��ϵĶ��ڴ�
		HeapFree(GetProcessHeap(), 0, pVName);
		pVarBeg += lstrlen(pVarBeg) + 1;
	}
	FreeEnvironmentStrings(pVarBlock);
}