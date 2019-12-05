

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
//ϵͳ��Ϣ
void fun10(int argc, char *argv[]){
	//********************��ȡϵͳ�汾��Ϣ
	//OSVERSIONINFO ovex;
	//TCHAR szVersionInfo[1024] = {0};
	//ovex.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	//if (!GetVersionEx(&ovex)) {
	//	printf("����%d\n", GetLastError());
	//	return;
	//}
	//if (ovex.dwMajorVersion == 5) {
	//	if (ovex.dwMinorVersion == 0) {
	//		lstrcat(szVersionInfo, "Windows 2000");
	//	}
	//	else if (ovex.dwMinorVersion == 1) {
	//		lstrcat(szVersionInfo, "Windows XP");
	//	}
	//	else if (ovex.dwMinorVersion == 2) {
	//		lstrcat(szVersionInfo, "Windows Server 2003");
	//	}
	//}
	//else if (ovex.dwMajorVersion == 6) {
	//	lstrcat(szVersionInfo, "Windows Vista");
	//}
	//else {
	//	lstrcat(szVersionInfo, "Windows ����");
	//}
	//printf("%s\n", szVersionInfo);
	//printf("Windows %d.%d Build %d",
	//	ovex.dwMajorVersion,
	//	ovex.dwMinorVersion,
	//	ovex.dwPlatformId);
	//printf("%s\n", ovex.szCSDVersion);

	//��ȡӲ����Ϣ
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	printf("�ڴ��ҳ��С��0x%.0X�������ڴ���ʼ��0x%.8X�������ڴ��������0x%.8X\n",
		si.dwPageSize,
		si.lpMinimumApplicationAddress,
		si.lpMaximumApplicationAddress);
	printf("������������%d\n", si.dwNumberOfProcessors);
	printf("���������ͣ�\n");
	switch (si.dwProcessorType) {
	case PROCESSOR_INTEL_386:
		printf("386\n");
		break;
	case PROCESSOR_INTEL_486:
		printf("486\n");
		break;
	case PROCESSOR_INTEL_PENTIUM:
		printf("PENTIUM\n");
		break;
	default:
		printf("%d\n", si.dwProcessorType);
		break;
	}
	printf("�������ܹ���");
	switch (si.wProcessorArchitecture) {
	case PROCESSOR_ARCHITECTURE_INTEL:
		printf("INTEL\n");
		break;
	default:
		printf("%d\n", si.wProcessorArchitecture);
		break;
	}
}
//ϵͳ��Ϣ
void fun11(int argc, char *argv[]){
	//ϵͳĿ¼
	TCHAR szSystemDirectory[MAX_PATH];
	GetSystemDirectory(szSystemDirectory, MAX_PATH);
	printf("ϵͳĿ¼��%s\n", szSystemDirectory);

	TCHAR szWindowsDirectory[MAX_PATH];
	GetWindowsDirectory(szWindowsDirectory, MAX_PATH);
	printf("WindowsĿ¼��%s\n", szWindowsDirectory);

	TCHAR szComputerName[MAX_COMPUTERNAME_LENGTH+1];
	DWORD dwComputerNameLength = MAX_COMPUTERNAME_LENGTH + 1;
	GetComputerName(szComputerName, &dwComputerNameLength);
	printf("���������%s\n", szComputerName);

	TCHAR szUserName[64];
	DWORD dwUserNameLength = 64;
	GetUserName(szUserName, &dwUserNameLength);
	printf("�û�����%s\n", szUserName);

	int aMouseInfo[3];
	BOOL fResult = SystemParametersInfo(SPI_GETMOUSE, 0, aMouseInfo, 0);
	if (fResult) {
		aMouseInfo[2] = 2 * aMouseInfo[2];
		SystemParametersInfo(SPI_SETMOUSE, 0, aMouseInfo, SPIF_SENDCHANGE);
	}
}
//ʱ����Ϣ
void fun12(int argc, char *argv[]){
	SYSTEMTIME st;
	GetLocalTime(&st);//��ȡ���ص�ǰʱ��
	printf("%d-%d-%d %d:%d:%d\n",
		st.wYear, st.wMonth, st.wDay,
		st.wHour, st.wMinute, st.wSecond);
	//st.wHour--;
	//SetLocalTime(&st);//���õ�ǰʱ��

	DWORD c1 = GetTickCount();//��ȡ���������ڵ�ʱ��
	ULONGLONG c2 = GetTickCount64();//��ȡ���������ڵ�ʱ��
	printf("%d %lld\n", c1, c2);

}

