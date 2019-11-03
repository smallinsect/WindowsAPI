#include <Windows.h>

#include <iostream>
using namespace std;

DWORD ShowFileTime(PFILETIME lptime) {
	FILETIME ftLocal;
	SYSTEMTIME st;
	FileTimeToLocalFileTime(lptime, &ftLocal);
	FileTimeToSystemTime(&ftLocal, &st);
	printf("%d��%#02d��%#02d�գ�%#02d:%#02d:%#02d\n",
		st.wYear, st.wMonth, st.wDay,
		st.wHour, st.wMinute, st.wSecond);
	return 0;
}

int main() {
	cout << "Hello world!!" << endl;

	WIN32_FILE_ATTRIBUTE_DATA wfad;

	if (!GetFileAttributesEx("demoFileInfo.cpp", GetFileExInfoStandard, &wfad)) {
		cout << "��ȡ�ļ�����ʧ��" << GetLastError();
		system("pause");
	}

	cout << "����ʱ�䣺\t";
	ShowFileTime(&wfad.ftCreationTime);
	cout << "����ʱ�䣺\t";
	ShowFileTime(&wfad.ftLastAccessTime);
	cout << "�޸�ʱ�䣺\t";
	ShowFileTime(&wfad.ftLastWriteTime);

	system("pause");
	return 0;
}