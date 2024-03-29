

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
//时间信息
void fun12(int argc, char *argv[]){
	SYSTEMTIME st;
	GetLocalTime(&st);//获取本地当前时间
	printf("%d-%d-%d %d:%d:%d\n",
		st.wYear, st.wMonth, st.wDay,
		st.wHour, st.wMinute, st.wSecond);
	//st.wHour--;
	//SetLocalTime(&st);//设置当前时间

	DWORD c1 = GetTickCount();//获取开机到现在的时间
	ULONGLONG c2 = GetTickCount64();//获取开机到现在的时间
	printf("%d %lld\n", c1, c2);

}

BOOL CALLBACK EnumFamCallBack(LPLOGFONTA lplf,//逻辑字体
	LPTEXTMETRICA lpntm,//物理字体
	DWORD FontType,//字体类型
	LPARAM aFontCount)//枚举函数传给回调函数的数据 
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

//枚举字体
void fun13(int argc, char *argv[]){
	HDC hdc = GetDC(NULL);//获取桌面HDC
	//三种字体类型
	int aFontCount[] = {0, 0, 0};
	//NULL 枚举所有字体
	EnumFontFamilies(hdc, NULL, (FONTENUMPROC)EnumFamCallBack, (LPARAM)aFontCount);//枚举所有字体

	ReleaseDC(NULL, hdc);
	printf("Number of raster fonts: %d\n", aFontCount[0]);
	printf("Number of vector fonts: %d\n", aFontCount[1]);
	printf("Number of TrueType fonts: %d\n", aFontCount[2]);
}
//环境变量
void fun14(int argc, char *argv[]){
	if (argc == 2 && lstrcmp(argv[1], "showall")) {
		//环境变量格式
		//=::=::\\0ALLUSERSPROFILE=C:\ProgramData\0....
		//获取环境所有环境变量
		LPCH pEv = GetEnvironmentStrings();
		LPTSTR szEnvs = (LPTSTR)pEv;
		while (*szEnvs) {
			printf("%s\n", szEnvs);
			//找到下一个变量
			szEnvs = szEnvs + lstrlen(szEnvs) + 1;
			//while (*szEnvs++) {}//找到下一个变量
		}
		//释放指针
		FreeEnvironmentStrings(pEv);
	}
	else if (argc == 2 && lstrcmp(argv[1], "addnew")) {
		//当前程序环境变量 添加，用户环境变量和系统环境变量不会影响
		if (!SetEnvironmentVariable("a", "b")) {
			printf("添加失败 %d\n", GetLastError());
		}
		else {
			printf("添加成功\n");
		}
	}
	else if (argc == 2 && lstrcmp(argv[1], "delete")) {
		if (!SetEnvironmentVariable("a", NULL)) {
			printf("添加失败 %d\n", GetLastError());
		}
		else {
			printf("添加成功\n");
		}
	}
	else if (argc == 2 && lstrcmp(argv[1], "set")) {
		if (!SetEnvironmentVariable("a", "big")) {
			printf("添加失败 %d\n", GetLastError());
		}
		else {
			printf("添加成功\n");
		}
	}
	else if (argc == 2 && lstrcmp(argv[1], "get")) {
		TCHAR buf[1024];
		if (!GetEnvironmentVariable("a", buf, 1024)) {
			DWORD dwErr = GetLastError();
			if (dwErr == ERROR_ENVVAR_NOT_FOUND) {
				printf("环境变量不存在\n");
			}
			printf("添加失败 %d\n", dwErr);
		}
		else {
			printf("添加成功\n");
		}
	}


}
//枚举系统中的进程
void fun15(int argc, char *argv[]){
	//创建进程快照
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE) {
		printf("进程快照失败\n");
		return ;
	}
	//进程信息
	PROCESSENTRY32 pe = {0};
	pe.dwSize = sizeof(pe);
	//查找第一个进程
	BOOL bRet = Process32First(hSnapshot, &pe);
	while(bRet) {
		//打印进程ID和进程的名称
		printf("PID:%d\t名称:%s\n", pe.th32ProcessID, pe.szExeFile);
		//查找下一个进程
		bRet = Process32Next(hSnapshot, &pe);
	}
	//关闭句柄
	CloseHandle(hSnapshot);
}

BOOL UpdateProcessPrivilege(HANDLE hProcess, LPCTSTR lpRivilegeName = SE_DEBUG_NAME);

