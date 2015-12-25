#ifndef _EXPORT_TACTONIC_DLL_H
#define _EXPORT_TACTONIC_DLL_H

#if defined (EXPORTBUILD_TACTONIC)
# define _DLLExport __declspec (dllexport)  
# else  
# define _DLLExport __declspec (dllimport)  
#endif

#include "TactonicDLL.h"

// extern "C" bool _DLLExport getPressDown(int index);
// 
// extern "C" bool _DLLExport getPressUp(int index);

extern "C" bool _DLLExport getSingleFrame(int* frame, int* nCount, int* nTotal);

extern "C" bool _DLLExport getMultiFrame(int* frame, int* nDev, int* nCount, int* nTotal);

extern "C" int _DLLExport getDeviceCnt(int* nDev);

extern "C" bool _DLLExport getCertainFrame(int* frame, int no, int* nCount, int* nTotal);

#endif
