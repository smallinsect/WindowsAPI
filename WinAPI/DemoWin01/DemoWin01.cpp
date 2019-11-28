#include <windows.h>

HINSTANCE g_hInstance;

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	g_hInstance = hInstance;


	TCHAR szClassName[] = TEXT("MainWClass");

	//���崰����
	WNDCLASSEX wcx;
	wcx.cbClsExtra = 0;
	wcx.cbSize = sizeof(wcx);//�������С
	wcx.cbWndExtra = 0;
	wcx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//���ڱ���
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);//���ָ��
	wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);//��ͼ��ͼ��
	wcx.hIconSm = (HICON)LoadImage(hInstance,
		MAKEINTRESOURCE(5),
		IMAGE_ICON,
		GetSystemMetrics(SM_CXSMICON),
		GetSystemMetrics(SM_CYSMICON),
		LR_DEFAULTCOLOR);//Сͼ��
	wcx.hInstance = hInstance;
	wcx.lpfnWndProc = MainWndProc;//��Ϣ����ĺ���
	wcx.lpszClassName = szClassName;//����
	wcx.lpszMenuName = NULL;//�˵�
	wcx.style = CS_HREDRAW | CS_VREDRAW;

	//ע�ᴰ����
	if (!RegisterClassEx(&wcx)) {
		return 1;
	}

	//��������
	HWND hwnd = CreateWindow(szClassName,
		"Hello",//���ڱ���
		WS_OVERLAPPEDWINDOW,//������ʽ
		CW_USEDEFAULT,//����x���� Ĭ��
		CW_USEDEFAULT,//����y���� Ĭ��
		CW_USEDEFAULT,//���ڿ�� Ĭ��
		CW_USEDEFAULT,//���ڸ߶� Ĭ��
		(HWND)NULL,//�����ھ��
		(HMENU)NULL,//���ڲ˵�
		hInstance,//ʵ�����
		(LPVOID)NULL);//
	
	if (!hwnd) {
		return 1;
	}

	ShowWindow(hwnd, nCmdShow);//��ʾ����
	UpdateWindow(hwnd);//ˢ�´���


	MSG msg;
	//��Ϣѭ��
	while ( GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);//������Ϣ
		DispatchMessage(&msg);//ת����Ϣ
	}

	return 0;
}

//������Ϣ ��Ϣ����
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_DESTROY://���ٴ���
		PostQuitMessage(0);//�����˳���Ϣ
		break;
	default:
		break;
	}
	return DefWindowProc( hwnd, uMsg, wParam, lParam);
}