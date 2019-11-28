

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
void fun08(int argc, char *argv[]){}
void fun09(int argc, char *argv[]){}
void fun10(int argc, char *argv[]){}