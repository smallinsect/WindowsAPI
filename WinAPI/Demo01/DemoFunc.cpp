

#include "DemoFunc.h"

//��ȡϵͳĿ¼ ��Ŀ¼д���ļ���
void fun01() {
	TCHAR szSystemDir[MAX_PATH];
	//��ȡϵͳĿ¼
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
	DWORD dwWritten;//ʵ��д���ֽ���
	if (!WriteFile(hFile, szSystemDir, lstrlen(szSystemDir), &dwWritten, NULL)) {
		printf("write file error ...\n");
	}
	printf("write file success ...\n");
	CloseHandle(hFile);
}