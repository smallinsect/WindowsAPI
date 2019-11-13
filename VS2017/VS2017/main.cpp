
#include <locale.h>
#include <Windows.h>


#include <iostream>
using namespace std;

typedef int(*LPAdd)(int, int);

int main(int argc, char *argv[]) {

	HMODULE hModule = LoadLibrary(TEXT("MyDLL.dll"));
	int n = GetLastError();
	if (hModule != NULL) {
		LPAdd lpAdd = (LPAdd)GetProcAddress(hModule, TEXT("add"));
		n = GetLastError();
		if (lpAdd != NULL) {
			printf("%d\n", lpAdd(22, 33));
		}
		FreeLibrary(hModule);
	}

	system("pause");
	return 0;
}