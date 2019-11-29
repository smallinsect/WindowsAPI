

#include "DemoFunc.h"

//获取系统目录 将目录写入文件中
void fun01(int argc, char *argv[]) {
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
void fun02(int argc, char *argv[]) {
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


//遍历卷
void fun03(int argc, char *argv[]) {
	printf("************第一种查找卷****************\n");
	CHAR szLogicalDriveStrings[BUFSIZE];
	ZeroMemory(szLogicalDriveStrings, BUFSIZE);
	//获取所有盘符
	GetLogicalDriveStrings(BUFSIZE-1, szLogicalDriveStrings);
	//c:\\0d:\\0e:\\0\0 获取的盘符样子
	//printf("%s\n", szLogicalDriveStrings);
	PCHAR szDrive = (PCHAR)szLogicalDriveStrings;
	do {
		printf("%s\n", szDrive);
		szDrive += lstrlen(szDrive) + 1;
	} while (*szDrive != '\0');

	printf("************第二种查找卷****************\n");
	TCHAR buf[BUFSIZE];
	BOOL bFlag;
	HANDLE hVol = FindFirstVolume(buf, BUFSIZE);
	if (hVol == INVALID_HANDLE_VALUE) {
		printf("no found volumes ...\n");
		return;
	}
	do {
		printf("%s\n", buf);//打印出来的是设备名
	} while (FindNextVolume(hVol, buf, BUFSIZE));
	bFlag = FindVolumeClose(hVol);
}

//获取驱动属性
void fun04(int argc, char *argv[]) {

	UINT uDriveType = GetDriveType("C:/");
	printf("%d\n", uDriveType);
	switch (uDriveType) {
	case DRIVE_UNKNOWN://未知盘
		break;
	case DRIVE_NO_ROOT_DIR://无效值
		break;
	case DRIVE_REMOVABLE://可移动的软盘，例如U盘。
		break;
	case DRIVE_FIXED://硬盘
		break;
	case DRIVE_REMOTE://远程，通过网络共享过来的
		break;
	case DRIVE_CDROM://光盘
		break;
	case DRIVE_RAMDISK://闪盘，U盘
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
		&dwVolumeSerialNumber,//硬盘序列号
		&dwMaximumComponentLength,//硬盘字符串长度
		&dwFileSystemFlags,//更多的属性信息
		szFileSystemNameBuffer,//文件系统名称 NTFS
		MAX_PATH)) 
	{
		printf("获取信息失败\n");
		return;
	}
	if (lstrlen(szDriveName) > 0) {
		printf("Drive Name is %s\n", szDriveName);//卷标 
	}
	printf("%d\n", dwVolumeSerialNumber);//硬盘序列号
	printf("%d\n", dwMaximumComponentLength);//文件名最长
	printf("%s\n", szFileSystemNameBuffer);//文件系统类型
	if (dwFileSystemFlags & FILE_VOLUME_QUOTAS) {//配合
	}
}

//磁盘容量
void fun05(int argc, char *argv[]){
	printf("************第一种获取磁盘容量****************\n");
	DWORD dwTotalClusters;//总 簇
	DWORD dwFreeClusters;//空余 簇
	DWORD dwSectPerClust;//每个簇有多少个扇区
	DWORD dwBytesPerSect;//每个扇区有多少个字节
	BOOL bResult = GetDiskFreeSpace("C:",
		&dwSectPerClust,
		&dwBytesPerSect,
		&dwFreeClusters,
		&dwTotalClusters);
	if (bResult) {
		printf("获取磁盘空间信息\n");
		printf("总簇数量：      %d\n", dwTotalClusters);
		printf("空闲的簇数量：  %d\n", dwFreeClusters);
		printf("每簇的扇区数量：%d\n", dwSectPerClust);
		printf("每扇区字节数：  %d\n", dwBytesPerSect);
		printf("磁盘总容量：    %I64d\n", (DWORD64)dwTotalClusters*dwSectPerClust*dwBytesPerSect);
		printf("磁盘空闲容量：  %I64d\n", (DWORD64)dwFreeClusters*dwSectPerClust*dwBytesPerSect);
	}

	printf("************第二种获取磁盘容量****************\n");
	
	DWORD64 qwFreeBytes, qwFreeBytesToCaller, qwTotalBytes;
	bResult = GetDiskFreeSpaceEx("C:",
		(PULARGE_INTEGER)&qwFreeBytesToCaller,
		(PULARGE_INTEGER)&qwTotalBytes,
		(PULARGE_INTEGER)&qwFreeBytes);
	if (bResult) {
		printf("获取磁盘空间信息\n");
		printf("磁盘总容量：      %I64d\n", qwTotalBytes);
		printf("可用磁盘空闲容量：%I64d\n", qwFreeBytes);
		printf("磁盘空闲容量：    %I64d\n", qwFreeBytesToCaller);
	}

}
//文件删除 移动 重命名 操作
void fun06(int argc, char *argv[]){
	//printf("个数:%d\n", argc);
	//printf("第一个:%s\n", argv[0]);
	//printf("第二个:%s\n", argv[1]);
	//printf("第三个:%s\n", argv[2]);
	
	if (argc == 3 && lstrcmp("-d", argv[1]) == 0) {//-d 删除文件
		if (DeleteFile(argv[2])) {
			printf("删除文件成功\n");
		}
		else {
			printf("删除文件失败：%d\n", GetLastError());
		}
	}
	else if (argc == 4 && lstrcmp("-c", argv[1]) == 0) {//-c 复制文件
		if (CopyFile(argv[2], argv[3], TRUE)) {//TRUE 复制时 有文件存在，不覆盖
			printf("复制文件成功\n");
		}
		else {//说明文件有了，是否覆盖
			if (GetLastError() == 0x50) {
				printf("文件%s已经存在，是否覆盖？y/n:", argv[3]);
				if ('y' == getchar()) {
					if (CopyFile(argv[2], argv[3], FALSE)) {//FALSE 复制时 有文件存在，直接覆盖
						printf("复制文件成功\n");
					}
					else {
						printf("复制文件失败：%d\n", GetLastError());
					}
				}
				else {
					return;
				}
			}
		}
	}
	else if (argc == 4 && lstrcmp("-m", argv[1]) == 0) {//-m 移动文件
		if (MoveFile(argv[2], argv[3])) {
			printf("名文件重命成功\n");
		}
		else {
			printf("名文件重命名错误：%d\n", GetLastError());
		}
	}
	else {//参数错误
		printf("参数错误！\n");
	}
}
//文件复制 C 和 API
void fun07(int argc, char *argv[]){
	if (argc < 3) {
		printf(" Demo01 a.txt b.txt\n");
		return;
	}
	//********************C复制文件************************
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
	//********************C复制文件************************

	//********************API复制文件************************
	HANDLE hRead = CreateFile(argv[1],
		GENERIC_READ,//打开文件 读
		FILE_SHARE_READ,//打开共享文件 读
		NULL,
		OPEN_EXISTING,//打开已存在的文件
		FILE_ATTRIBUTE_NORMAL,//常规文件属性
		NULL);
	if (hRead == INVALID_HANDLE_VALUE) {
		printf("打开文件错误：%d\n", GetLastError());
		return;
	}
	HANDLE hWrite = CreateFile(argv[2],
		GENERIC_WRITE,//打开文件 写
		0,// 0不共享 FILE_SHARE_WRITE,//共享 写
		NULL,
		CREATE_ALWAYS,//总是创建新的文件
		FILE_ATTRIBUTE_NORMAL,//常规文件
		NULL);
	if (hWrite == INVALID_HANDLE_VALUE) {
		printf("输出文件错误：%d\n", GetLastError());
		return;
	}
	DWORD dwRead, dwWrite;
	CHAR buffer[BUFSIZE];
	while (ReadFile(hRead, buffer, BUFSIZE, &dwRead, NULL) && dwRead > 0) {
		WriteFile(hWrite, buffer, dwRead, &dwWrite, NULL);
		if (dwRead != dwWrite) {
			printf("写文件，严重错误 %d\n", GetLastError());
			return;
		}
	}
	CloseHandle(hRead);
	CloseHandle(hWrite);
	//********************API复制文件************************
}

//遍历目录
void fun08(int argc, char *argv[]){
	WIN32_FIND_DATA findFileData;

	HANDLE hFindFile = FindFirstFile(TEXT("c:/*"), &findFileData);
	if (hFindFile == INVALID_HANDLE_VALUE) {
		printf("错误：%d\n", GetLastError());
		return;
	}
	do {
		printf("%s\t\t", findFileData.cFileName);
		if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_ENCRYPTED) {
			printf("<加密>");
		}
		if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) {
			printf("<隐藏>");
		}
		if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			printf("<DIR>");
		}
		printf("\n");
	} while (FindNextFile(hFindFile, &findFileData));
}
//显示时间
void ShowFileTime(PFILETIME lptime) {
	FILETIME ftLocal;
	FileTimeToLocalFileTime(lptime, &ftLocal);//标准时间转换成本地时间
	SYSTEMTIME st;
	FileTimeToSystemTime(&ftLocal, &st);//本地时间转换成系统时间，系统时间有年月日时分秒，本地时间是一个很大的数
	printf("%4d年%02d月%02d日，%02d:%02d:%02d\n", 
		st.wYear, st.wMonth, st.wDay,
		st.wHour, st.wMinute, st.wSecond);
}
//计算文件大小
void ShowFileSize(DWORD dwFileSizeHigh, DWORD dwFileSizeLow) {
	ULONGLONG liFileSize;
	liFileSize = dwFileSizeHigh;
	liFileSize <<= 32;
	liFileSize += dwFileSizeLow;
	printf("文件大小：%I64u\n", liFileSize);
}
//显示文件属性
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
//文件属性和时间
void fun09(int argc, char *argv[]){
	
	TCHAR szFile[] = TEXT("book.txt");
	WIN32_FILE_ATTRIBUTE_DATA wfad;
	if (!GetFileAttributesEx(szFile, GetFileExInfoStandard, &wfad)) {
		printf("获取文件属性失败：%d\n", GetLastError());
		return;
	}
	printf("创建时间：");
	ShowFileTime(&(wfad.ftCreationTime));
	printf("访问时间：");
	ShowFileTime(&(wfad.ftLastAccessTime));
	printf("修改时间：");
	ShowFileTime(&(wfad.ftLastWriteTime));
	ShowFileSize(wfad.nFileSizeHigh, wfad.nFileSizeLow);
	ShowFileAttrInfo(wfad.dwFileAttributes);

	//获取所有文件属性
	//DWORD dwFileAttributes = GetFileAttributes(szFile);
	//dwFileAttributes |= FILE_ATTRIBUTE_READONLY;
	//dwFileAttributes |= FILE_ATTRIBUTE_HIDDEN;
	//if (SetFileAttributes(szFile, dwFileAttributes)) {
	//	printf("文件 %s 的隐藏和只读属性设置成功\n", szFile);
	//}
	//else {
	//	printf("属性设置失败：%d\n", GetLastError());
	//}
}
//系统信息
void fun10(int argc, char *argv[]){
	//********************获取系统版本信息
	//OSVERSIONINFO ovex;
	//TCHAR szVersionInfo[1024] = {0};
	//ovex.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	//if (!GetVersionEx(&ovex)) {
	//	printf("错误：%d\n", GetLastError());
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
	//	lstrcat(szVersionInfo, "Windows 其它");
	//}
	//printf("%s\n", szVersionInfo);
	//printf("Windows %d.%d Build %d",
	//	ovex.dwMajorVersion,
	//	ovex.dwMinorVersion,
	//	ovex.dwPlatformId);
	//printf("%s\n", ovex.szCSDVersion);

	//获取硬件信息
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	printf("内存分页大小：0x%.0X，可用内存起始：0x%.8X，可用内存年结束：0x%.8X\n",
		si.dwPageSize,
		si.lpMinimumApplicationAddress,
		si.lpMaximumApplicationAddress);
	printf("处理器个数：%d\n", si.dwNumberOfProcessors);
	printf("处理器类型：\n");
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
	printf("处理器架构：");
	switch (si.wProcessorArchitecture) {
	case PROCESSOR_ARCHITECTURE_INTEL:
		printf("INTEL\n");
		break;
	default:
		printf("%d\n", si.wProcessorArchitecture);
		break;
	}
}
//系统信息
void fun11(int argc, char *argv[]){
	//系统目录
	TCHAR szSystemDirectory[MAX_PATH];
	GetSystemDirectory(szSystemDirectory, MAX_PATH);
	printf("系统目录：%s\n", szSystemDirectory);

	TCHAR szWindowsDirectory[MAX_PATH];
	GetWindowsDirectory(szWindowsDirectory, MAX_PATH);
	printf("Windows目录：%s\n", szWindowsDirectory);

	TCHAR szComputerName[MAX_COMPUTERNAME_LENGTH+1];
	DWORD dwComputerNameLength = MAX_COMPUTERNAME_LENGTH + 1;
	GetComputerName(szComputerName, &dwComputerNameLength);
	printf("计算机名：%s\n", szComputerName);

	TCHAR szUserName[64];
	DWORD dwUserNameLength = 64;
	GetUserName(szUserName, &dwUserNameLength);
	printf("用户名：%s\n", szUserName);

	int aMouseInfo[3];
	BOOL fResult = SystemParametersInfo(SPI_GETMOUSE, 0, aMouseInfo, 0);
	if (fResult) {
		aMouseInfo[2] = 2 * aMouseInfo[2];
		SystemParametersInfo(SPI_SETMOUSE, 0, aMouseInfo, SPIF_SENDCHANGE);
	}
}

void fun12(int argc, char *argv[]){}
void fun13(int argc, char *argv[]){}
void fun14(int argc, char *argv[]){}
void fun15(int argc, char *argv[]){}
void fun16(int argc, char *argv[]){}
void fun17(int argc, char *argv[]){}
void fun18(int argc, char *argv[]){}
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