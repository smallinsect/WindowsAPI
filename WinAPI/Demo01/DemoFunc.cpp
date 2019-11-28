

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

//��ȡ��������
void fun04() {

	UINT uDriveType = GetDriveType("C:/");
	printf("%d\n", uDriveType);
	switch (uDriveType) {
	case DRIVE_UNKNOWN://δ֪��
		break;
	case DRIVE_NO_ROOT_DIR://��Чֵ
		break;
	case DRIVE_REMOVABLE://���ƶ������̣�����U�̡�
		break;
	case DRIVE_FIXED://Ӳ��
		break;
	case DRIVE_REMOTE://Զ�̣�ͨ�����繲�������
		break;
	case DRIVE_CDROM://����
		break;
	case DRIVE_RAMDISK://���̣�U��
		break;
	default:
		break;
	}

	CHAR szDriveName[MAX_PATH];
	DWORD dwVolumeSerialNumber;
	DWORD dwMaximumComponentLength;
	DWORD dwFileSystemFlags;
	CHAR szFileSystemNameBuffer[MAX_PATH];
	if (!GetVolumeInformation("d:/",
		szDriveName, MAX_PATH,
		&dwVolumeSerialNumber,//Ӳ�����к�
		&dwMaximumComponentLength,//Ӳ���ַ�������
		&dwFileSystemFlags,//�����������Ϣ
		szFileSystemNameBuffer,//�ļ�ϵͳ���� NTFS
		MAX_PATH)) 
	{
		printf("��ȡ��Ϣʧ��\n");
		return;
	}
	if (lstrlen(szDriveName) > 0) {
		printf("Drive Name is %s\n", szDriveName);//��� 
	}
	printf("%d\n", dwVolumeSerialNumber);//Ӳ�����к�
	printf("%d\n", dwMaximumComponentLength);//�ļ����
	printf("%s\n", szFileSystemNameBuffer);//�ļ�ϵͳ����
	if (dwFileSystemFlags & FILE_VOLUME_QUOTAS) {//���
	}
}

//��������
void fun05(){
	printf("************��һ�ֻ�ȡ��������****************\n");
	DWORD dwTotalClusters;//�� ��
	DWORD dwFreeClusters;//���� ��
	DWORD dwSectPerClust;//ÿ�����ж��ٸ�����
	DWORD dwBytesPerSect;//ÿ�������ж��ٸ��ֽ�
	BOOL bResult = GetDiskFreeSpace("C:",
		&dwSectPerClust,
		&dwBytesPerSect,
		&dwFreeClusters,
		&dwTotalClusters);
	if (bResult) {
		printf("��ȡ���̿ռ���Ϣ\n");
		printf("�ܴ�������      %d\n", dwTotalClusters);
		printf("���еĴ�������  %d\n", dwFreeClusters);
		printf("ÿ�ص�����������%d\n", dwSectPerClust);
		printf("ÿ�����ֽ�����  %d\n", dwBytesPerSect);
		printf("������������    %I64d\n", (DWORD64)dwTotalClusters*dwSectPerClust*dwBytesPerSect);
		printf("���̿���������  %I64d\n", (DWORD64)dwFreeClusters*dwSectPerClust*dwBytesPerSect);
	}

	printf("************�ڶ��ֻ�ȡ��������****************\n");
	
	DWORD64 qwFreeBytes, qwFreeBytesToCaller, qwTotalBytes;
	bResult = GetDiskFreeSpaceEx("C:",
		(PULARGE_INTEGER)&qwFreeBytesToCaller,
		(PULARGE_INTEGER)&qwTotalBytes,
		(PULARGE_INTEGER)&qwFreeBytes);
	if (bResult) {
		printf("��ȡ���̿ռ���Ϣ\n");
		printf("������������      %I64d\n", qwTotalBytes);
		printf("���ô��̿���������%I64d\n", qwFreeBytes);
		printf("���̿���������    %I64d\n", qwFreeBytesToCaller);
	}

}
void fun06(){}
void fun07(){}
void fun08(){}
void fun09(){}
void fun10(){}