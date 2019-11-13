
#ifndef __MY_DLL__
#define __MY_DLL__

#include <Windows.h>
#include <stdio.h>

extern "C"
__declspec(dllexport) int  add(int a, int b);


#endif