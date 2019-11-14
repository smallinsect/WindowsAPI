


#include "MyDLL.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved){
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		//printf("DLL_PROCESS_ATTACH\n");
		break;
	case DLL_THREAD_ATTACH:
		//printf("DLL_THREAD_ATTACH\n");
		break;
	case DLL_THREAD_DETACH:
		//printf("DLL_THREAD_DETACH\n");
		break;
	case DLL_PROCESS_DETACH:
		//printf("DLL_THREAD_DETACH\n");
		break;
	}
	return TRUE;
}


int add(int a, int b) {
	return a + b;
}

int showDirFileName(LPTSTR szPath) {
	WIN32_FIND_DATA findFileData;
	HANDLE hFindFile = FindFirstFile(szPath, &findFileData);
	if (hFindFile == INVALID_HANDLE_VALUE) {
		printf("find error %d\n", GetLastError());
		return -1;
	}
	do {
		printf("%s\n", findFileData.cFileName);
	} while (FindNextFile(hFindFile, &findFileData));
	return 0;
}