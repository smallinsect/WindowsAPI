

#include "DemoFunc.h"

//��ȡϵͳĿ¼ ��Ŀ¼д���ļ���
void fun01(int argc, char *argv[]) {
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
void fun02(int argc, char *argv[]) {
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


//������
void fun03(int argc, char *argv[]) {
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
void fun04(int argc, char *argv[]) {

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
void fun05(int argc, char *argv[]){
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
//�ļ�ɾ�� �ƶ� ������ ����
void fun06(int argc, char *argv[]){
	//printf("����:%d\n", argc);
	//printf("��һ��:%s\n", argv[0]);
	//printf("�ڶ���:%s\n", argv[1]);
	//printf("������:%s\n", argv[2]);
	
	if (argc == 3 && lstrcmp("-d", argv[1]) == 0) {//-d ɾ���ļ�
		if (DeleteFile(argv[2])) {
			printf("ɾ���ļ��ɹ�\n");
		}
		else {
			printf("ɾ���ļ�ʧ�ܣ�%d\n", GetLastError());
		}
	}
	else if (argc == 4 && lstrcmp("-c", argv[1]) == 0) {//-c �����ļ�
		if (CopyFile(argv[2], argv[3], TRUE)) {//TRUE ����ʱ ���ļ����ڣ�������
			printf("�����ļ��ɹ�\n");
		}
		else {//˵���ļ����ˣ��Ƿ񸲸�
			if (GetLastError() == 0x50) {
				printf("�ļ�%s�Ѿ����ڣ��Ƿ񸲸ǣ�y/n:", argv[3]);
				if ('y' == getchar()) {
					if (CopyFile(argv[2], argv[3], FALSE)) {//FALSE ����ʱ ���ļ����ڣ�ֱ�Ӹ���
						printf("�����ļ��ɹ�\n");
					}
					else {
						printf("�����ļ�ʧ�ܣ�%d\n", GetLastError());
					}
				}
				else {
					return;
				}
			}
		}
	}
	else if (argc == 4 && lstrcmp("-m", argv[1]) == 0) {//-m �ƶ��ļ�
		if (MoveFile(argv[2], argv[3])) {
			printf("���ļ������ɹ�\n");
		}
		else {
			printf("���ļ�����������%d\n", GetLastError());
		}
	}
	else {//��������
		printf("��������\n");
	}
}
//�ļ����� C �� API
void fun07(int argc, char *argv[]){
	if (argc < 3) {
		printf(" Demo01 a.txt b.txt\n");
		return;
	}
	//********************C�����ļ�************************
	//FILE *pRFile = fopen(argv[1], "rb");
	//if (pRFile == NULL) {
	//	perror(argv[1]);
	//	return;
	//}
	//FILE *pWFile = fopen(argv[2], "wb");
	//if (pWFile == NULL) {
	//	perror(argv[2]);
	//	return;
	//}
	//char buf[BUFSIZE];
	//size_t rSize, wSize;
	//while ((rSize = fread(buf, 1, BUFSIZE, pRFile)) > 0) {
	//	wSize = fwrite(buf, 1, rSize, pWFile);
	//	if (rSize != wSize) {
	//		perror("Fetal write error.");
	//		return;
	//	}
	//}

	//fclose(pRFile);
	//fclose(pWFile);
	//********************C�����ļ�************************

	//********************API�����ļ�************************
	HANDLE hRead = CreateFile(argv[1],
		GENERIC_READ,//���ļ� ��
		FILE_SHARE_READ,//�򿪹����ļ� ��
		NULL,
		OPEN_EXISTING,//���Ѵ��ڵ��ļ�
		FILE_ATTRIBUTE_NORMAL,//�����ļ�����
		NULL);
	if (hRead == INVALID_HANDLE_VALUE) {
		printf("���ļ�����%d\n", GetLastError());
		return;
	}
	HANDLE hWrite = CreateFile(argv[2],
		GENERIC_WRITE,//���ļ� д
		0,// 0������ FILE_SHARE_WRITE,//���� д
		NULL,
		CREATE_ALWAYS,//���Ǵ����µ��ļ�
		FILE_ATTRIBUTE_NORMAL,//�����ļ�
		NULL);
	if (hWrite == INVALID_HANDLE_VALUE) {
		printf("����ļ�����%d\n", GetLastError());
		return;
	}
	DWORD dwRead, dwWrite;
	CHAR buffer[BUFSIZE];
	while (ReadFile(hRead, buffer, BUFSIZE, &dwRead, NULL) && dwRead > 0) {
		WriteFile(hWrite, buffer, dwRead, &dwWrite, NULL);
		if (dwRead != dwWrite) {
			printf("д�ļ������ش��� %d\n", GetLastError());
			return;
		}
	}
	CloseHandle(hRead);
	CloseHandle(hWrite);
	//********************API�����ļ�************************
}

//����Ŀ¼
void fun08(int argc, char *argv[]){
	WIN32_FIND_DATA findFileData;

	HANDLE hFindFile = FindFirstFile(TEXT("c:/*"), &findFileData);
	if (hFindFile == INVALID_HANDLE_VALUE) {
		printf("����%d\n", GetLastError());
		return;
	}
	do {
		printf("%s\t\t", findFileData.cFileName);
		if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_ENCRYPTED) {
			printf("<����>");
		}
		if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) {
			printf("<����>");
		}
		if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			printf("<DIR>");
		}
		printf("\n");
	} while (FindNextFile(hFindFile, &findFileData));
}
//��ʾʱ��
void ShowFileTime(PFILETIME lptime) {
	FILETIME ftLocal;
	FileTimeToLocalFileTime(lptime, &ftLocal);//��׼ʱ��ת���ɱ���ʱ��
	SYSTEMTIME st;
	FileTimeToSystemTime(&ftLocal, &st);//����ʱ��ת����ϵͳʱ�䣬ϵͳʱ����������ʱ���룬����ʱ����һ���ܴ����
	printf("%4d��%02d��%02d�գ�%02d:%02d:%02d\n", 
		st.wYear, st.wMonth, st.wDay,
		st.wHour, st.wMinute, st.wSecond);
}
//�����ļ���С
void ShowFileSize(DWORD dwFileSizeHigh, DWORD dwFileSizeLow) {
	ULONGLONG liFileSize;
	liFileSize = dwFileSizeHigh;
	liFileSize <<= 32;
	liFileSize += dwFileSizeLow;
	printf("�ļ���С��%I64u\n", liFileSize);
}
//��ʾ�ļ�����
void ShowFileAttrInfo(DWORD dwFileAttributes) {
	if (dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) {
		printf(" ARCHIVE");
	}
	else if (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
		printf(" DIRECTORY");
	}
	else if (dwFileAttributes & FILE_ATTRIBUTE_READONLY) {
		printf(" READONLY");
	}
}
//�ļ����Ժ�ʱ��
void fun09(int argc, char *argv[]){
	
	TCHAR szFile[] = TEXT("book.txt");
	WIN32_FILE_ATTRIBUTE_DATA wfad;
	if (!GetFileAttributesEx(szFile, GetFileExInfoStandard, &wfad)) {
		printf("��ȡ�ļ�����ʧ�ܣ�%d\n", GetLastError());
		return;
	}
	printf("����ʱ�䣺");
	ShowFileTime(&(wfad.ftCreationTime));
	printf("����ʱ�䣺");
	ShowFileTime(&(wfad.ftLastAccessTime));
	printf("�޸�ʱ�䣺");
	ShowFileTime(&(wfad.ftLastWriteTime));
	ShowFileSize(wfad.nFileSizeHigh, wfad.nFileSizeLow);
	ShowFileAttrInfo(wfad.dwFileAttributes);

	//��ȡ�����ļ�����
	//DWORD dwFileAttributes = GetFileAttributes(szFile);
	//dwFileAttributes |= FILE_ATTRIBUTE_READONLY;
	//dwFileAttributes |= FILE_ATTRIBUTE_HIDDEN;
	//if (SetFileAttributes(szFile, dwFileAttributes)) {
	//	printf("�ļ� %s �����غ�ֻ���������óɹ�\n", szFile);
	//}
	//else {
	//	printf("��������ʧ�ܣ�%d\n", GetLastError());
	//}
}
void fun10(int argc, char *argv[]){}