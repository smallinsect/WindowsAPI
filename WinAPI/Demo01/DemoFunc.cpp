

#include "DemoFunc.h"

//获取系统目录 将目录写入文件中
void fun01() {
	TCHAR szSystemDir[MAX_PATH];
	//获取系统目录
	GetSystemDirectory(szSystemDir, MAX_PATH);

	printf("%s\n", szSystemDir);

	HANDLE hFile = CreateFile("systemroot.txt",
		GENERIC_WRITE,
		0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		printf("open file error ...\n");
		return;
	}
	printf("open file success ...\n");
	DWORD dwWritten;//实际写入字节数
	if (!WriteFile(hFile, szSystemDir, lstrlen(szSystemDir), &dwWritten, NULL)) {
		printf("write file error ...\n");
	}
	printf("write file success ...\n");
	CloseHandle(hFile);
}

//宽字符和多字节之间的转换
void fun02() {
	DWORD dwNum;
	//配置地域信息
	setlocale(LC_ALL, "");
	//多字节字符串
	char szText[] = "多字节字符串转宽字符串";//多字节字符串
	dwNum = MultiByteToWideChar(CP_ACP,//被转换的是ASCII
		0,//控制位
		szText,//被转换的字符串
		-1,//遇到 \0 结束
		NULL,//转换后的字符串
		0);//转换后的字符长度
	wchar_t *pwText;
	pwText = new wchar_t[dwNum];
	if (pwText == NULL) {
		return;
	}
	MultiByteToWideChar(CP_ACP, 0, szText, -1, pwText, dwNum);
	wprintf(L"M->W %s\n", pwText);
	delete[] pwText;

	wchar_t szwText[] = L"宽字符转换字节字符串";
	dwNum = WideCharToMultiByte(CP_OEMCP,//当前windows正在使用的字节
		0,//控制位
		szwText,//被转换的宽字符
		-1,//末尾\0结束
		NULL,//转换后的多字节
		0,//转换后的多字节长度
		NULL,
		NULL);
	char *psText = new char[dwNum];
	WideCharToMultiByte(CP_OEMCP, 0, szwText, -1, psText, dwNum, NULL, NULL);

	printf("W->M %s\n", psText);
}