//#pragma comment(lib, "psapi.lib")
//枚举进程中的所有
void fun16(int argc, char *argv[]) {
	//提升当前进程的权限
	UpdateProcessPrivilege(GetCurrentProcess());

	DWORD PID[1024];//保存所有进程的ID
	DWORD cbNeeded;//系统当前实际进程数量
	//获取所有进程的ID
	if (!EnumProcesses(PID, sizeof(PID), &cbNeeded)) {
		printf("获取所有进程ID失败\n");
		return;
	}
	DWORD processcount = cbNeeded / sizeof(DWORD);//计算进程个数
	printf("当前共有%d个进程\n", processcount);
	HANDLE hProcess;
	HMODULE hModules[1024];//模块
	for (DWORD i = 0; i < processcount; ++i) {
		hProcess = OpenProcess(
			PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,//打开进程 查询信息 读取信息
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
				printf("模块打开失败\n");
			}
		}
		else {
			printf("PID: %d 打开进程失败\n", PID[i]);
		}
		CloseHandle(hProcess);
	}

}
//提升进程权限
BOOL UpdateProcessPrivilege(HANDLE hProcess, LPCTSTR lpRivilegeName) {
	HANDLE hToken;
	TOKEN_PRIVILEGES TokenPrivileges;
	if (OpenProcessToken(hProcess, TOKEN_ALL_ACCESS, &hToken)) {
		printf("OpenProcessToken 成功\n");
		LUID destLuid;
		if (LookupPrivilegeValue(NULL, lpRivilegeName, &destLuid)) {
			printf("LookupPrivilegeValue 成功\n");
			TokenPrivileges.PrivilegeCount = 1;
			TokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
			TokenPrivileges.Privileges[0].Luid = destLuid;
			if (AdjustTokenPrivileges(hToken, FALSE, &TokenPrivileges,0,NULL,NULL)) {
				printf("AdjustTokenPrivileges 成功\n");
				return TRUE;
			}
		}
	}
	return FALSE;
}

