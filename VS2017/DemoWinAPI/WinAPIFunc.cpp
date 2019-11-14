
#include "WinAPIFunc.h"


void func1() {
	
	TCHAR szFilePath[MAX_PATH] = "E:/smallinsect/WindowsAPI/*";
	WIN32_FIND_DATA findFileData;
	HANDLE handle = FindFirstFile(szFilePath, &findFileData);
	if (handle == INVALID_HANDLE_VALUE) {
		printf("find error %d\n", GetLastError());
		return ;
	}
	do {
		printf("%s\n", findFileData.cFileName);
	} while (FindNextFile(handle, &findFileData));

}