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
	int wmId, wmEvent;
	static HWND hList1;
	int iIdx, iLen;
	TCHAR *pVarText;

	switch (uMsg) {
	case WM_INITDIALOG:
		break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		hList1 = GetDlgItem(hDlg, IDC_LIST1);
		switch (wmId) {
		case IDC_LIST1:
			if (wmEvent == LBN_SELCHANGE) {
				iIdx = SendMessage(hList1, LB_GETCURSEL,0,0);
				iLen = SendMessage(hList1, LB_GETTEXTLEN, iIdx, 0) + 1;
				pVarText = (TCHAR *)calloc(iLen, sizeof(TCHAR));
				SendMessage(hDlg, LB_GETTEXT, iIdx, (LPARAM)pVarText);
				MessageBox(hDlg, pVarText, TEXT("TEST"), MB_OK);
			}
			break;
		case IDC_BUTTON1:
			SendMessage(hList1, LB_ADDSTRING, 0, (LPARAM)TEXT("hello"));
			SendMessage(hList1, LB_ADDSTRING, 0, (LPARAM)TEXT("windows"));
			SendMessage(hList1, LB_ADDSTRING, 0, (LPARAM)TEXT("apple"));
			break;
		case IDC_BUTTON2:
			SendMessage(hList1, LB_DELETESTRING, 1, 0);
			break;
		case IDC_BUTTON3:
			SendMessage(hList1, LB_RESETCONTENT, 0, 0);
			break;
		case IDC_BUTTON4:
			SendMessage(hList1, LB_SETCURSEL,2, 0);
			break;
		case IDC_BUTTON5:
			SendMessage(hList1, LB_SETCURSEL, -1, 0);
			break;
		}
		break;
	case WM_LBUTTONDOWN:
		//MessageBox(hDlg, TEXT("°®°×²ËµÄÐ¡À¥³æ"), TEXT("Ð¡À¥³æ3"), MB_OK);
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