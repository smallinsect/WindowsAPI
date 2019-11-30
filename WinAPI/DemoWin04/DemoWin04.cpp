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

	static HWND hwndEdit1, hwndEdit2;
	static TCHAR buf[1024];

	switch (uMsg) {
	case WM_COMMAND:
		hwndEdit1 = GetDlgItem(hDlg, IDC_EDIT1);
		hwndEdit2 = GetDlgItem(hDlg, IDC_EDIT2);
		switch (LOWORD(wParam)) {
		case IDC_BUTTON1://按钮1 弹出消息
			switch (HIWORD(wParam)) {//消息控制码
			case BN_CLICKED:
				//MessageBox(hDlg, TEXT("111"), TEXT("2222"), MB_OK);
				SendMessage(hwndEdit1, WM_CLEAR, 0 , 0);
				break;
			case BN_SETFOCUS:
				break;
			}
			break;
		case IDC_BUTTON2:
			switch (HIWORD(wParam)) {//消息控制码
			case BN_CLICKED:
				SendMessage(hwndEdit1, WM_COPY, 0, 0);
				break;
			}
			break;
		case IDC_BUTTON3:
			switch (HIWORD(wParam)) {//消息控制码
			case BN_CLICKED:
				SendMessage(hwndEdit1, WM_PASTE, 0, 0);
				break;
			}
			break;
		case IDC_BUTTON4:
			GetWindowText(hwndEdit1, buf, 1024);
			MessageBox(hDlg, buf, buf, MB_OK);
			break;
		case IDC_BUTTON5:
			SetWindowText(hwndEdit2, TEXT("hello"));
			break;
		case IDC_EDIT1:
			switch (HIWORD(wParam)) {//消息控制码
			case EN_MAXTEXT:
				break;
			case EN_ERRSPACE:
				break;
			case EN_UPDATE:
				GetWindowText(hwndEdit1, buf, 1024);
				SetWindowText(hwndEdit2, buf);
				break;
			}
			break;
		default:
			return DefWindowProc(hDlg, uMsg, wParam, lParam);
		}
		break;
	case WM_LBUTTONDOWN:
		//MessageBox(hDlg, TEXT("爱白菜的小昆虫"), TEXT("小昆虫3"), MB_OK);
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