BOOL CALLBACK EnumFamCallBack(LPLOGFONTA lplf,//�߼�����
	LPTEXTMETRICA lpntm,//��������
	DWORD FontType,//��������
	LPARAM aFontCount)//ö�ٺ��������ص����������� 
{
	PINT aiFontCount = (PINT)aFontCount;
	if (FontType & RASTER_FONTTYPE) {
		printf(" RASTER_FONTTYPE" );
		aiFontCount[0]++;
	}
	else if (FontType & TRUETYPE_FONTTYPE) {
		printf(" TRUETYPE_FONTTYPE");
		aiFontCount[2]++;
	}
	else {
		printf(" VECTORTYPE_FONTTYPE");
		aiFontCount[1]++;
	}
	printf(" %s\tItalic = %d\n", lplf->lfFaceName, lplf->lfItalic);
	return TRUE;
}

//ö������
void fun13(int argc, char *argv[]){
	HDC hdc = GetDC(NULL);//��ȡ����HDC
	//������������
	int aFontCount[] = {0, 0, 0};
	//NULL ö����������
	EnumFontFamilies(hdc, NULL, (FONTENUMPROC)EnumFamCallBack, (LPARAM)aFontCount);//ö����������

	ReleaseDC(NULL, hdc);
	printf("Number of raster fonts: %d\n", aFontCount[0]);
	printf("Number of vector fonts: %d\n", aFontCount[1]);
	printf("Number of TrueType fonts: %d\n", aFontCount[2]);
}
//��������
void fun14(int argc, char *argv[]){
	if (argc == 2 && lstrcmp(argv[1], "showall")) {
		//����������ʽ
		//=::=::\\0ALLUSERSPROFILE=C:\ProgramData\0....
		//��ȡ�������л�������
		LPCH pEv = GetEnvironmentStrings();
		LPTSTR szEnvs = (LPTSTR)pEv;
		while (*szEnvs) {
			printf("%s\n", szEnvs);
			//�ҵ���һ������
			szEnvs = szEnvs + lstrlen(szEnvs) + 1;
			//while (*szEnvs++) {}//�ҵ���һ������
		}
		//�ͷ�ָ��
		FreeEnvironmentStrings(pEv);
	}
	else if (argc == 2 && lstrcmp(argv[1], "addnew")) {
		//��ǰ���򻷾����� ��ӣ��û�����������ϵͳ������������Ӱ��
		if (!SetEnvironmentVariable("a", "b")) {
			printf("���ʧ�� %d\n", GetLastError());
		}
		else {
			printf("��ӳɹ�\n");
		}
	}
	else if (argc == 2 && lstrcmp(argv[1], "delete")) {
		if (!SetEnvironmentVariable("a", NULL)) {
			printf("���ʧ�� %d\n", GetLastError());
		}
		else {
			printf("��ӳɹ�\n");
		}
	}
	else if (argc == 2 && lstrcmp(argv[1], "set")) {
		if (!SetEnvironmentVariable("a", "big")) {
			printf("���ʧ�� %d\n", GetLastError());
		}
		else {
			printf("��ӳɹ�\n");
		}
	}
	else if (argc == 2 && lstrcmp(argv[1], "get")) {
		TCHAR buf[1024];
		if (!GetEnvironmentVariable("a", buf, 1024)) {
			DWORD dwErr = GetLastError();
			if (dwErr == ERROR_ENVVAR_NOT_FOUND) {
				printf("��������������\n");
			}
			printf("���ʧ�� %d\n", dwErr);
		}
		else {
			printf("��ӳɹ�\n");
		}
	}


}
//ö��ϵͳ�еĽ���
void fun15(int argc, char *argv[]){
	//�������̿���
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE) {
		printf("���̿���ʧ��\n");
		return ;
	}
	//������Ϣ
	PROCESSENTRY32 pe = {0};
	pe.dwSize = sizeof(pe);
	//���ҵ�һ������
	BOOL bRet = Process32First(hSnapshot, &pe);
	while(bRet) {
		//��ӡ����ID�ͽ��̵�����
		printf("PID:%d\t����:%s\n", pe.th32ProcessID, pe.szExeFile);
		//������һ������
		bRet = Process32Next(hSnapshot, &pe);
	}
	//�رվ��
	CloseHandle(hSnapshot);
}

