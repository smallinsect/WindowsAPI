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
		case IDC_BUTTON2://ɾ��
			SendMessage(hList1, LB_DELETESTRING, 1, 0);//ɾ��
			break;
		case IDC_BUTTON3://����
			SendMessage(hList1, LB_RESETCONTENT, 0, 0);//����
			break;
		case IDC_BUTTON4://ѡ��
			SendMessage(hList1, LB_SETCURSEL,2, 0);//ѡ��
			break;
		case IDC_BUTTON5://ȡ��
			SendMessage(hList1, LB_SETCURSEL, -1, 0);//ȡ��ѡ��
			break;
		case IDC_BUTTON6://����
			SendMessage(hList2, LB_INSERTSTRING, -1, (LPARAM)TEXT("hhh"));//����ĩβ
			SendMessage(hList2, LB_INSERTSTRING, -1, (LPARAM)TEXT("hhh"));//����ĩβ
			SendMessage(hList2, LB_INSERTSTRING, -1, (LPARAM)TEXT("hhh"));//����ĩβ
			SendMessage(hList2, LB_INSERTSTRING, -1, (LPARAM)TEXT("hhh"));//����ĩβ
			break;
		case IDC_BUTTON7://����ƶ����ұ�
			iIdx = SendMessage(hList1, LB_GETCURSEL, 0, 0);//��ȡѡ���±�
			iLen = SendMessage(hList1, LB_GETTEXTLEN, iIdx, 0) + 1;//��ȡѡ�����ַ�������
			pVarText = (TCHAR*)calloc(iLen, sizeof(TCHAR));
			SendMessage(hList1, LB_GETTEXT, iIdx, (LPARAM)pVarText);//��ȡѡ�е��ַ���
			SendMessage(hList1, LB_DELETESTRING, iIdx, 0);//ɾ��ѡ�е���
			SendMessage(hList2, LB_INSERTSTRING, -1, (LPARAM)pVarText);//ĩβ�����ַ���
			break;
		case IDC_BUTTON8://��ѡ
			SendMessage(hList2, LB_SETSEL, 1, 2);//ѡ���±�2
			SendMessage(hList2, LB_SETSEL, 1, 5);//ѡ���±�5
			break;
		case IDC_BUTTON9://ȡ��ѡ��
			SendMessage(hList2, LB_SETSEL, 0, 2);//ѡ���±�2
			SendMessage(hList2, LB_SETSEL, 0, 5);//ѡ���±�5
			break;
		case IDC_BUTTON10://ȫ��ѡ��
			SendMessage(hDlg, LB_SETSEL, 1, -1);//1 ѡ�� -1ȫ��ѡ��
			break;
		case IDC_BUTTON11://�ƶ����
			//�б���ȫ����Ŀ һ���ж��ٸ�
			iCount = SendMessage(hList2, LB_GETCOUNT, 0, 0);
			for (iIdx = iCount - 1; iIdx >= 0; iIdx--) {
				iSelect = SendMessage(hList2, LB_GETSEL, iIdx, 0);//��ȡ�±�iIdx�Ƿ�ѡ��
				if (iSelect != 0) {//��ѡ��
					iLen = SendMessage(hList2, LB_GETTEXTLEN, iIdx, 0)+1;//��ȡ�±�iIdx�ĳ���
					pVarText = (TCHAR*)calloc(iLen, sizeof(TCHAR));//�����ڴ�
					SendMessage(hList2, LB_GETTEXT, iIdx, (LPARAM)pVarText);//��ȡ�±�iIdx���ַ���
					SendMessage(hList2, LB_DELETESTRING, iIdx, 0);//ɾ���±�iIdx���ַ���
					SendMessage(hList3, LB_INSERTSTRING, -1, (LPARAM)pVarText);//��list3��ĩβ����һ��
				}
			}
			break;
		}
		break;
	case WM_LBUTTONDOWN:
		//MessageBox(hDlg, TEXT("���ײ˵�С����"), TEXT("С����3"), MB_OK);
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