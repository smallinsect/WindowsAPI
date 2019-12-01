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

void PaintTheBlock(HWND hwnd, COLORREF drawColor, int iFigure) {
	RECT rect;
	GetClientRect(hwnd, &rect);

	InvalidateRect(hwnd, NULL, TRUE);//子窗口失效
	UpdateWindow(hwnd);

	HDC hdc = GetDC(hwnd);
	HBRUSH hBrush = CreateSolidBrush(drawColor);
	hBrush = (HBRUSH)SelectObject(hdc, hBrush);
	if (iFigure == IDC_Ellipse) {
		Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);
	}
	else {
		Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
	}
	DeleteObject(SelectObject(hdc, hBrush));
	ReleaseDC(hwnd, hdc);
}

INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	BOOL bRet = TRUE;

	static HWND hCtrlBlock;
	static TCHAR buf[1024];
	static int iFigure;
	static COLORREF drawColor;

	switch (uMsg) {
	case WM_INITDIALOG:
		hCtrlBlock = GetDlgItem(hDlg, IDC_PAINT);
		iFigure = IDC_Rectangle;
		drawColor = RGB(0, 0, 0);
		SendMessage(GetDlgItem(hDlg, IDC_Black), BM_SETCHECK, 1, 0);
		SendDlgItemMessage(hDlg, IDC_Rectangle, BM_SETCHECK, 1, 0);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_Black:
			drawColor = RGB(0, 0, 0);
			break;
		case IDC_Blue:
			drawColor = RGB(0, 0, 255);
			break;
		case IDC_Green:
			drawColor = RGB(0, 255, 0);
			break;
		case IDC_Rectangle:
			iFigure = IDC_Rectangle;
			break;
		case IDC_Ellipse:
			iFigure = IDC_Ellipse;
			break;
		}
		PaintTheBlock(hCtrlBlock, drawColor, iFigure);
		break;
	case WM_PAINT:
		PaintTheBlock(hCtrlBlock, drawColor, iFigure);
		bRet = FALSE;
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