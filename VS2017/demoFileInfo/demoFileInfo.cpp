#include <Windows.h>

#include <iostream>
using namespace std;

DWORD ShowFileTime(PFILETIME lptime) {
	FILETIME ftLocal;
	SYSTEMTIME st;
	FileTimeToLocalFileTime(lptime, &ftLocal);
	FileTimeToSystemTime(&ftLocal, &st);
	printf("%d年%#02d月%#02d日，%#02d:%#02d:%#02d\n",
		st.wYear, st.wMonth, st.wDay,
		st.wHour, st.wMinute, st.wSecond);
	return 0;
}

int main() {
	cout << "Hello world!!" << endl;

	WIN32_FILE_ATTRIBUTE_DATA wfad;

	if (!GetFileAttributesEx("demoFileInfo.cpp", GetFileExInfoStandard, &wfad)) {
		cout << "获取文件属性失败" << GetLastError();
		system("pause");
	}

	cout << "创建时间：\t";
	ShowFileTime(&wfad.ftCreationTime);
	cout << "访问时间：\t";
	ShowFileTime(&wfad.ftLastAccessTime);
	cout << "修改时间：\t";
	ShowFileTime(&wfad.ftLastWriteTime);

	system("pause");
	return 0;
}