BOOL UpdateProcessPrivilege(HANDLE hProcess, LPCTSTR lpRivilegeName = SE_DEBUG_NAME);

//#pragma comment(lib, "psapi.lib")
//ö�ٽ����е�����
void fun16(int argc, char *argv[]) {
	//������ǰ���̵�Ȩ��
	UpdateProcessPrivilege(GetCurrentProcess());

	DWORD PID[1024];//�������н��̵�ID
	DWORD cbNeeded;//ϵͳ��ǰʵ�ʽ�������
	//��ȡ���н��̵�ID
	if (!EnumProcesses(PID, sizeof(PID), &cbNeeded)) {
		printf("��ȡ���н���IDʧ��\n");
		return;
	}
	DWORD processcount = cbNeeded / sizeof(DWORD);//������̸���
	printf("��ǰ����%d������\n", processcount);
	HANDLE hProcess;
	HMODULE hModules[1024];//ģ��
	for (DWORD i = 0; i < processcount; ++i) {
		hProcess = OpenProcess(
			PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,//�򿪽��� ��ѯ��Ϣ ��ȡ��Ϣ
			FALSE,
			PID[i]);
		if (hProcess) {
			printf("PID: %d\n", PID[i]);
			if (EnumProcessModules(hProcess, hModules, sizeof(hModules), &cbNeeded)) {
				for (int j = 0; j < (cbNeeded / sizeof(HMODULE)); ++j) {
					TCHAR szFilename[MAX_PATH];
					DWORD nSize;
					if (GetModuleFileNameEx(hProcess, hModules[j], szFilename, MAX_PATH)) {
						printf("\t%d %s (0x%08x)\n", j, szFilename, hModules[j]);
					}
				}
			}
			else {
				printf("ģ���ʧ��\n");
			}
		}
		else {
			printf("PID: %d �򿪽���ʧ��\n", PID[i]);
		}
		CloseHandle(hProcess);
	}

}
//��������Ȩ��
BOOL UpdateProcessPrivilege(HANDLE hProcess, LPCTSTR lpRivilegeName) {
	HANDLE hToken;
	TOKEN_PRIVILEGES TokenPrivileges;
	if (OpenProcessToken(hProcess, TOKEN_ALL_ACCESS, &hToken)) {
		printf("OpenProcessToken �ɹ�\n");
		LUID destLuid;
		if (LookupPrivilegeValue(NULL, lpRivilegeName, &destLuid)) {
			printf("LookupPrivilegeValue �ɹ�\n");
			TokenPrivileges.PrivilegeCount = 1;
			TokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
			TokenPrivileges.Privileges[0].Luid = destLuid;
			if (AdjustTokenPrivileges(hToken, FALSE, &TokenPrivileges,0,NULL,NULL)) {
				printf("AdjustTokenPrivileges �ɹ�\n");
				return TRUE;
			}
		}
	}
	return FALSE;
}

