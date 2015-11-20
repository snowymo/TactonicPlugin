#ifndef _EXPORT_INT_DLL_H
#define _EXPORT_INT_DLL_H

#if defined (EXPORTBUILD_INT)
# define _DLLExport __declspec (dllexport)  
# else  
# define _DLLExport __declspec (dllimport)  
#endif

#include "MYINT.h"
#include "TactonicDLL.h"

extern "C" int _DLLExport getInt();

//************************************
// Method:    getPressDown
// FullName:  getPressDown
// Access:    public 
// Returns:   extern "C" bool _DLLExport
// Qualifier:
// Parameter: int index
//************************************
extern "C" bool _DLLExport getPressDown(int index);

#endif
