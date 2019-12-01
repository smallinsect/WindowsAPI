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
	static HWND hList1, hList2, hList3;
	int iIdx, iLen, iCount, iSelect;
	TCHAR *pVarText;

	switch (uMsg) {
	case WM_INITDIALOG:
		break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		hList1 = GetDlgItem(hDlg, IDC_LIST1);
		hList2 = GetDlgItem(hDlg, IDC_LIST2);
		hList3 = GetDlgItem(hDlg, IDC_LIST3);
		switch (wmId) {
		//case IDC_LIST1:
		//	if (wmEvent == LBN_SELCHANGE) {
		//		iIdx = SendMessage(hList1, LB_GETCURSEL,0,0);
		//		iLen = SendMessage(hList1, LB_GETTEXTLEN, iIdx, 0) + 1;
		//		pVarText = (TCHAR *)calloc(iLen, sizeof(TCHAR));
		//		SendMessage(hDlg, LB_GETTEXT, iIdx, (LPARAM)pVarText);
		//		MessageBox(hDlg, pVarText, TEXT("TEST"), MB_OK);
		//	}
		//	break;
		case IDC_BUTTON1:
			SendMessage(hList1, LB_ADDSTRING, 0, (LPARAM)TEXT("hello"));
			SendMessage(hList1, LB_ADDSTRING, 0, (LPARAM)TEXT("windows"));
			SendMessage(hList1, LB_ADDSTRING, 0, (LPARAM)TEXT("apple"));
			break;
		case IDC_BUTTON2://删除
			SendMessage(hList1, LB_DELETESTRING, 1, 0);//删除
			break;
		case IDC_BUTTON3://重置
			SendMessage(hList1, LB_RESETCONTENT, 0, 0);//重置
			break;
		case IDC_BUTTON4://选中
			SendMessage(hList1, LB_SETCURSEL,2, 0);//选中
			break;
		case IDC_BUTTON5://取消
			SendMessage(hList1, LB_SETCURSEL, -1, 0);//取消选中
			break;
		case IDC_BUTTON6://插入
			SendMessage(hList2, LB_INSERTSTRING, -1, (LPARAM)TEXT("hhh"));//插入末尾
			SendMessage(hList2, LB_INSERTSTRING, -1, (LPARAM)TEXT("hhh"));//插入末尾
			SendMessage(hList2, LB_INSERTSTRING, -1, (LPARAM)TEXT("hhh"));//插入末尾
			SendMessage(hList2, LB_INSERTSTRING, -1, (LPARAM)TEXT("hhh"));//插入末尾
			break;
		case IDC_BUTTON7://左边移动到右边
			iIdx = SendMessage(hList1, LB_GETCURSEL, 0, 0);//获取选中下标
			iLen = SendMessage(hList1, LB_GETTEXTLEN, iIdx, 0) + 1;//获取选中行字符串长度
			pVarText = (TCHAR*)calloc(iLen, sizeof(TCHAR));
			SendMessage(hList1, LB_GETTEXT, iIdx, (LPARAM)pVarText);//获取选中的字符串
			SendMessage(hList1, LB_DELETESTRING, iIdx, 0);//删除选中的行
			SendMessage(hList2, LB_INSERTSTRING, -1, (LPARAM)pVarText);//末尾插入字符串
			break;
		case IDC_BUTTON8://多选
			SendMessage(hList2, LB_SETSEL, 1, 2);//选中下标2
			SendMessage(hList2, LB_SETSEL, 1, 5);//选中下标5
			break;
		case IDC_BUTTON9://取消选中
			SendMessage(hList2, LB_SETSEL, 0, 2);//选中下标2
			SendMessage(hList2, LB_SETSEL, 0, 5);//选中下标5
			break;
		case IDC_BUTTON10://全部选中
			SendMessage(hDlg, LB_SETSEL, 1, -1);//1 选中 -1全部选中
			break;
		case IDC_BUTTON11://移动多个
			//列表中全部项目 一共有多少个
			iCount = SendMessage(hList2, LB_GETCOUNT, 0, 0);
			for (iIdx = iCount - 1; iIdx >= 0; iIdx--) {
				iSelect = SendMessage(hList2, LB_GETSEL, iIdx, 0);//获取下标iIdx是否被选中
				if (iSelect != 0) {//被选中
					iLen = SendMessage(hList2, LB_GETTEXTLEN, iIdx, 0)+1;//获取下标iIdx的长度
					pVarText = (TCHAR*)calloc(iLen, sizeof(TCHAR));//分配内存
					SendMessage(hList2, LB_GETTEXT, iIdx, (LPARAM)pVarText);//获取下标iIdx的字符串
					SendMessage(hList2, LB_DELETESTRING, iIdx, 0);//删除下标iIdx的字符串
					SendMessage(hList3, LB_INSERTSTRING, -1, (LPARAM)pVarText);//在list3中末尾插入一行
				}
			}
			break;
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