//windows�ն˷��� 
//windows terminate server
//#include <WtsApi32.h>
#pragma comment(lib, "WtsApi32.lib")
void fun17(int argc, char *argv[]){
	////�������
	//TCHAR szServerName[32] = TEXT("DESKTOP-45J0D6P");
	////����̨������������
	//HANDLE hWtsServer = WTSOpenServer(szServerName);
	//if (hWtsServer == INVALID_HANDLE_VALUE) {
	//	printf("WTSOpenServer ʧ��\n");
	//	return;
	//}
	//�ն˷��������Ϣ
	PWTS_PROCESS_INFO pProcessInfo;
	//���̸���
	DWORD dwCount;
	//if (!WTSEnumerateProcesses(hWtsServer, 0, 1, &pProcessInfo, &dwCount)) {
	if (!WTSEnumerateProcesses(WTS_CURRENT_SERVER_HANDLE, 0, 1, &pProcessInfo, &dwCount)) {
		printf("WTSEnumerateProcesses ʧ��\n");
		return;
	}
	//ö�����н��̵���Ϣ
	for (DWORD i = 0; i < dwCount; ++i) {
		printf("PID:%d\t����:%s\n", pProcessInfo[i].ProcessId, pProcessInfo[i].pProcessName);
	}
	//�ڴ��ͷ�
	WTSFreeMemory(pProcessInfo);
	//�رշ���
	//WTSCloseServer(hWtsServer);
}

typedef DWORD(WINAPI *ZWQUERYSYSTEMINFORMATION)(DWORD, PVOID, DWORD, PDWORD);
#define SystemProcessesAndThreadsInformation 5
typedef struct _SYSTEM_PRCESS_INFORMATION {
	DWORD			NextEntryDelta;
	DWORD			ThreadCount;
	DWORD			Reservedl[6];
	FILETIME		ftCreateTime;
	FILETIME		ftUserTime;
	FILETIME		ftKernelTime;
	UNICODE_STRING	ProcessName;
	DWORD			BasePriority;
	DWORD			ProcessId;
	DWORD			InheritedFromProcessId;
	DWORD			HandleCount;
	DWORD			Reserved2[2];
	DWORD			VmCounters;
	DWORD			dCommintCharge;
	DWORD			ThreadInfos[1];
} SYSTEM_PRCESS_INFORMATION, *PSYSTEM_PRCESS_INFORMATION;
//ö�ٽ�����Ϣ
void fun18(int argc, char *argv[]){
	HMODULE hNtDll = GetModuleHandle(TEXT("ntdll.dll"));
	if (!hNtDll) {
		printf("GetModuleHandle ʧ��\n");
		return;
	}
	ZWQUERYSYSTEMINFORMATION ZwQuerySystemInformation = (ZWQUERYSYSTEMINFORMATION)GetProcAddress(hNtDll, TEXT("ZwQuerySystemInformation"));
	if (ZwQuerySystemInformation == NULL) {
		printf("GetProcAddress ʧ��\n");
		return;
	}

	ULONG cbBuffer = 0x10000;
	LPVOID pBuffer = malloc(cbBuffer);
	if (pBuffer == NULL) {
		printf("malloc ʧ��\n");
		return;
	}

	ZwQuerySystemInformation(SystemProcessesAndThreadsInformation, pBuffer, cbBuffer, NULL);
	//������Ϣ�ṹ pInfo = (������Ϣ�ṹ)pBuffer;
	PSYSTEM_PRCESS_INFORMATION pInfo = (PSYSTEM_PRCESS_INFORMATION)cbBuffer;
	while (true) {
		printf("PID:%d\t����:%ls\n", pInfo->ProcessId, pInfo->ProcessName);
		if (pInfo->NextEntryDelta == 0) {
			break;
		}
		pInfo = (PSYSTEM_PRCESS_INFORMATION)(((PUCHAR)pInfo) + pInfo->NextEntryDelta);
	}
	free(pBuffer);
}
void fun19(int argc, char *argv[]){}
void fun20(int argc, char *argv[]){}
void fun21(int argc, char *argv[]){}
void fun22(int argc, char *argv[]){}
void fun23(int argc, char *argv[]){}
void fun24(int argc, char *argv[]){}
void fun25(int argc, char *argv[]){}
void fun26(int argc, char *argv[]){}
void fun27(int argc, char *argv[]){}
void fun28(int argc, char *argv[]){}
void fun29(int argc, char *argv[]){}