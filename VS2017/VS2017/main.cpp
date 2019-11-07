
#include <locale.h>
#include <Windows.h>


#include <iostream>
using namespace std;

typedef int(*lpAdd)(int, int);

int main(int argc, char *argv[]) {

	HMODULE hModule = LoadLibrary(TEXT("DemoDLL.dll"));
	int n = GetLastError();
	if (hModule != NULL) {
		lpAdd add = (lpAdd)GetProcAddress(hModule, TEXT("add"));
		n = GetLastError();
		if (add != NULL) {
			printf("%d\n", add(22, 33));
		}
		FreeLibrary(hModule);
	}

	system("pause");
	return 0;
}