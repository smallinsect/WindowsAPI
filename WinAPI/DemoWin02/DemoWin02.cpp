#include <windows.h>

#include "resource.h"

HINSTANCE g_hInstance;

//LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	g_hInstance = hInstance;

	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, MainDlgProc);

	return 0;
}

INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	BOOL bRet = TRUE;

	switch (uMsg) {
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_BUTTON1://��ť1
			MessageBox(hDlg, TEXT("button 1"), TEXT("С����1"), MB_OK);
			break;
		case IDC_BUTTON2://��ť2
			MessageBox(hDlg, TEXT("button 2"), TEXT("С����2"), MB_OK);
			break;
		default:
			bRet = FALSE;
			break;
		}
		break;
	case WM_LBUTTONDOWN:
		MessageBox(hDlg, TEXT("���ײ˵�С����"), TEXT("С����3"), MB_OK);
		break;
	case WM_CLOSE:
		EndDialog(hDlg, 0);
		break;
	default:
		bRet = FALSE;
		break;
	}

	return bRet;
}