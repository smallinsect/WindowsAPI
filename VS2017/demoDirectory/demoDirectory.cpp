#include <Windows.h>

#include <iostream>
using namespace std;

int main() {

	TCHAR szSystemDir[MAX_PATH];

	GetSystemDirectory(szSystemDir, MAX_PATH);
	printf("%s\n", szSystemDir);

	HANDLE hFile;
	hFile = CreateFile("systemroot.txt",
		GENERIC_WRITE,
		0,NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwWritten;
	if (hFile != INVALID_HANDLE_VALUE) {
		if (!WriteFile(hFile, szSystemDir, lstrlen(szSystemDir),&dwWritten, NULL)) {
			cout << GetLastError() << endl;
		}
	}
	CloseHandle(hFile);

	system("pause");
	return 0;
}