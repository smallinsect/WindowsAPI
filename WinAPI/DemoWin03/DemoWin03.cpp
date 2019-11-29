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

	static HWND hButton;
	static HWND hCheckBox;
	static HWND hRadioButton;
	int iCheck;
	TCHAR buf[128];


	switch (uMsg) {
	case WM_COMMAND:
		hButton = GetDlgItem(hDlg, IDC_BUTTON1);
		hCheckBox = GetDlgItem(hDlg, IDC_CHECK1);
		hRadioButton = GetDlgItem(hDlg, IDC_RADIO1);

		switch (LOWORD(wParam)) {
		case IDC_BUTTON1://按钮1 弹出消息
			MessageBox(hDlg, TEXT("button 1"), TEXT("小昆虫1"), MB_OK);
			break;
		case IDC_BUTTON2://按钮2 设置单选框 复选框 选中
			SendMessage(hCheckBox, BM_SETCHECK, 1, 0);
			SendMessage(hRadioButton, BM_SETCHECK, 1, 0);
			break;
		case IDC_BUTTON3://按钮3 设置 单选框 复选框 未选中
			SendMessage(hCheckBox, BM_SETCHECK, 0, 0);
			SendMessage(hRadioButton, BM_SETCHECK, 0, 0);
			break;
		case IDC_BUTTON4://按钮4 获取单选框 复选框 是否选中
			iCheck = (int)SendMessage(hCheckBox, BM_GETCHECK, 0, 0);
			if (iCheck) {
				MessageBox(hDlg, TEXT("check 选中"), TEXT("提示"), MB_OK);
			}
			else {
				MessageBox(hDlg, TEXT("check 没选中"), TEXT("提示"), MB_OK);
			}
			iCheck = (int)SendMessage(hRadioButton, BM_GETCHECK, 0, 0);
			if (iCheck) {
				MessageBox(hDlg, TEXT("radio 选中"), TEXT("提示"), MB_OK);
			}
			else {
				MessageBox(hDlg, TEXT("radio 没选中"), TEXT("提示"), MB_OK);
			}
			break;
		case IDC_BUTTON5://按钮5 修改按键的文本
			SetWindowText(hButton, TEXT("hello"));
			SetWindowText(hCheckBox, TEXT("hello"));
			SetWindowText(hRadioButton, TEXT("hello"));
			break;
		case IDC_BUTTON6://按钮6 获取按键的文本
			GetWindowText(hButton, buf, 128);
			MessageBox(hDlg, buf, TEXT("提示"), MB_OK);
			//GetWindowText(hCheckBox, buf, 128);
			//GetWindowText(hRadioButton, buf, 128);
			break;
		case IDC_BUTTON7://按钮7 设置 显示和隐藏控件
			if (IsWindowVisible(hButton)) {
				ShowWindow(hButton, SW_HIDE);
			}
			else {
				ShowWindow(hButton, SW_SHOW);
			}
			break;
		case IDC_BUTTON8://按钮8 设置 控件禁用 启用
			//if (IsWindowEnabled(hButton)) {
			//	EnableWindow(hButton, FALSE);
			//}
			//else {
			//	EnableWindow(hButton, TRUE);
			//}
			IsWindowEnabled(hButton) ? EnableWindow(hButton, FALSE) : EnableWindow(hButton, TRUE);
			break;
		default:
			return DefWindowProc(hDlg, uMsg, wParam, lParam);
		}
		break;
	case WM_LBUTTONDOWN:
		MessageBox(hDlg, TEXT("爱白菜的小昆虫"), TEXT("小昆虫3"), MB_OK);
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