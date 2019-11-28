#include <windows.h>

HINSTANCE g_hInstance;

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	g_hInstance = hInstance;


	TCHAR szClassName[] = TEXT("MainWClass");

	//定义窗口类
	WNDCLASSEX wcx;
	wcx.cbClsExtra = 0;
	wcx.cbSize = sizeof(wcx);//窗口类大小
	wcx.cbWndExtra = 0;
	wcx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//窗口背景
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);//鼠标指针
	wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);//大图标图标
	wcx.hIconSm = (HICON)LoadImage(hInstance,
		MAKEINTRESOURCE(5),
		IMAGE_ICON,
		GetSystemMetrics(SM_CXSMICON),
		GetSystemMetrics(SM_CYSMICON),
		LR_DEFAULTCOLOR);//小图标
	wcx.hInstance = hInstance;
	wcx.lpfnWndProc = MainWndProc;//消息处理的函数
	wcx.lpszClassName = szClassName;//类名
	wcx.lpszMenuName = NULL;//菜单
	wcx.style = CS_HREDRAW | CS_VREDRAW;

	//注册窗口类
	if (!RegisterClassEx(&wcx)) {
		return 1;
	}

	//创建窗口
	HWND hwnd = CreateWindow(szClassName,
		"Hello",//窗口标题
		WS_OVERLAPPEDWINDOW,//窗口样式
		CW_USEDEFAULT,//窗口x坐标 默认
		CW_USEDEFAULT,//窗口y坐标 默认
		CW_USEDEFAULT,//窗口宽度 默认
		CW_USEDEFAULT,//窗口高度 默认
		(HWND)NULL,//父窗口句柄
		(HMENU)NULL,//窗口菜单
		hInstance,//实力句柄
		(LPVOID)NULL);//
	
	if (!hwnd) {
		return 1;
	}

	ShowWindow(hwnd, nCmdShow);//显示窗口
	UpdateWindow(hwnd);//刷新窗口


	MSG msg;
	//消息循环
	while ( GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);//翻译消息
		DispatchMessage(&msg);//转发消息
	}

	return 0;
}

//窗口消息 消息处理
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_DESTROY://销毁窗口
		PostQuitMessage(0);//发送退出消息
		break;
	default:
		break;
	}
	return DefWindowProc( hwnd, uMsg, wParam, lParam);
}