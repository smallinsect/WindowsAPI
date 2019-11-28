

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

#define BUFSIZE 1024

//遍历卷
void fun03() {
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
void fun04() {

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