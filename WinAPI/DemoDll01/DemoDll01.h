
#ifndef __DEMODLL01_H__
#define __DEMODLL01_H__



#ifdef __cplusplus //如果是C++
#define EXPORT extern "C" __declspec(dllexport)
#else//是C
#define EXPORT __declspec(dllexport)
#endif


#ifdef UNICODE
#define EdrCenterText EdrCenterTextW 
#else
#define EdrCenterText EdrCenterTextA
#endif




#endif