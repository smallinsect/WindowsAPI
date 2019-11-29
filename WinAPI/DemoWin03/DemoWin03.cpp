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
		case IDC_BUTTON1://��ť1 ������Ϣ
			MessageBox(hDlg, TEXT("button 1"), TEXT("С����1"), MB_OK);
			break;
		case IDC_BUTTON2://��ť2 ���õ�ѡ�� ��ѡ�� ѡ��
			SendMessage(hCheckBox, BM_SETCHECK, 1, 0);
			SendMessage(hRadioButton, BM_SETCHECK, 1, 0);
			break;
		case IDC_BUTTON3://��ť3 ���� ��ѡ�� ��ѡ�� δѡ��
			SendMessage(hCheckBox, BM_SETCHECK, 0, 0);
			SendMessage(hRadioButton, BM_SETCHECK, 0, 0);
			break;
		case IDC_BUTTON4://��ť4 ��ȡ��ѡ�� ��ѡ�� �Ƿ�ѡ��
			iCheck = (int)SendMessage(hCheckBox, BM_GETCHECK, 0, 0);
			if (iCheck) {
				MessageBox(hDlg, TEXT("check ѡ��"), TEXT("��ʾ"), MB_OK);
			}
			else {
				MessageBox(hDlg, TEXT("check ûѡ��"), TEXT("��ʾ"), MB_OK);
			}
			iCheck = (int)SendMessage(hRadioButton, BM_GETCHECK, 0, 0);
			if (iCheck) {
				MessageBox(hDlg, TEXT("radio ѡ��"), TEXT("��ʾ"), MB_OK);
			}
			else {
				MessageBox(hDlg, TEXT("radio ûѡ��"), TEXT("��ʾ"), MB_OK);
			}
			break;
		case IDC_BUTTON5://��ť5 �޸İ������ı�
			SetWindowText(hButton, TEXT("hello"));
			SetWindowText(hCheckBox, TEXT("hello"));
			SetWindowText(hRadioButton, TEXT("hello"));
			break;
		case IDC_BUTTON6://��ť6 ��ȡ�������ı�
			GetWindowText(hButton, buf, 128);
			MessageBox(hDlg, buf, TEXT("��ʾ"), MB_OK);
			//GetWindowText(hCheckBox, buf, 128);
			//GetWindowText(hRadioButton, buf, 128);
			break;
		case IDC_BUTTON7://��ť7 ���� ��ʾ�����ؿؼ�
			if (IsWindowVisible(hButton)) {
				ShowWindow(hButton, SW_HIDE);
			}
			else {
				ShowWindow(hButton, SW_SHOW);
			}
			break;
		case IDC_BUTTON8://��ť8 ���� �ؼ����� ����
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