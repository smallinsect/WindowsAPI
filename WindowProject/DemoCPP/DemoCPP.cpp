// DemoCPP.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <Windows.h>

DWORD ShowFileTime(PFILETIME lptime) {
	FILETIME ftLocal;
	SYSTEMTIME st;
	//转换成本地时间
	FileTimeToLocalFileTime(lptime, &ftLocal);
	//本地时间转换成系统时间
	FileTimeToSystemTime(&ftLocal, &st);
	printf("%d年%#02d月%#02d日，%#02d:%#02d:%#02d\n",
		st.wYear, st.wMonth, st.wDay,
		st.wHour, st.wMinute, st.wSecond);

	return 0;
}

int main()
{
	WIN32_FILE_ATTRIBUTE_DATA wfad;
	//获取文件属性
	if (!GetFileAttributesEx(TEXT("DemoCPP.cpp"), GetFileExInfoStandard, &wfad)) {
		printf("获取文件失败");
		return -1;
	}
	
	printf("创建时间：");
	ShowFileTime(&wfad.ftCreationTime);
	printf("访问时间：");
	ShowFileTime(&wfad.ftLastAccessTime);
	printf("修改时间：");
	ShowFileTime(&wfad.ftLastWriteTime);


    std::cout << "Hello World!\n";

	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