//windows终端服务 
//windows terminate server
//#include <WtsApi32.h>
#pragma comment(lib, "WtsApi32.lib")
void fun17(int argc, char *argv[]){
	////计算机名
	//TCHAR szServerName[32] = TEXT("DESKTOP-45J0D6P");
	////把这台计算机当服务打开
	//HANDLE hWtsServer = WTSOpenServer(szServerName);
	//if (hWtsServer == INVALID_HANDLE_VALUE) {
	//	printf("WTSOpenServer 失败\n");
	//	return;
	//}
	//终端服务进程信息
	PWTS_PROCESS_INFO pProcessInfo;
	//进程个数
	DWORD dwCount;
	//if (!WTSEnumerateProcesses(hWtsServer, 0, 1, &pProcessInfo, &dwCount)) {
	if (!WTSEnumerateProcesses(WTS_CURRENT_SERVER_HANDLE, 0, 1, &pProcessInfo, &dwCount)) {
		printf("WTSEnumerateProcesses 失败\n");
		return;
	}
	//枚举所有进程的信息
	for (DWORD i = 0; i < dwCount; ++i) {
		printf("PID:%d\t名称:%s\n", pProcessInfo[i].ProcessId, pProcessInfo[i].pProcessName);
	}
	//内存释放
	WTSFreeMemory(pProcessInfo);
	//关闭服务
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
//枚举进程信息
void fun18(int argc, char *argv[]){
	HMODULE hNtDll = GetModuleHandle(TEXT("ntdll.dll"));
	if (!hNtDll) {
		printf("GetModuleHandle 失败\n");
		return;
	}
	ZWQUERYSYSTEMINFORMATION ZwQuerySystemInformation = (ZWQUERYSYSTEMINFORMATION)GetProcAddress(hNtDll, TEXT("ZwQuerySystemInformation"));
	if (ZwQuerySystemInformation == NULL) {
		printf("GetProcAddress 失败\n");
		return;
	}

	ULONG cbBuffer = 0x10000;
	LPVOID pBuffer = malloc(cbBuffer);
	if (pBuffer == NULL) {
		printf("malloc 失败\n");
		return;
	}

	ZwQuerySystemInformation(SystemProcessesAndThreadsInformation, pBuffer, cbBuffer, NULL);
	//进程信息结构 pInfo = (进程信息结构)pBuffer;
	PSYSTEM_PRCESS_INFORMATION pInfo = (PSYSTEM_PRCESS_INFORMATION)cbBuffer;
	while (true) {
		printf("PID:%d\t名称:%ls\n", pInfo->ProcessId, pInfo->ProcessName);
		if (pInfo->NextEntryDelta == 0) {
			break;
		}
		pInfo = (PSYSTEM_PRCESS_INFORMATION)(((PUCHAR)pInfo) + pInfo->NextEntryDelta);
	}
	free(pBuffer);
}
//内存信息
void fun19(int argc, char *argv[]){
	MEMORYSTATUSEX ms;
	ms.dwLength = sizeof(ms);

	GlobalMemoryStatusEx(&ms);
	printf("全部物理内存：%lld字节\n", ms.ullTotalPhys);
	printf("可用物理内存：%lld字节\n", ms.ullAvailPhys);
	printf("全部虚拟内存：%lld字节\n", ms.ullTotalVirtual);
	printf("可用虚拟内存：%lld字节\n", ms.ullAvailVirtual);
	printf("全部页面文件：%lld字节\n", ms.ullTotalPageFile);
	printf("可用页面文件：%lld字节\n", ms.ullAvailPageFile);

}
//堆
void fun20(int argc, char *argv[]){
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	HANDLE hHeap1 = HeapCreate(HEAP_NO_SERIALIZE,//堆 不序列化 可以优化执行速度
		si.dwPageSize*2,//最小值 创建两页大小的堆
		si.dwPageSize*10);//最大值 10页
	if (hHeap1 == INVALID_HANDLE_VALUE) {
		printf("HeapCreate hHeap1 失败 %d\n", GetLastError());
		return;
	}
	printf("HeapCreate hHeap1 成功 初始最小2页 最大10页\n");

	HANDLE hHeap2 = HeapCreate(HEAP_NO_SERIALIZE,
		0,//最小值 1
		0);//最大值 自动增长
	if (hHeap2 == INVALID_HANDLE_VALUE) {
		printf("HeapCreate hHeap2 失败 %d\n", GetLastError());
		return;
	}
	printf("HeapCreate hHeap2 成功 初始最小1 最大自动增长\n");

	//获取当前堆的数量
	DWORD dwHeapNum = GetProcessHeaps(0, NULL);
	if (dwHeapNum == 0) {
		printf("GetProcessHeaps 失败 %d\n", GetLastError());
		return;
	}
	printf("GetProcessHeaps 成功 堆有%d个\n", dwHeapNum);

	//在第一个堆上分配内存
	PVOID lpMem1 = HeapAlloc(hHeap1, 
		HEAP_ZERO_MEMORY,//创建的内存 初始化为零
		si.dwPageSize*3);//大小三页
	if (lpMem1 == NULL) {
		printf("HeapAlloc hHeap1 失败 %d\n", GetLastError());
		return;
	}
	printf("HeapAlloc hHeap1 成功 0x%x\n", lpMem1);

	//PVOID lpAloc1 = HeapAlloc(hHeap1,
	//	HEAP_ZERO_MEMORY,
	//	si.dwPageSize*11);
	//if (lpAloc1 == NULL) {
	//	printf("HeapAlloc lpAloc1 失败 %d\n", GetLastError());
	//	return;
	//}
	//printf("HeapAlloc lpAloc1 成功 %d\n", GetLastError());

	//在第二个堆上分配内存
	PVOID lpMem2 = HeapAlloc(hHeap2,
		HEAP_ZERO_MEMORY,//创建的内存 初始化为零
		si.dwPageSize * 3);//大小三页
	if (lpMem1 == NULL) {
		printf("HeapAlloc hHeap1 失败 %d\n", GetLastError());
		return;
	}
	printf("HeapAlloc hHeap1 成功 0x%x\n", lpMem1);

	//重新分配内存大小
	PVOID lpAloc2 = HeapReAlloc(hHeap2,
		HEAP_ZERO_MEMORY,
		lpMem2,
		si.dwPageSize * 11);
	if (lpAloc2 == NULL) {
		printf("HeapAlloc lpAloc1 失败 %d\n", GetLastError());
		return;
	}
	printf("HeapAlloc lpAloc1 成功 0x%x\n", lpAloc2);

	DWORD dwHeapBlockSize = HeapSize(hHeap2, HEAP_NO_SERIALIZE, lpAloc2);
	if (dwHeapBlockSize == -1) {
		printf("HeapSize hHeap2 失败 %d\n", GetLastError());
		return;
	}
	printf("HeapSize hHeap2 大小0x%x\n", dwHeapBlockSize);

	//释放hHeap1堆上的lpMem1内存
	if (!HeapFree(hHeap1, HEAP_NO_SERIALIZE, lpMem1)) {
		printf("HeapFree hHeap1 lpMem1 失败 %d\n", GetLastError());
		return;
	}
	printf("HeapFree hHeap1 lpMem1 成功 \n");
	//
	if (!HeapFree(hHeap2, HEAP_NO_SERIALIZE, lpAloc2)) {
		printf("HeapFree hHeap1 lpMem1 失败 %d\n", GetLastError());
		return;
	}
	printf("HeapFree hHeap1 lpMem1 成功 \n");

	//销毁堆hHeap1
	if (!HeapDestroy(hHeap1)) {
		printf("HeapDestroy hHeap1 失败 %d\n", GetLastError());
		return;
	}
	printf("HeapDestroy hHeap1 成功\n");
	//销毁堆hHeap2
	if (!HeapDestroy(hHeap2)) {
		printf("HeapDestroy hHeap2 失败 %d\n", GetLastError());
		return;
	}
	printf("HeapDestroy hHeap2 成功\n");

	//使用进程的默认堆
	HANDLE hHeap3 = GetProcessHeap();
	LPVOID lpMem3 = HeapAlloc(hHeap3, HEAP_NO_SERIALIZE, si.dwPageSize*3);
	if (lpMem3 == NULL) {
		printf("HeapAlloc hHeap3 lpMem3 失败 %d\n", GetLastError());
		return;
	}
	printf("HeapAlloc hHeap3 lpMem3 成功\n");
	if (!HeapFree(hHeap3, HEAP_NO_SERIALIZE, lpMem3)) {
		printf("HeapFree \n");
		return;
	}
	//进程堆 不能销毁
}

#define MEM_BLOCK_SIZE 32

BOOL ShowMemContent(LPVOID lpMem, SIZE_T dwSize) {
	if (dwSize > MEM_BLOCK_SIZE) {
		printf("dwSize > %d\n", MEM_BLOCK_SIZE);
		return FALSE;
	}
	BYTE lpShow[MEM_BLOCK_SIZE];
	CopyMemory((LPVOID)lpShow, lpMem, dwSize);
	for (int i = 0; i < dwSize; ++i) {
		if ((i % 16) == 0) {
			printf("\n");
		}
		printf("%.2X ", lpShow[i]);
	}
	printf("\n");
	return TRUE;
}
//内存基本操作
void fun21(int argc, char *argv[]){
	HANDLE hHeap = GetProcessHeap();
	//创建内存
	LPVOID lpMem1 = HeapAlloc(hHeap, 0, MEM_BLOCK_SIZE);
	puts("====================lpMem1");
	ShowMemContent(lpMem1, MEM_BLOCK_SIZE);
	//创建内存
	LPVOID lpMem2 = HeapAlloc(hHeap, HEAP_ZERO_MEMORY, MEM_BLOCK_SIZE);
	puts("====================lpMem2");
	ShowMemContent(lpMem2, MEM_BLOCK_SIZE);
	//将lpMem1内存的数据清零
	ZeroMemory(lpMem1, MEM_BLOCK_SIZE);
	puts("====================lpMem1");
	ShowMemContent(lpMem1, MEM_BLOCK_SIZE);
	//将lpMem1内存的数据填充0xAA
	FillMemory(lpMem1, MEM_BLOCK_SIZE, 0xAA);
	puts("====================lpMem1");
	ShowMemContent(lpMem1, MEM_BLOCK_SIZE);
	//填充一部分
	FillMemory(lpMem1, MEM_BLOCK_SIZE/2, 0xBB);
	puts("====================lpMem1");
	ShowMemContent(lpMem1, MEM_BLOCK_SIZE);
	//将第一块内存数据移动到第二块内存中
	MoveMemory(lpMem2, lpMem1, MEM_BLOCK_SIZE);
	puts("====================lpMem2");
	ShowMemContent(lpMem2, MEM_BLOCK_SIZE);
	//两块内存不能重叠 和MoveMemory一样
	//CopyMemory(lpMem2, lpMem1, MEM_BLOCK_SIZE);

	//释放内存
	HeapFree(hHeap, 0, lpMem1);
	HeapFree(hHeap, 0, lpMem2);
}
void fun22(int argc, char *argv[]){}
void fun23(int argc, char *argv[]){}
void fun24(int argc, char *argv[]){}
void fun25(int argc, char *argv[]){}
void fun26(int argc, char *argv[]){}
void fun27(int argc, char *argv[]){}
void fun28(int argc, char *argv[]){}
void fun29(int argc, char *argv[]){}