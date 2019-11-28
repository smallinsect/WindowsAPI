

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

//���ַ��Ͷ��ֽ�֮���ת��
void fun02() {
	DWORD dwNum;
	//���õ�����Ϣ
	setlocale(LC_ALL, "");
	//���ֽ��ַ���
	char szText[] = "���ֽ��ַ���ת���ַ���";//���ֽ��ַ���
	dwNum = MultiByteToWideChar(CP_ACP,//��ת������ASCII
		0,//����λ
		szText,//��ת�����ַ���
		-1,//���� \0 ����
		NULL,//ת������ַ���
		0);//ת������ַ�����
	wchar_t *pwText;
	pwText = new wchar_t[dwNum];
	if (pwText == NULL) {
		return;
	}
	MultiByteToWideChar(CP_ACP, 0, szText, -1, pwText, dwNum);
	wprintf(L"M->W %s\n", pwText);
	delete[] pwText;

	wchar_t szwText[] = L"���ַ�ת���ֽ��ַ���";
	dwNum = WideCharToMultiByte(CP_OEMCP,//��ǰwindows����ʹ�õ��ֽ�
		0,//����λ
		szwText,//��ת���Ŀ��ַ�
		-1,//ĩβ\0����
		NULL,//ת����Ķ��ֽ�
		0,//ת����Ķ��ֽڳ���
		NULL,
		NULL);
	char *psText = new char[dwNum];
	WideCharToMultiByte(CP_OEMCP, 0, szwText, -1, psText, dwNum, NULL, NULL);

	printf("W->M %s\n", psText);
}

#define BUFSIZE 1024

//������
void fun03() {
	printf("************��һ�ֲ��Ҿ�****************\n");
	CHAR szLogicalDriveStrings[BUFSIZE];
	ZeroMemory(szLogicalDriveStrings, BUFSIZE);
	//��ȡ�����̷�
	GetLogicalDriveStrings(BUFSIZE-1, szLogicalDriveStrings);
	//c:\\0d:\\0e:\\0\0 ��ȡ���̷�����
	//printf("%s\n", szLogicalDriveStrings);
	PCHAR szDrive = (PCHAR)szLogicalDriveStrings;
	do {
		printf("%s\n", szDrive);
		szDrive += lstrlen(szDrive) + 1;
	} while (*szDrive != '\0');

	printf("************�ڶ��ֲ��Ҿ�****************\n");
	TCHAR buf[BUFSIZE];
	BOOL bFlag;
	HANDLE hVol = FindFirstVolume(buf, BUFSIZE);
	if (hVol == INVALID_HANDLE_VALUE) {
		printf("no found volumes ...\n");
		return;
	}
	do {
		printf("%s\n", buf);//��ӡ���������豸��
	} while (FindNextVolume(hVol, buf, BUFSIZE));
	bFlag = FindVolumeClose(hVol);
}