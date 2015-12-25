#ifndef _EXPORT_MULTI_TACTONIC_DLL_H
#define _EXPORT_MULTI_TACTONIC_DLL_H

#if defined (EXPORTBUILD_TACTONIC)
# define _DLLExport __declspec (dllexport)  
# else  
# define _DLLExport __declspec (dllimport)  
#endif

#include "MultiTactonicDLL.h"

extern "C" bool _DLLExport getMultiFrame(int* frame, int*devCnt, int* nCount, int* nTotal);

#endif
